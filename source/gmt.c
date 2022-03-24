// SPDX-License-Identifier: GPL-2.0
// Copyright (C) 2022 Oleh Kravchenko <oleg@kaa.org.ua>

#include <limits.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "platform.h"
#include "gmt/gmt.h"
#include "list.h"
#include "sha1.h"

struct gmt {
	char		*hint;
	SHA1Context	in;
	struct list	out;
};

struct gmt_data {
	struct list	list;
	void		*ptr;
	size_t		len;
};

static void put_file_contents(const char *path, const void *buf, size_t len)
{
	FILE *f;

	f = fopen(path, "wb");
	if (!f)
		return;

	if (fwrite(buf, 1, len, f) != len)
		abort();

	fclose(f);
}

static struct gmt *__gmtBegin(void)
{
	struct gmt *gmt;

	gmt = malloc(sizeof(struct gmt));
	if (!gmt)
		abort();

	SHA1Reset(&gmt->in);
	list_init(&gmt->out);

	return gmt;
}

GMT_EXPORT struct gmt *gmtBegin(const char *name)
{
	struct gmt *gmt;

	gmt = __gmtBegin();
	gmt->hint = strdup(name);
	if (!gmt->hint)
		abort();

	return gmt;
}

GMT_EXPORT void gmtIn(struct gmt *gmt, const void *ptr, size_t len)
{
	SHA1Input(&gmt->in, ptr, len);
}

GMT_EXPORT void gmtOut(struct gmt *gmt, const void *ptr, size_t len)
{
	struct gmt_data *item;

	item = malloc(sizeof(*item));
	if (!item)
		abort();

	item->ptr = malloc(len);
	if (!item->ptr)
		abort();

	memcpy(item->ptr, ptr, len);
	item->len = len;

	list_add_tail(&gmt->out, &item->list);
}

GMT_EXPORT void gmtEnd(struct gmt *gmt)
{
	uint8_t		sha1[SHA1HashSize];
	char 		sha1name[SHA1HashSize * 2 + 1];
	char		path[PATH_MAX];
	size_t		path_len;
	char		*gmt_prefix;
	unsigned long	filenum;
	struct gmt_data	*i, *t;
	char		filename[PATH_MAX];

	if (!gmt)
		return;

	SHA1Result(&gmt->in, sha1);
	snprintf(sha1name, sizeof(sha1name),
		"%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x"
		"%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x",
		 sha1[0], sha1[1], sha1[2], sha1[3],
		 sha1[4], sha1[5], sha1[6], sha1[7],
		 sha1[8], sha1[9], sha1[10], sha1[11],
		 sha1[12], sha1[13], sha1[13], sha1[15],
		 sha1[16], sha1[17], sha1[18], sha1[19]);

	*path = 0;
	path_len = 0;

	gmt_prefix = getenv("GMT_PREFIX");
	if (gmt_prefix) {
		path_len += snprintf(path + path_len, sizeof(path) - path_len,
				    "%s/", gmt_prefix);
		create_directory(path);
	}

	path_len += snprintf(path + path_len, sizeof(path) - path_len,
			    "%s/", gmt->hint);
	create_directory(path);

	path_len += snprintf(path + path_len, sizeof(path) - path_len,
			    "%s/", sha1name);
	create_directory(path);

	filenum = 0;
	list_foreach_safe(&gmt->out, i, t, struct gmt_data, list) {
		path_len += snprintf(filename, sizeof(filename),
				    "%s%lu", path, filenum++);
		put_file_contents(filename, i->ptr, i->len);

		list_del_node(&i->list);
		free(i->ptr);
		free(i);
	}

	free(gmt->hint);
	free(gmt);
}

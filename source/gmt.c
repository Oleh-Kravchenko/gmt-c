// SPDX-License-Identifier: GPL-2.0
// Copyright (C) 2022 Oleh Kravchenko <oleg@kaa.org.ua>

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "gmt/gmt.h"
#include "list.h"
#include "platform.h"
#include "sha1.h"

struct gmt {
	int		ready;
	char		*hint;
	SHA1Context	in;
	struct list	out;
};

static struct gmt _gmt;

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

GMT_EXPORT void gmtBegin(const char *name)
{
	if (_gmt.ready)
		abort();
	_gmt.ready = !_gmt.ready;

	SHA1Reset(&_gmt.in);
	list_init(&_gmt.out);

	_gmt.hint = strdup(name);
	if (!_gmt.hint)
		abort();
}

GMT_EXPORT void gmtInv(const void *ptr, size_t len)
{
	if (!_gmt.ready)
		abort();

	SHA1Input(&_gmt.in, ptr, len);
}

GMT_EXPORT void gmtOutv(const void *ptr, size_t len)
{
	struct gmt_data *item;

	if (!_gmt.ready)
		abort();

	item = malloc(sizeof(*item));
	if (!item)
		abort();

	item->ptr = malloc(len);
	if (!item->ptr)
		abort();

	memcpy(item->ptr, ptr, len);
	item->len = len;

	list_add_tail(&_gmt.out, &item->list);
}

GMT_EXPORT void gmtEnd(void)
{
	uint8_t		sha1[SHA1HashSize];
	char 		sha1name[SHA1HashSize * 2 + 1];
	char		path[PATH_MAX];
	size_t		path_len;
	char		*gmt_prefix;
	unsigned long	filenum;
	struct gmt_data	*i, *t;
	char		filename[PATH_MAX];

	if (!_gmt.ready)
		abort();

	SHA1Result(&_gmt.in, sha1);
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
			     "%s/", _gmt.hint);
	create_directory(path);

	path_len += snprintf(path + path_len, sizeof(path) - path_len,
			    "%s/", sha1name);
	create_directory(path);

	filenum = 0;
	list_foreach_safe(&_gmt.out, i, t, struct gmt_data, list) {
		path_len += snprintf(filename, sizeof(filename),
				    "%s%lu", path, filenum++);
		put_file_contents(filename, i->ptr, i->len);

		list_del_node(&i->list);
		free(i->ptr);
		free(i);
	}

	free(_gmt.hint);

	memset(&_gmt, 0, sizeof(_gmt));
}

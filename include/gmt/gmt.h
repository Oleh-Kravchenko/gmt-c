// SPDX-License-Identifier: GPL-2.0
// Copyright (C) 2022 Oleh Kravchenko <oleg@kaa.org.ua>

#ifndef __GMT_H
#define __GMT_H

#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <gmt/gmt_export.h>

GMT_EXPORT struct gmt *gmtBegin(const char *name);

GMT_EXPORT void gmtIn(struct gmt *gmt, const void *ptr, size_t len);

GMT_EXPORT void gmtOut(struct gmt *gmt, const void *ptr, size_t len);

GMT_EXPORT void gmtEnd(struct gmt *gmt);

static inline void gmtInString(struct gmt *gmt, const char *s)
{
	gmtIn(gmt, s, strlen(s));
}

static inline void gmtOutString(struct gmt *gmt, const char *s)
{
	gmtOut(gmt, s, strlen(s));
}

static inline void gmtInUint32(struct gmt *gmt, uint32_t i)
{
	gmtIn(gmt, &i, sizeof(i));
}

static inline void gmtOutUint32(struct gmt *gmt, uint32_t i)
{
	gmtOut(gmt, &i, sizeof(i));
}

#endif /* __GMT_H */

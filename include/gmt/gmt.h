// SPDX-License-Identifier: GPL-2.0
// Copyright (C) 2022 Oleh Kravchenko <oleg@kaa.org.ua>

#ifndef __GMT_H
#define __GMT_H

#include <stddef.h>
#include <string.h>

#ifdef WIN32

#include <windows.h>
#define inline __inline

#endif /* WIN32 */

#include <gmt/gmt_export.h>

// v	array
// c	char
// s	short
// i	int
// f	float
// d	double
// ub	unsigned char
// us	unsigned short
// ui	unsigned int
// str	NULL terminated string

GMT_EXPORT void gmtBegin(const char *name);

GMT_EXPORT void gmtInv(const void *ptr, size_t len);

static inline void gmtInc(char c)
{
	gmtInv(&c, sizeof(c));
}

static inline void gmtIns(short s)
{
	gmtInv(&s, sizeof(s));
}

static inline void gmtIni(int i)
{
	gmtInv(&i, sizeof(i));
}

static inline void gmtInf(float f)
{
	gmtInv(&f, sizeof(f));
}

static inline void gmtInd(double d)
{
	gmtInv(&d, sizeof(d));
}

static inline void gmtInub(unsigned char uc)
{
	gmtInv(&uc, sizeof(uc));
}

static inline void gmtInus(unsigned short us)
{
	gmtInv(&us, sizeof(us));
}

static inline void gmtInui(unsigned int ui)
{
	gmtInv(&ui, sizeof(ui));
}

static inline void gmtInstr(const char *str)
{
	gmtInv(str, strlen(str));
}

GMT_EXPORT void gmtOutv(const void *ptr, size_t len);

static inline void gmtOutc(char c)
{
	gmtOutv(&c, sizeof(c));
}

static inline void gmtOuts(short s)
{
	gmtOutv(&s, sizeof(s));
}

static inline void gmtOuti(int i)
{
	gmtOutv(&i, sizeof(i));
}

static inline void gmtOutf(float f)
{
	gmtOutv(&f, sizeof(f));
}

static inline void gmtOutd(double d)
{
	gmtOutv(&d, sizeof(d));
}

static inline void gmtOutub(unsigned char uc)
{
	gmtOutv(&uc, sizeof(uc));
}

static inline void gmtOutus(unsigned short us)
{
	gmtOutv(&us, sizeof(us));
}

static inline void gmtOutui(unsigned int ui)
{
	gmtOutv(&ui, sizeof(ui));
}

static inline void gmtOutstr(const char *str)
{
	gmtOutv(str, strlen(str));
}

GMT_EXPORT void gmtEnd(void);

#endif /* __GMT_H */

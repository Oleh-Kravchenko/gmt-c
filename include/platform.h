// SPDX-License-Identifier: GPL-2.0
// Copyright (C) 2022 Oleh Kravchenko <oleg@kaa.org.ua>

#ifndef __GMT_PLATFORM_H
#define __GMT_PLATFORM_H

void create_directory(const char *path);

#ifdef WIN32

#include <windows.h>

#ifndef PATH_MAX
#	define PATH_MAX MAX_PATH
#endif /* PATH_MAX */

#if !((__MINGW32__) || (__MINGW64__))

int snprintf(char *str, size_t size, const char *format, ...);

#endif /* !((__MINGW32__) || (__MINGW64__)) */

#endif /* WIN32 */

#endif /* __GMT_PLATFORM_H */

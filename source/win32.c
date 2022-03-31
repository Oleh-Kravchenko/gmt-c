// SPDX-License-Identifier: GPL-2.0
// Copyright (C) 2022 Oleh Kravchenko <oleg@kaa.org.ua>

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "platform.h"

void create_directory(const char *path)
{
	if (!CreateDirectoryA(path, NULL) && GetLastError() != ERROR_ALREADY_EXISTS)
		abort();
}

#if !((__MINGW32__) || (__MINGW64__))

int snprintf(char *str, size_t size, const char *format, ...)
{
	va_list	arglist;
	int	ret;

	va_start(arglist, format);
	ret = _vsnprintf_s_l(str, size, _TRUNCATE, format, NULL, arglist);
	if (ret == -1)
		abort();

	return ret;
}

#endif /* !((__MINGW32__) || (__MINGW64__)) */

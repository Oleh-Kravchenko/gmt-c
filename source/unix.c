// SPDX-License-Identifier: GPL-2.0
// Copyright (C) 2022 Oleh Kravchenko <oleg@kaa.org.ua>

#include <errno.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "platform.h"

void create_directory(const char *path)
{
	if (mkdir(path, 0755) && errno != EEXIST)
		abort();
}

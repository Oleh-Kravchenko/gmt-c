// SPDX-License-Identifier: GPL-2.0
// Copyright (C) 2022 Oleh Kravchenko <oleg@kaa.org.ua>

#include <stdio.h>

#include <gmt/gmt.h>

int main(int argc, char *argv[])
{
	const char *input = "Input string";
	const char *output = "Output string";

	printf("gmt-%s (%s: %s)\n",
	       PROJECT_VERSION,
	       PROJECT_GIT_BRANCH,
	       PROJECT_GIT_SHORT);

	struct gmt *gmt = gmtBegin(__func__);

	gmtInString(gmt, input);
	gmtInUint32(gmt, 1);
	gmtInUint32(gmt, 2);
	gmtInUint32(gmt, 3);

	gmtOutString(gmt, output);
	gmtOutUint32(gmt, 4);
	gmtOutUint32(gmt, 5);
	gmtOutUint32(gmt, 6);

	gmtEnd(gmt);

	return 0;
}

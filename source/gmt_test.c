// SPDX-License-Identifier: GPL-2.0
// Copyright (C) 2022 Oleh Kravchenko <oleg@kaa.org.ua>

#include <stdio.h>

#include <gmt/gmt.h>

int main(int argc, char *argv[])
{
	printf("gmt-%s (%s: %s)\n",
	       PROJECT_VERSION,
	       PROJECT_GIT_BRANCH,
	       PROJECT_GIT_SHORT);

	gmtBegin("test");

	gmtInc(-10);
	gmtIns(-10000);
	gmtIni(-1000000);
	gmtInf(3.14159);
	gmtInd(2.71828);
	gmtInub(255);
	gmtInus(65535);
	gmtInui(1000000);
	gmtInstr("Input string");

	// black box

	gmtOutc(-10);
	gmtOuts(-10000);
	gmtOuti(-1000000);
	gmtOutf(3.14159);
	gmtOutd(2.71828);
	gmtOutub(255);
	gmtOutus(65535);
	gmtOutui(1000000);
	gmtOutstr("Output string");

	gmtEnd();

	return 0;
}

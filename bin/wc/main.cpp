/*
 * Copyright (C) 2016 SuperTau, 2017 Daniel Martín
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <string.h>
#include "printInfo.h"
#include "options.h"

int main(int argc, char *argv[])
{
	unsigned char options = 0;
	int i;
	int nPrinted = -1;

	if (argc < 2) {
		printf("Usage: %s [-l] [-w] [-c] [FILE(s)]\n", argv[0]);
		return 0;
	}

	for(i = 1; i < argc; i++)
	{
		if(!strcmp(argv[i], "-l")) options |= OPT_L;
		if(!strcmp(argv[i], "-w")) options |= OPT_W;
		if(!strcmp(argv[i], "-c")) options |= OPT_C;
	}

	if(!options) options = OPT_L | OPT_W | OPT_C;

	for(i = 1; i < argc; i++)
	{
		if(strcmp(argv[i], "-l") && strcmp(argv[i], "-w") && strcmp(argv[i], "-c"))
		{
			printInfo(argv[i], options);
			nPrinted++;
		}
	}

	if (nPrinted) printTotal(options);

	return 0;
}

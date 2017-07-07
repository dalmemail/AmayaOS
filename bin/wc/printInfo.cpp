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

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "lineCounter.h"
#include "wordCounter.h"
#include "charCounter.h"
#include "options.h"

int getFileSize(char *path)
{
	struct stat st;
	return ((stat(path, &st)) < 0) ? -1 : st.st_size;
}

void printError(char *path)
{
	printf("wc: %s: %s\n", path, strerror(errno));
}

void printInfo(char *path, unsigned char options)
{
	int fs = getFileSize(path);
	if (fs == -1) { printError(path); return; }
	int fd = open(path, O_RDONLY);
	if (fd == -1) { printError(path); return; }

	char *fc = (char *)malloc(fs+1);
	if (read(fd, fc, fs+1) == -1) {
		printError(path);
		close(fd);
		return;
	}
	char *c = fc;
	do {

		if(options & OPT_L) lineCounter(*c);
		if(options & OPT_W) wordCounter(*c);
		if(options & OPT_C) charCounter(*c);
		*c++;

	} while(*c);

	free(fc);

	if(options & OPT_L) printf("%d ", sl);
	if(options & OPT_W) printf("%d ", sw);
	if(options & OPT_C) printf("%d ", sc);
	printf("%s\n", path);

	resetLineCounter();
	resetWordCounter();
	resetCharCounter();

	close(fd);
}

void printTotal(unsigned char options)
{
	if(options & OPT_L) printf("%d ", tl);
	if(options & OPT_W) printf("%d ", tw);
	if(options & OPT_C) printf("%d ", tc);
	printf("total\n");
}

/*
 * Copyright (C) 2016 Dan Rulos
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
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "wordcount.h"
#include "linecount.h"
#include "charcount.h"

#define YES 1
#define NO 0

int f_size(char *path)
{
	struct stat st;
	int ssize;
	if ((stat(path, &st)) < 0) {
		ssize = -1;
	}
	else {
		ssize = st.st_size;
	}
	return ssize;
}

int main(int argc, char **argv)
{
	int fd;
	int c = NO, l = NO,w = NO;
	if (argc < 2) {
		printf("Uso: %s FILE1 FILE2...\n", argv[0]);
		return EXIT_FAILURE;
	}
	/* check arguments */
	int nofiles = 0;
	for (int i=1; i < argc; i++) {
		if (strcmp(argv[i], "-c") == 0) {
			c = YES;
			nofiles++;
		}
		if (strcmp(argv[i], "-l") == 0) {
			l = YES;
			nofiles++;
		}
		if (strcmp(argv[i], "-w") == 0) {
			w = YES;
			nofiles++;
		}
	}
	if (nofiles == 0) {
		c = l = w = YES;
	}
	int nc = 0, nl = 0, nw = 0, sw = 0, sl = 0, sc = 0;
	for (int i=1; i < argc; i++) {
		if (strcmp(argv[i], "-c") != 0 && strcmp(argv[i], "-w") != 0 && strcmp(argv[i], "-l") != 0) {
			char *ch = new char [f_size(argv[i])];
			if ((fd = open(argv[i], O_RDONLY)) < 0) {
				printf("Error al abrir '%s': %s\n", argv[i], strerror(errno));
			}
			else {
				read(fd, ch, f_size(argv[i]));
				close(fd);
				if (l == YES) {
					nl = linecount(ch);
					sl += nl;
					printf("\t%d", nl);
				}
				if (w == YES) {
					nw = wordcount(ch);
					sw += nw;
					printf("\t%d", nw);
				}
				if (c == YES) {
					nc = charcount(ch);
					sc += nc;
					printf("\t%d", nc);
				}
				printf("\t%s\n", argv[i]);
			}
			delete ch;
		}
	}
	if (argc - nofiles > 2) {
		if (l == YES) {
			printf("\t%d", sl);
		}
		if (w == YES) {
			printf("\t%d", sw);
		}
		if (c == YES) {
			printf("\t%d", sc);
		}
		printf("\ttotal\n");
	}
	return EXIT_SUCCESS;
}

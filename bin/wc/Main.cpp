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
#include "wc.h"

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
	int chars = NO, lines = NO,words = NO;
	if (argc < 2) {
		printf("Uso: %s FILE1 FILE2...\n", argv[0]);
		return EXIT_FAILURE;
	}
	/* check arguments */
	int nofiles = 0;
	for (int i=1; i < argc; i++) {
		if (strcmp(argv[i], "-c") == 0) {
			chars = YES;
			nofiles++;
		}
		if (strcmp(argv[i], "-l") == 0) {
			lines = YES;
			nofiles++;
		}
		if (strcmp(argv[i], "-w") == 0) {
			words = YES;
			nofiles++;
		}
	}
	if (nofiles == 0) {
		chars = lines = words = YES;
	}
	int nc = 0, nl = 0, nw = 0;
	for (int i=1; i < argc; i++) {
		if (strcmp(argv[i], "-c") != 0 && strcmp(argv[i], "-w") != 0 && strcmp(argv[i], "-l") != 0) {
			char *file_content = new char [f_size(argv[i])];
			if ((fd = open(argv[i], O_RDONLY)) < 0) {
				printf("Error al abrir '%s': %s\n", argv[i], strerror(errno));
			}
			else {
				read(fd, file_content, f_size(argv[i]));
				close(fd);
				struct wc file_wc = wordcount(file_content);
				if (lines) {
					nl += file_wc.lines;
					printf("\t%d", file_wc.lines);
				}
				if (words) {
					nw += file_wc.words;
					printf("\t%d", file_wc.words);
				}
				if (chars) {
					nc += file_wc.chars;
					printf("\t%d", file_wc.chars);
				}
				printf("\t%s\n", argv[i]);
			}
			delete file_content;
		}
	}
	if (argc - nofiles > 2) {
		if (lines) {
			printf("\t%d", nl);
		}
		if (words) {
			printf("\t%d", nw);
		}
		if (chars) {
			printf("\t%d", nc);
		}
		printf("\ttotal\n");
	}
	return EXIT_SUCCESS;
}

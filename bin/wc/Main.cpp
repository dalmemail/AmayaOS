/*
 * Copyright (C) 2015 Dan Rulos
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
#include <files.h>
#include <stdlib.h>

#define IN 0
#define OUT 1

#define YES 0
#define NO 1

int main(int argc, char **argv)
{
	int c,l,w = NO;
	if (argc < 2) {
		printf("Uso: %s FILE1 FILE2...\n", argv[0]);
		return EXIT_FAILURE;
	}
	/* check arguments */
	int no = 0;
	for (int i=1; i < argc; i++) {
		if (strcmp(argv[i], "-c") == 0) {
			c = YES;
			no++;
		}
		if (strcmp(argv[i], "-l") == 0) {
			l = YES;
			no++;
		}
		if (strcmp(argv[i], "-w") == 0) {
			w = YES;
			no++;
		}
	}
	if (no == 0) {
		c = l = w = YES;
	}
	int sc,sl,sw = 0;
	int nc,nl,nw = 0;
	int state = OUT;
	for (int i=1; i < argc; i++) {
		if (strcmp(argv[i], "-c") == 0 ||strcmp(argv[i], "-w") == 0 ||strcmp(argv[i], "-l") == 0) {
		}
		else {
			file *f = new file();
			f->setpath(argv[i]);
			f->f_open(O_RDONLY);
			char *ch = f->readAll();
			f->f_close();
			nc = nl = nw = 0;
			for (unsigned int k=0; k < strlen(ch); k++) {
				nc++;
				if (ch[k] == '\n') {
					nl++;
				}
				if (ch[k] == '\n' || ch[k] == ' ' || ch[k] == '\t') {
					state = OUT;
				}
				else if (state == OUT) {
					state = IN;
					nw++;
				}
			}
			if (l == YES) {
				printf("\t%d", nl);
			}
			if (w == YES) {
				printf("\t%d", nw);
			}
			if (c == YES) {
				printf("\t%d", nc);
			}
			printf("\t%s\n", argv[i]);
			sl = sl + nl;
			sw = sw + nw;
			sc = sc + nc;
		}
	}
	if (argc - no > 2) {
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

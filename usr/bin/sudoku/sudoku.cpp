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

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <files.h>
#include "sudoku.h"

#define EASY 0
#define DIFFICULT 1
#define COMPETITION_EASY 2
#define COMPETITION_DIFF 3

void clear_window()
{
	char str[] = {0x1b, 0x5b, 0x48, 0x1b, 0x5b, 0x4a, '\0'};
	printf("%s", str);
}

int getnum()
{
	static char ch[1024];
	read(0, ch, 1);
	if (ch[0] == '\b') {
		return -1;
	}
	int n = atoi(ch);

	return n;
}

void print_sudoku(int *numbers)
{
	clear_window();
	for (int i = 0; i < 16; i++) {
		printf("|");
		if (numbers[i] == 0) {
			printf("X");
		}
		if (numbers[i] != 0) {
			printf("%d", numbers[i]);
		}
		if ((i+1) % 4 == 0) {
			printf("|\n");
		}
	}
	printf("\n");
}

int randomnumber()
{
	file *f = new file();
	f->setpath("/dev/time");
	f->f_open(O_RDONLY);
	char *ch = f->readAll();
	f->f_close();
	return (atoi(ch) % 10);
}

int make_sudoku(int pos, int nsudoku, int mode)
{
	/* available sudoku */
	int easy[10][16] {
		{2,1,0,0,0,3,2,0,0,0,0,4,1,0,0,0},
		{0,0,0,1,4,0,0,2,2,0,0,4,0,0,2,3},
		{4,0,0,0,0,0,1,0,0,2,4,0,0,0,2,1},
		{0,2,1,0,0,0,3,2,0,1,0,0,2,0,0,1},
		{0,0,0,3,0,4,0,2,0,0,2,1,1,0,0,0},
		{0,2,0,0,0,0,3,0,0,0,0,4,4,1,2,0},
		{0,2,0,0,1,0,0,2,3,0,0,4,0,0,1,0},
		{2,4,0,0,0,0,2,0,4,0,0,1,0,3,0,0},
		{0,3,0,0,0,1,0,0,3,0,1,0,1,0,2,0},
		{1,0,0,0,3,0,1,0,0,0,0,4,0,3,2,0},
	};
	int difficult[10][16] {
		{4,0,0,0,0,0,4,0,0,0,0,3,0,2,0,0},
		{4,0,0,3,0,2,0,0,2,0,4,0,0,0,0,0},
		{0,2,0,0,0,0,2,0,0,0,0,3,4,0,0,0},
		{0,4,0,0,0,0,0,2,0,0,0,0,0,0,2,3},
		{2,0,0,0,0,0,0,3,0,0,0,0,0,4,1,0},
		{0,0,0,2,3,0,0,0,0,0,1,0,0,1,0,0},
		{0,0,2,0,0,3,0,0,0,0,0,2,4,0,0,0},
		{0,0,0,0,1,0,2,0,0,4,0,3,0,0,0,0},
		{0,2,0,0,0,0,0,4,2,0,0,0,0,0,0,3},
		{2,4,0,0,0,1,0,0,0,0,0,1,0,0,2,0},
	};
	switch (mode) {
		case EASY:
		case COMPETITION_EASY:
			return easy[nsudoku][pos];
			break;
		case DIFFICULT:
		case COMPETITION_DIFF:
			return difficult[nsudoku][pos];
			break;
	}
	return 0;
}

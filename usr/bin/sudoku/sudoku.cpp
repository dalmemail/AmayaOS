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

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <files.h>
#include "sudoku.h"

void clear_window()
{
	char str[] = {0x1b, 0x5b, 0x48, 0x1b, 0x5b, 0x4a, '\0'};
	printf("%s", str);
}

void print_sudoku(int *numbers, int act_pos)
{
	char *output = new char[1024];
	clear_window();
	strcpy(output, "\n\t\t\t\t");
	for (int i = 0; i < 16; i++) {
		strcat(output, "|");
		if (i == act_pos) {
			strcat(output, "<");
		}
		else {
			strcat(output, " ");
		}
		if (numbers[i] == 0) {
			strcat(output, "X");
		}
		if (numbers[i] != 0) {
			char *c = new char[2];
			c[0] = numbers[i]+'0';
			c[1] = '\0';
			strcat(output, c);
			delete c;
		}
		if (i == act_pos) {
			strcat(output, ">");
		}
		else {
			strcat(output, " ");
		}
		if ((i+1) % 4 == 0) {
			strcat(output, "|\n\t\t\t\t");
		}
	}
	strcat(output, "\n\t\t\t\tw\n\t\t\t      a   d     move cursor\n\t\t\t\ts");
	strcat(output, "\n\t\t\t\tf\tfix squares");
	strcat(output, "\n\t\t\t\tq\tquit game");
	strcat(output, "\n\t\t\t\tn\tnew board");
	printf("%s\n", output);
	delete output;
}

char *read_file(char *path)
{
	file *f = new file();
	f->setpath(path);
	f->f_open(O_RDONLY);
	char *ch = f->readAll();
	f->f_close();
	return ch;
}

int randomnumber()
{
	char *ch = read_file("/dev/time");
	return (atoi(ch) % 10);
}

int make_sudoku(int pos, char *path)
{
	char *ch = read_file(path);
	return (ch[pos]-'0');
}

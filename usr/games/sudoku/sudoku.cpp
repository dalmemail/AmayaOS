/*
 * Copyright (C) 2016, 2017 Daniel Martín
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
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "sudoku.h"

void clear_window()
{
	char str[] = {0x1b, 0x5b, 0x48, 0x1b, 0x5b, 0x4a, '\0'};
	printf("%s", str);
}

void print_sudoku(unsigned int *numbers, int act_pos)
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

int getSize(char *path)
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

char *read_file(char *path)
{
	int fd;
	char *content;
	int fsize = getSize(path);
	if (fsize == -1) {
		printf("Error: %s\n", strerror(errno));
		return (char *)NULL;
	}
	if ((fd = open(path, O_RDONLY)) < 0) {
		printf("Error: %s\n", strerror(errno));
		return (char *)NULL;
	}
	content = new char[17];
	read(fd, content, 16);
	return content;
}

unsigned int getSudokuFromFile(char *path, unsigned int *Sudoku)
{
	char *content = read_file(path);
	if (content == NULL) return 0;
	for (unsigned int i = 0; i < 16; i++) {
		Sudoku[i] = content[i]-'0';
		if (content[i] < '0' || content[i] > '4') Sudoku[i] = 0;
	}
	delete content;
	return 1;
}

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
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include "gamemodes.h"
#include "sudoku.h"

#define VERSION "0.6"

int main(int argc, char **argv)
{
	char *path;
	if (argc == 1) {
		int n = -1;
		while (n == -1) {
			path = new char[256];
			strcpy(path, "/etc/sudoku/sudoku_");
			n = randomnumber() % 2;
			if (n == 0) {
				strcat(path, "easy");
			}
			else {
				strcat(path, "difficult");
			}
			char *c = new char[2];
			c[0] = (randomnumber()+'0');
			c[1] = '\0';
			strcat(path, c);
			n = sudoku(path);
			if (n == 0) {
				clear_window();
			}
			delete c;
			delete path;
		}
	}
	else if (argc == 2 && (strcmp(argv[1], "--version")) == 0) {
		printf("%s: Version %s\n", argv[0], VERSION);
	}
	else if (argc == 2 && (strcmp(argv[1], "--help")) == 0) {
		printf("Uso: %s archivo.suk\n\n", argv[0]);
		printf("--help\tMuestra esta ayuda y finaliza\n");
		printf("--version\tMuestra la version de %s y finaliza\n", argv[0]);
	}
	else if (argc == 2) {
		int fd;
		if ((fd = open(argv[1], O_RDONLY)) < 0) {
			printf("Error: El archivo %s no existe o no puede ser abierto\n", argv[1]);
		}
		else {
			path = &argv[1][0];
			close(fd);
			sudoku(path);
		}
	}
	return 0;
}

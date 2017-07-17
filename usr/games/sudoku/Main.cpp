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

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <time.h>
#include "gamemodes.h"
#include "sudoku.h"
#include "sudoku_database.h"

#define VERSION "0.6.1"

int main(int argc, char **argv)
{
	if (argc == 1) {
		int playSudoku = 1;
		while (playSudoku) {
			int sud_n = random() % N_SUDOKUS;
			playSudoku = sudoku(sudb[sud_n]);
			if (!playSudoku) clear_window();
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
			close(fd);
			unsigned int sudokuFromFile[16];
			if (getSudokuFromFile(argv[1], sudokuFromFile)) sudoku(sudokuFromFile);
		}
	}
	return 0;
}

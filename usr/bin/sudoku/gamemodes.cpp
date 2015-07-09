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

#include "sudoku.h"
#include <stdio.h>
#include <stdlib.h>
#include "gamemodes.h"

#define LOST 0
#define WIN 1

#define EASY 0
#define DIFFICULT 1
#define COMPETITION_EASY 2
#define COMPETITION_DIFF 3

int sudoku(int mode)
{
	clear_window();
	int level = 1;
	/* we get a random number to select a sudoku */
	int n = randomnumber();
	int numbers[16];
	/* get sudoku */
	for (int i = 0; i < 16; i++) {
		numbers[i] = make_sudoku(i, n, mode);
	}
	int sudoku4x4[4][4];
	int subregions[4][4];
	char option = 'r';
	while (option != 'c' && option != 'C') {
		print_sudoku(numbers);
		for (int i = 0; i < 16; i++) {
			if (numbers[i] == 0) {
				printf("Introduce el valor a la X%d: ", i+1);
				numbers[i] = getnum();
				if (numbers[i] == 0) {
					numbers[i] = 1;
					i--;
				}
				printf("%c\n", numbers[i]);
				print_sudoku(numbers);
			}
		}
		for (int i = 0, k = 0, p=0; k < 4; i++) {
			sudoku4x4[k][i] = numbers[p];
			if ((i+1) % 4 == 0) {
				k++;
				i = -1;
			}
			p++;
		}
		for(int i = 0, k = 0; i < 4; i++) {
			for(int j = 0; j < 4; j++) {
				subregions[i][j] = numbers[k];
				k++;
			}
		}
		int gamestate = WIN;
		/* check rows and columns */
		for (int i = 0, k = 0; k < 4; i++) {
			if (sudoku4x4[k][i] == sudoku4x4[k][0] && i != 0) {
				gamestate = LOST;
			}
			if (sudoku4x4[k][i] == sudoku4x4[k][1] && i != 1) {
				gamestate = LOST;
			}
			if (sudoku4x4[k][i] == sudoku4x4[k][2] && i != 2) {
				gamestate = LOST;
			}
			if (sudoku4x4[k][i] == sudoku4x4[k][3] && i != 3) {
				gamestate = LOST;
			}
			if ((i+1) % 4 == 0) {
				k++;
				i = -1;
			}
		}
		for (int i = 0, k = 0; i < 4; k++) {
			if (sudoku4x4[k][i] == sudoku4x4[0][i] && k != 0) {
				gamestate = LOST;
			}
			if (sudoku4x4[k][i] == sudoku4x4[1][i] && k != 1) {
				gamestate = LOST;
			}
			if (sudoku4x4[k][i] == sudoku4x4[2][i] && k != 2) {
				gamestate = LOST;
			}
			if (sudoku4x4[k][i] == sudoku4x4[3][i] && k != 3) {
				gamestate = LOST;
			}
			if ((k+1) % 4 == 0) {
				i++;
				k = -1;
			}
		}
		/* check subregions */
		for (int i = 0, k = 0; k < 4; i++) {
			if (subregions[k][i] == subregions[k][0] && i != 0) {
				gamestate = LOST;
			}
			if (subregions[k][i] == subregions[k][1] && i != 1) {
				gamestate = LOST;
			}
			if (subregions[k][i] == subregions[k][2] && i != 2) {
				gamestate = LOST;
			}
			if (subregions[k][i] == subregions[k][3] && i != 3) {
				gamestate = LOST;
			}
			if ((i+1) % 4 == 0) {
				k++;
				i = -1;
			}
		}
		if (gamestate == WIN && mode < 2) {
			printf("Nivel %d COMPLETADO\n", level);
			do {
				printf("[N]ivel %d o [C]errar\n", level+1);
				option = getchar();
			} while (option != 'n' && option != 'N' && option != 'c' && option != 'C');
			n = randomnumber();
			level++;
		}
		if (gamestate == LOST && mode < 2) {
			printf("Nivel %d NO COMPLETADO\n", level);
			do {
				printf("[R]eintentar o [C]errar\n");
				option = getchar();
			} while (option != 'r' && option != 'R' && option != 'c' && option != 'C');
		}
		if (option == 'r' || option == 'R' || option == 'n' || option == 'N') {
			for (int i = 0; i < 16; i++) {
				numbers[i] = make_sudoku(i, n, mode);
			}
		}
		/* multiplayer mode */
		if (mode == COMPETITION_EASY && gamestate == WIN) {
			return 1;
		}
		if (mode == COMPETITION_DIFF && gamestate == WIN) {
			return 3;
		}
		if (mode >= COMPETITION_EASY && gamestate == LOST) {
			return 0;
		}
	}
	return 0;
}

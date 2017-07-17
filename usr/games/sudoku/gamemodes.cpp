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

#include "sudoku.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gamemodes.h"

#define FIX 'f'
#define EXIT 'q'
#define UP 'w'
#define DOWN 's'
#define LEFT 'a'
#define RIGHT 'd'
#define NEW 'n'

int sudoku(unsigned int numbers_def[16])
{
	clear_window();
	unsigned int numbers[16];
	for (int i = 0; i < 16; i++) {
		numbers[i] = numbers_def[i];
	}
	char option = 'a';
	for (int i = 0; option != EXIT;) {
		print_sudoku(numbers, i);
		option = getchar();
		if (option == FIX) {
			clear_window();
			if (checkSudoku(numbers)) {
				printf("\n\t\t\t\tYou win!\n");
			}
			else {
				printf("\n\t\t\t\tYou lost\n");
			}
			printf("\t\t\t\tPress any key to exit\n");
			getchar();
			return 0;
		}
		else if (option == UP && i >= 4) {
			i -= 4;
		}
		else if (option == DOWN && i <= 11) {
			i += 4;
		}
		else if (option == LEFT && i > 0) {
			i--;
		}
		else if (option == RIGHT && i < 15) {
			i++;
		}
		else if (option >= '1' && option <= '4' && numbers_def[i] == 0) {
			numbers[i] = (option - '0');
		}
		else if (option == NEW) {
			return 1;
		}
	}
	return 0;
}

int checkSudoku(unsigned int numbers[16])
{
	int sudoku4x4[4][4];
	int subregions[4][4];
	for (int i = 0, k = 0, p=0; k < 4; i++) {
		sudoku4x4[k][i] = numbers[p];
		if ((i+1) % 4 == 0) {
			k++;
			i = -1;
		}
		p++;
	}
	for(int i = 0, k = 0; i < 4; i++) {
		int action = 0;
		for(int j = 0; j < 4; j++) {
			subregions[i][j] = numbers[k];
			if ((k+1) % 2 == 0) {
				if ((k+1) == 8) {
					k = 5;
					action = 0;
				}
				if (action == 0) {
					k += 3;
					action++;
				}
				else {
					k -= 3;
					action--;
				}
			}
			else {
				k++;
			}
		}
	}
	int gamestate = WIN;
	/* check rows and columns */
	for (int i = 0, k = 0; k < 4; i++) {
		for (int x = 0; x < 4; x++) {
			if (sudoku4x4[k][i] == sudoku4x4[k][x] && i != x) {
				gamestate = LOST;
			}
		}
		if ((i+1) % 4 == 0) {
			k++;
			i = -1;
		}
	}
	for (int i = 0, k = 0; i < 4; k++) {
		for (int x = 0; x < 4; x++) {
			if (sudoku4x4[k][i] == sudoku4x4[x][i] && k != x) {
				gamestate = LOST;
			}
		}
		if ((k+1) % 4 == 0) {
			i++;
			k = -1;
		}
	}
	/* check subregions */
	for (int i = 0, k = 0; k < 4; i++) {
		for (int x = 0; x < 4; x++) {
			if (subregions[k][i] == subregions[k][x] && i != x) {
				gamestate = LOST;
			}
		}
		if (i+1 == 4) {
			k++;
			i = -1;
		}
	}
	return gamestate;
}

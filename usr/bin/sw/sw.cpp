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
#include <stdlib.h>
#include "sw.h"
#include "sw_colors.h"

#define UNKOWN_WATER 0
#define WATER 1
#define UNKOWN_SHIP 2
#define SHIP 3

int game_map[2][10][10];

void clear_window()
{
	char str[] = {0x1b, 0x5b, 0x48, 0x1b, 0x5b, 0x4a, '\0'};
	printf("%s", str);
}

void print_map()
{
	clear_window();
	printf(" [x] 0  1  2  3  4  5  6  7  8  9\t[x] 0  1  2  3  4  5  6  7  8  9\n");
	printf(" --------------------------------\t--------------------------------\n");
	for (int i = 0; i < 10; i++) {
		printf("%d    ", i);
		for (int x = 0; x <= 1; x++) {
			if (x == 1) {
				printf("\t    ");
			}
			for (int y = 0; y != 10; y++) {
				switch(game_map[x][i][y]) {
					case UNKOWN_WATER:
					case UNKOWN_SHIP:
						printf("?  ");
						break;
					case WATER:
						printf(BLUE "#  \e[m");
						break;
					case SHIP:
						printf(RED "X  \e[m");
						break;
				}
			}
		}
		printf("\n");
	}
}

int sw()
{
	print_map();
	return EXIT_SUCCESS;
}

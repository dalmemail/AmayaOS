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
#include "random.h"

#define UNKOWN_WATER 0
#define WATER_IA 1
#define WATER 2
#define UNKOWN_SHIP 3
#define SHIP_IA 4
#define SHIP 5

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
						printf(BLUE);
					case WATER_IA:
						printf("#  \e[m");
						break;
					case SHIP:
						printf(RED);
					case SHIP_IA:
						printf("X  \e[m");
						break;
				}
			}
		}
		printf("\n");
	}
}

void put_ship_on_map()
{
	for (int i = 0; i < 10; i++) {
		for (int x = 0; x < 10; x++) {
			game_map[1][i][x] = WATER_IA;
		}
	}
	int pos1 = getRandomNumber(10);
	pos1++;
	int pos2 = getRandomNumber(pos1);
	pos2++;
	for (int i = 1; i <= 4; i++) {
		printf("Barco %d\nX: ", i);
		int x = getnum();
		printf("%d\nY: ", x);
		int y = getnum();
		printf("%d\n", y);
		game_map[1][y][x] = SHIP_IA;
		for (int p = 0; p < (i+1); p++) {
			if (x+p <= 9) {
				game_map[1][y][x+p] = SHIP_IA;
			}
		}
		x -= pos1;
		y -= pos2;
		if (x < 0) {
			x *= -1;
		}
		if (y < 0) {
			y *= -1;
		}
		game_map[0][x][y] = UNKOWN_SHIP;
		for (int p = 0; p < (i+1); p++) {
			if (y+p <= 9) {
				game_map[0][x][y+p] = UNKOWN_SHIP;
			}
		}
	}
}

int sw()
{
	put_ship_on_map();
	print_map();
	return EXIT_SUCCESS;
}

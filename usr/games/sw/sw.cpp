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
#include <time.h>
#include "sw.h"
#include "sw_colors.h"

#define UNKOWN_WATER 0
#define WATER_IA 1
#define WATER 2
#define UNKOWN_SHIP 3
#define SHIP_IA 4
#define SHIP 5

#define WIN 0
#define LOSE 1
#define PLAYING 2
#define EXIT_SW 3
#define EQUAL 4

#define ONE_PLAYER 0
#define MULTI_PLAYER 1

int game_map[2][10][10];

int getnum()
{
	int n = 0;
	char c = getchar();
	if (c >= '0' && c <= '9') {
		n = c - '0';
	}
	else if (c == 'e') {
		n = -1;
	}
	return n;
}

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

void put_ship_on_map(int mode)
{
	int pos1, pos2;
	if (mode == ONE_PLAYER) {
		for (int i = 0; i < 10; i++) {
			for (int x = 0; x < 10; x++) {
				game_map[1][i][x] = WATER_IA;
			}
		}
		srandom(time(NULL));
		pos1 = random() % 10;
		pos1++;
		srandom(time(NULL));
		pos2 = random() % pos1;
		pos2++;
	}
	for (int z = 0; z <= 1; z++) {
		clear_window();
		if (mode == ONE_PLAYER && z == 0) {
			continue;
		}
		for (int i = 1; i <= 4; i++) {
			printf("Barco %d\nX: ", i);
			int x = getnum();
			printf("%d\nY: ", x);
			int y = getnum();
			printf("%d\n", y);
			char option;
			do {
				printf("Horizontal o Vertical (h/v): ");
				option = getchar();
				printf("%c\n", option);
			} while(option != 'h' && option != 'v');
			game_map[z][y][x] = SHIP_IA;
			if (mode == ONE_PLAYER) {
				for (int p = 0; p < (i+1); p++) {
					if (x+p <= 9 && option == 'h') {
						game_map[z][y][x+p] = SHIP_IA;
					}
					if (y+p <= 9 && option == 'v') {
						game_map[z][y+p][x] = SHIP_IA;
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
			else if (mode == MULTI_PLAYER) {
				for (int p = 0; p < (i+1); p++) {
					if (x+p <= 9 && option == 'h') {
						game_map[z][y][x+p] = UNKOWN_SHIP;
					}
					if (y+p <= 9 && option == 'v') {
						game_map[z][y+p][x] = UNKOWN_SHIP;
					}
				}
			}
		}
	}
}

int CheckGameStatus()
{
	int current_state = PLAYING;
	int ship_count = 0;
	int ship_ia_count = 0;
	for (int x = 0; x < 10; x++) {
		for (int y = 0; y < 10; y++) {
			if (game_map[0][x][y] == UNKOWN_SHIP) {
				ship_count++;
			}
			if (game_map[1][x][y] == SHIP_IA || game_map[1][x][y] == UNKOWN_SHIP) {
				ship_ia_count++;
			}
		}
	}
	if (ship_count == 0) {
		current_state = WIN;
	}
	if (ship_ia_count == 0) {
		current_state = LOSE;
	}
	if (ship_count == ship_ia_count && ship_count == 0) {
		current_state = EQUAL;
	}
	return current_state;
}

int sw(int mode)
{
	clear_window();
	int result = EXIT_SUCCESS;
	put_ship_on_map(mode);
	short int x = 0;
	short int y = 0;
	int state = PLAYING;
	while (state == PLAYING) {
		print_map();
		printf("Pulse 'e' para cerrar Sea War.\nX: ");
		x = getnum();
		printf("%d\nY: ", x);
		y = getnum();
		printf("%d\n", y);
		if (x < 0 || y < 0) {
			state = EXIT_SW;
		}
		if (game_map[0][y][x] == UNKOWN_WATER || game_map[0][y][x] == UNKOWN_SHIP) {
			game_map[0][y][x]++;
			game_map[0][y][x]++;
		}
		if (mode == ONE_PLAYER) {
			srandom(time(NULL));
			x = random() % 10;
			srandom(time(NULL));
			y = random() % 10;
			if (game_map[1][x][y] != WATER && game_map[1][x][y] != SHIP) {
				game_map[1][x][y]++;
			}
			else {
				for (x = 0, y = 0; game_map[1][y][x] == WATER || game_map[1][y][x] == SHIP; x++) {
					if (x == 9) {
						x = 0;
						y++;
					}
				}
				game_map[1][y][x]++;
			}
		}
		else if (mode == MULTI_PLAYER) {
			printf("Player 2\nX: ");
			x = getnum();
			printf("%d\nY: ", x);
			y = getnum();
			printf("%d\n", y);
			if (x < 0 || y < 0) {
				state = EXIT_SW;
			}
			if (game_map[1][y][x] == UNKOWN_WATER || game_map[1][y][x] == UNKOWN_SHIP) {
				game_map[1][y][x]++;
				game_map[1][y][x]++;
			}
		}
		if (state != EXIT_SW) {
			state = CheckGameStatus();
		}
	}
	print_map();
	switch (state) {
		case WIN:
			printf("La flota enemiga ha sido destruida.\n");
			break;
		case LOSE:
			printf("La flota aliada ha sido destruida.\n");
			break;
		case EXIT_SW:
			printf("Cerrando Sea War.\n");
			break;
		case EQUAL:
			printf("Las dos flotas han sido destruidas. [EMPATE]\n");
			break;
		default:
			printf("Sea War Error.\n");
			result = EXIT_FAILURE;
			break;
	}
	return result;
}

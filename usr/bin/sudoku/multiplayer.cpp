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
#include "gamemodes.h"
#include "sudoku.h"
#include "multiplayer.h"

#define COMPETITION_EASY 2
#define COMPETITION_DIFF 3

void multiplayer_mode()
{
	char player[2][12];
	do {
		printf("Nombre del Player 1: ");
		gets_s(player[0], 12);
		printf("Nombre del Player 2: ");
		gets_s(player[1], 12);
	} while ((strcmp(player[0], player[1])) == 0);
	int points[2] = {0,0};
	int points_now = 0;
	int mode = COMPETITION_EASY;
	/* multiplayer main */
	for (int i = 1; i <= 5; i++) {
		for (int k = 0; k <= 1; k++) {
			clear_window();
			printf("Es el turno de %s\n", player[k]);
			do {
				printf("Sudoku Facil [2] o Sudoku Dificil [3]\n");
				mode = getnum();
			} while (mode != 2 && mode != 3);
			points_now = sudoku(mode);
			points[k] = points[k] + points_now;
		}
		clear_window();
		printf("Clasificacion: \n");
		printf("----------------------\n");
		printf("%s | %d puntos\n", player[0], points[0]);
		printf("%s | %d puntos\n", player[1], points[1]);
		if (i < 5) {
			printf("Pulsa una tecla\n");
			getchar();
		}
		else {
			printf("Juego terminado\n");
			if (points[0] != points[1]) {
				printf("Ha ganado ");
				if (points[0] > points[1]) {
					printf("%s con %d puntos\n", player[0], points[0]);
				}
				else {
					printf("%s con %d puntos\n", player[1], points[1]);
				}
			}
			else {
				printf("Empate a %d puntos\n", points[0]);
			}
			printf("Pulsa una tecla\n");
			getchar();
		}
	}
}

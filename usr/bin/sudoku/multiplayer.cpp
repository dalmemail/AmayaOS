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

int multiplayer_mode()
{
	printf("Introduce el numero de jugadores: ");
	int player_num = getnum();
	if (player_num < 2 || player_num > 9) {
		player_num = 2;
	}
	printf("%d\n", player_num);
	char player[player_num][12];
	for (int i = 0; i < player_num; i++) {
		printf("Nombre del Player %d: ", i+1);
		gets_s(player[i], 12);
	}
	/* two players can't have the same name */
	for (int i = 0; i < player_num; i++) {
		for (int v = 0; v < player_num; v++) {
			if ((strcmp(player[i], player[v])) == 0 && i != v) {
				printf("Error: player %d y player %d se llaman %s\n", i+1, v+1, player[i]);
				printf("Pulsa una tecla para continuar\n");
				getchar();
				return 0;
			}
		}
	}
	int points[player_num];
	/* all start points = 0 */
	for (int i = 0; i < player_num; i++) {
		points[i] = 0;
	}
	int points_now = 0;
	int mode = COMPETITION_EASY;
	printf("Numero de turnos: ");
	int n_games = getnum();
	if (n_games < 1 && n_games > 9) {
		n_games = 5;
	}
	printf("%d\n", n_games);
	/* multiplayer main */
	for (int i = 1; i <= n_games; i++) {
		for (int k = 0; k < player_num; k++) {
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
		for (int x = 0; x < player_num; x++) {
			printf("%s | %d puntos\n", player[x], points[x]);
		}
		if (i < n_games) {
			printf("Pulsa una tecla\n");
			getchar();
		}
		else {
			printf("Juego terminado\n");
			/* position of winner on array */
			int pos = 0;
			int best_point = 0;
			int wl = 0;
			for (int b = 0; b < player_num; b++) {
				if (points[b] > best_point) {
					best_point = points[b];
					pos = b;
				}
			}
			for (int b = 0; b < player_num; b++) {
				if (points[b] == best_point) {
					wl++;
				}
			}
			if (wl == 1) {
				printf("Ha ganado %s con %d puntos\n", player[pos], points[pos]);
			}
			else {
				printf("Empate a %d puntos\n", points[pos]);
			}
			printf("Pulsa una tecla\n");
			getchar();
		}
	}
	return 0;
}

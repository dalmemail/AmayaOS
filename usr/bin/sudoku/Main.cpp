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
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include "gamemodes.h"
#include "sudoku.h"
#include "multiplayer.h"

#define EASY 0
#define DIFFICULT 1

#define VERSION "0.5.1.1"

int main(int argc, char **argv)
{
	int c = 1;
	while (c != 4) {
		clear_window();
		printf("=== SUDOku v%s ===\n", VERSION);
		printf("[1] Modo facil [4X4]\n");
		printf("[2] Modo dificil [4X4]\n");
		printf("[3] Modo campeonato [MULTIPLAYER]\n");
		printf("[4] Salir de SUDOku\n");
		printf("Selecciona una opcion: ");
		c = getnum();
		printf("%c\n", c);
		switch (c) {
			case 1:
				sudoku(EASY);
				break;
			case 2:
				sudoku(DIFFICULT);
				break;
			case 3:
				multiplayer_mode();
				break;
		}
	}
	return 0;
}

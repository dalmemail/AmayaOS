/*
 * Copyright (C) 2015 Dan Rulos.
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
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <amaya.h>
#include "calculator.h"

#define VERSION "0.5.2"

/* main function */
int main(int argc, char **argv)
{
	/* declaramos variables */
	char option='s';
	while(1) {
		/* clean screen */
		clean_calc();
		/* mostramos el menú */
		printf("CALC %s\r\n", VERSION);
		printf("[1] Sumar\r\n");
		printf("[2] Restar\r\n");
		printf("[3] Multiplicar\r\n");
		printf("[4] Dividir\r\n");
		printf("[5] Conversor de temperaturas\n");
		printf("[S] Salir\r\n");
		printf("Seleccione una opcion: ");
		option = getchar();
		/* you can do different things */
		switch (option) {
			case '1':
				clean_calc();
				calculator(0);
				break;
			case '2':
				clean_calc();
				calculator(1);
				break;
			case '3':
				clean_calc();
				calculator(2);
				break;
			case '4':
				clean_calc();
				calculator(3);
				break;
			case '5':
				clean_calc();
				temp();
				break;
			case 's':
			case 'S':
				clean_calc();
				return 0;
				break;
			/* si no es ninguna de las anteriores */
			default:
				clean_calc();
				printf("Error: Orden no encontrada\n");
				pause();
		}
	}
}

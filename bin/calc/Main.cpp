/*
 * Copyright (C) 2016 Dan Rulos.
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
#include <string.h>
#include "calculator.h"

#define VERSION "0.9.6.1"

/* main function */
int main(int argc, char **argv)
{
	int i = 0;
	double decimal_n;
	char decimal_array[16];
	int ret = EXIT_SUCCESS;
	if (argc == 2 && (strcmp(argv[1], "--version")) == 0) {
		printf("Version: %s\n", VERSION);
	}
	else if (argc >= 3 && (strcmp(argv[1], "--squareroot")) == 0) {
		for (i = 2; i < argc; i++) {
			if (argv[i][0] == '-') {
				printf("Error: %s no tiene raices conocidas.\n", argv[i]);
			}
			else {
				decimal_n = atof(argv[i]);
				ftoa(decimal_array, root(decimal_n, 2));
				printf("%s\n", decimal_array);
			}
		}
	}
	else if (argc == 4 && (strcmp(argv[1], "--root")) == 0) {
			if (argv[3][0] == '-' && atoi(argv[2]) % 2 == 0) {
				printf("Math Error\n");
			}
			else if (atoi(argv[2]) == 0) {
				printf("Math Error\n");
			}
			else {
				decimal_n = atof(argv[3]);
				if (atoi(argv[2]) < 0) {
					int n = -atoi(argv[2]);
					ftoa(decimal_array, 1 / root(decimal_n, n));
				}
				else {
					ftoa(decimal_array, root(decimal_n, atoi(argv[2])));
				}
				printf("%s\n", decimal_array);
			}
	}
	else if (argc == 4 && (strcmp(argv[1], "--power")) == 0) {
		decimal_n = 1.0;
		int exponente = atoi(argv[3]);
		bool negative = false;
		if (exponente < 0) {
			exponente *= -1;
			negative = true;
		}
		if (exponente > 0) {
			for (i = 1; i <= exponente; i++) {
				decimal_n *= atof(argv[2]);
			}
		}
		if (negative) {
			decimal_n = 1 / decimal_n;
		}
		ftoa(decimal_array, decimal_n);
		if (decimal_array[0] == '-' && atof(argv[2]) > 0.0) {
			printf("%s: error de calculo\n", argv[0]);
		}
		else if (exponente == 0 && atof(argv[2]) == 0) {
			printf("Math Error\n");
		}
		else {
			printf("%s\n", decimal_array);
		}
	}
	else if (argc < 4) {
		printf("%s v%s Ayuda\n", argv[0], VERSION);
		printf("Operaciones Simples: %s num1 operator1 num2 operator2 num3 ...\n", argv[0]);
		printf("Raices Cuadradas: %s --squareroot num1 num2 ...\n", argv[0]);
		printf("Raices: %s --root superindice base\n", argv[0]);
		printf("Potencias: %s --power base exponente\n", argv[0]);
		ret = EXIT_FAILURE;
	}
	else if (argc >= 4) {
		double result = atof(argv[1]);
		i = 2;
		do {
			result = calculator(result, argv[i][0], atof(argv[i+1]));
		} while((i += 2)+1 < argc);
		ftoa(decimal_array,result);
		printf("%s\n", decimal_array);
	}
	return ret;
}

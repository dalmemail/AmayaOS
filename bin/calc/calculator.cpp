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
#include <string.h>
#include <amaya.h>
#include "calculator.h"

/* clean the screen */
void clean_calc()
{
	char str[] = {0x1b, 0x5b, 0x48, 0x1b, 0x5b, 0x4a, '\0'};
	printf("%s", str);
}

/* check if n is a number */
bool numberinchar(char *n)
{
	for (unsigned int i=0; i <= (strlen(n)-1); i++) {
		if (n[i] != '0' && n[i] != '1' && n[i] != '2' && n[i] != '3' && n[i] != '4' && n[i] != '5' && n[i] != '6'&&
		    n[i] != '7' && n[i] != '8' && n[i] != '9' && n[0] != '-') {
			return false;
		}
	}
	return true;
}

/* do operations */
int calculator(unsigned int operation)
{
	int res = 0;
	char n1[8];
	char n2[8];
	printf("Numero 1: ");
	gets_s(n1, 8);
	printf("Numero 2: ");
	gets_s(n2, 8);
	switch (operation) {
		case 0:
			res = atoi(n1) + atoi(n2);
			break;
		case 1:
			res = atoi(n1) - atoi(n2);
			break;
		case 2:
			res = atoi(n1) * atoi(n2);
			break;
		case 3:
			res = atoi(n1) / atoi(n2);
			break;
		default:
			clean_calc();
			printf("Se ha producido un error: Operacion no reconocida\n");
			pause();
			return -1;
	}
	printf("Resultado: %d\n", res);
	pause();
	return 0;
}

/*convert temperatures (original from calc v0.5) */
int temp()
{
	char value = 's';
	char input[8];
	int resc = 0;
	printf("Conversor de temperaturas\n");
	printf("[1] Celius --> Fahrenheit\n");
	printf("[2] Fahrenheit --> Celsius\n");
	printf("[3] Kelvin --> Celsius\n");
	printf("[4] Kelvin --> Fahrenheit\n");
	printf("[5] Celsius --> Kelvin\n");
	printf("[6] Fahrenheit --> Kelvin\n");
	printf("[S] Cerrar el conversor\n");
	value = getchar();
	clean_calc();
	if (value == 's' || value == 'S') {
		return 0;
	}
	printf("Valor a convertir: ");
	gets_s(input, 8);
	clean_calc();
	switch(value) {
		case '1':
			resc = 9 * atoi(input) / 5 + 32;
			printf("Celsius: %6d Fahrenheit: %6d\n", atoi(input), resc);
			break;
		case '2':
			resc = 5 * (atoi(input)-32) / 9;
			printf("Fahrenheit: %6d Celsius: %6d\n", atoi(input), resc);
			break;
		case '3':
			resc = atoi(input) - 273;
			printf("Kelvin: %6d Celsius: %6d\n", atoi(input), resc);
			break;
		case '4':
			/* primero convertimos a celsius */
			resc = atoi(input) - 273;
			resc = 9 * resc / 5 + 32;
			printf("Kelvin: %6d Fahrenheit: %6d\n", atoi(input), resc);
			break;
		case '5':
			resc = atoi(input) + 273;
			printf("Celsius: %6d Kelvin: %6d\n", atoi(input), resc);
			break;
		case '6':
			/* primero convertimos a celsius */
			resc = 5 * (atoi(input)-32) / 9;
			resc = resc + 273;
			printf("Fahrenheit: %6d Kelvin: %6d\n", atoi(input), resc);
			break;
	}
	pause();
	clean_calc();
	return 0;
}

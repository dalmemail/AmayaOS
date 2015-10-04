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
#include <math.h>
#include "calculator.h"

void ftoa(char *output, double input)
{
	char number[8];
	char pdecc[8];
	int pint = input;
	double pdec = (input - pint) * 1000000;
	itoa(number, 10, pint);
	strcat(number, ".");
	pint = pdec;
	itoa(pdecc, 10, pint);
	strcat(number, pdecc);
	strcpy(output, number);
}

/* clean the screen */
void clean_calc()
{
	char str[] = {0x1b, 0x5b, 0x48, 0x1b, 0x5b, 0x4a, '\0'};
	printf("%s", str);
}

/* do operations */
int calculator(int num1, char operation, int num2)
{
	int result;
	switch (operation) {
		case '+':
			result = num1 + num2;
			break;
		case '-':
			result = num1 - num2;
			break;
		case '*':
			result = num1 * num2;
			break;
		case '/':
			result = num1 / num2;
			break;
		case '%':
			result = num1 % num2;
			break;
		default:
			printf("error: operador %c desconocido\n", operation);
			return EXIT_FAILURE;
	}
	printf("%d\n", result);
	return result;
}

/*convert temperatures (original from calc v0.5) */
int av()
{
	char value = 's';
	char input[8];
	char exponente[8];
	int resc = 0;
	printf("Opciones avanzadas:\n");
	printf("[1] Celius --> Fahrenheit\n");
	printf("[2] Fahrenheit --> Celsius\n");
	printf("[3] Kelvin --> Celsius\n");
	printf("[4] Kelvin --> Fahrenheit\n");
	printf("[5] Celsius --> Kelvin\n");
	printf("[6] Fahrenheit --> Kelvin\n");
	printf("[7] Raices cuadradas\n");
	printf("[8] Potencias\n");
	printf("[S] Cerrar el conversor\n");
	value = getchar();
	clean_calc();
	if (value == 's' || value == 'S') {
		return 0;
	}
	if (value < '7' && value > '0') {
		printf("Valor a convertir: ");
		gets_s(input, 8);
	}
	clean_calc();
	double res;
	char result[32];
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
		case '7':
			printf("Raiz de: ");
			gets_s(input, 8);
			res = sqrt(atof(input));
			ftoa(result, res);
			printf("%s\n", result);
			break;
		case '8':
			printf("Base: ");
			gets_s(input, 8);
			printf("Exponente: ");
			gets_s(exponente, 8);
			res = pow(atof(input), atof(exponente));
			ftoa(result, res);
			printf("%s\n", result);
			break;
	}
	return 0;
}

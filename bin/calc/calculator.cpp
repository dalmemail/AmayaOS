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

void ftoa(char r[16], double input)
{
	char number[16];
	char pdecc[16];
	int pint = input;
	double pdec = (input - pint) * 1000000;
	double dec_part = input - pint;
	if (pdec < 0) {
		pdec *= -1;
		dec_part *= -1;
		if (pint >= 0) {
			printf("-");
		}
	}
	itoa(number, 10, pint);
	strcat(number, ".");
	int times = 0;
	double mod = 0.1;
	while (mod > dec_part && mod > 0.000001) {
		times++;
		mod /= 10;
	}
	for (int i = 0; i < times; i++) {
		strcat(number, "0");
	}
	pint = pdec;
	itoa(pdecc, 10, pint);
	strcat(number, pdecc);
	strcpy(r, number);
}

/* do operations */
double calculator(double num1, char operation, double num2)
{
	double result = 0;
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
			if (num2 != 0) {
				result = num1 / num2;
			}
			break;
		default:
			printf("error: operador %c desconocido\n", operation);
			return EXIT_FAILURE;
	}
	return result;
}

double mkpower(double c, int superindice)
{
	double res = c;
	for (int i = 1; i < superindice; i++) {
		res *= c;
	}
	return res;
}

double negative_root(double base, int superindice)
{
	double c = 0, mod = 1;

	int i = 0;
	do {
		c -= mod;
		if(mkpower(c, superindice) < base)
		{
			c += mod;
			mod /= 10;
		}
		if (mod <= 0.000001) {
			i++;
		}
	} while (mkpower(c, superindice) != base && i <= 10);

	return c;
}

double root(double base, int superindice)
{
	double c = 0, mod = 1;

	if(base < 0)
	{
		return negative_root(base, superindice);
	}
	if (base == 0) {
		return 0;
	}

	int i = 0;
	do {
		c += mod;
		if(mkpower(c, superindice) > base)
		{
			c -= mod;
			mod /= 10;
		}
		if (mod <= 0.000001) {
			i++;
		}
	} while (mkpower(c, superindice) != base && i <= 10);

	return c;
}

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

/* limpia la pantalla */
void clean_calc()
{
	char str[] = {0x1b, 0x5b, 0x48, 0x1b, 0x5b, 0x4a, '\0'};
	printf("%s", str);
}

/* comprueba si un *char es un numero */
bool numberinchar(char *n)
{
	for (int i=0; i <= (strlen(n)-1); i++) {
		if (n[i] != '0' && n[i] != '1' && n[i] != '2' && n[i] != '3' && n[i] != '4' && n[i] != '5' && n[i] != '6'&&
		    n[i] != '7' && n[i] != '8' && n[i] != '9' && n[0] != '-') {
			return false;
		}
	}
	return true;
}

/* suma dos numeros */
void sumar()
{
	int resultado_sum=0;
	char n1_sum[128];
	char n2_sum[128];
	printf("Sumar\r\n");
	printf("Introduce numero 1 : ");
	gets_s(n1_sum, 128); /* Pedimos al usuario numero1 */
	printf("Introduce numero 2 : ");
	gets_s(n2_sum, 128); /* Pedimos al usuario numero2 */
	if (numberinchar(n1_sum) && numberinchar(n2_sum)) {
		resultado_sum = atoi(n1_sum) + atoi(n2_sum);
		printf("El resultado es : %d\n", resultado_sum);
	}
	else {
		printf("Error: Introduce solo numeros.\n");
	}
	pause();
}

/* resta dos numeros */
void restar()
{
	int resultado_res=0;
	char n1_res[128];
	char n2_res[128];
	printf("Restar\r\n");
	printf("Introduce numero 1 : ");
	gets_s(n1_res, 128); /* Pedimos al usuario numero1 */
	printf("Introduce numero 2 : ");
	gets_s(n2_res, 128); /* Pedimos al usuario numero2 */
	if (numberinchar(n1_res) && numberinchar(n2_res)) {
		resultado_res = atoi(n1_res) - atoi(n2_res);
		printf("El resultado es : %d\n", resultado_res);
	}
	else {
		printf("Error: Introduce solo numeros.\n");
	}
	pause();
}

/* multiplica dos numeros */
void multiplicar()
{
	int resultado_mul=0;
	char n1_mul[128];
	char n2_mul[128];
	printf("Multiplicar\r\n");
	printf("Introduce numero 1 : ");
	gets_s(n1_mul, 128); /* Pedimos al usuario numero1 */
	printf("Introduce numero 2 : ");
	gets_s(n2_mul, 128); /* Pedimos al usuario numero2 */
	if (numberinchar(n1_mul) && numberinchar(n2_mul)) {
		resultado_mul = atoi(n1_mul) * atoi(n2_mul);
		printf("El resultado es : %d\n", resultado_mul);
	}
	else {
		printf("Error: Introduce solo numeros.\n");
	}
	pause();
}

/* divide dos numeros */
void dividir()
{
	int resultado_div=0;
	char n1_div[128];
	char n2_div[128];
	printf("Sumar\r\n");
	printf("Introduce numero 1 : ");
	gets_s(n1_div, 128); /* Pedimos al usuario numero1 */
	printf("Introduce numero 2 : ");
	gets_s(n2_div, 128); /* Pedimos al usuario numero2 */
	if (numberinchar(n1_div) && numberinchar(n2_div)) {
		resultado_div = atoi(n1_div) / atoi(n2_div);
		printf("El resultado es : %d\n", resultado_div);
	}
	else {
		printf("Error: Introduce solo numeros.\n");
	}
	pause();
}

/* función principal */
int main(int argc, char **argv)
{
	/* declaramos variables */
	char option='s';
	while(1) {
		/* limpiamos la pantalla */
		clean_calc();
		/* mostramos el menú */
		printf("CALC 0.4\r\n");
		printf("[1] Sumar\r\n");
		printf("[2] Restar\r\n");
		printf("[3] Multiplicar\r\n");
		printf("[4] Dividir\r\n");
		printf("[S] Salir\r\n");
		printf("Seleccione una opcion: \n");
		option = getchar();
		/* diferentes opciones */
		switch (option) {
			case '1':
				clean_calc();
				sumar();
				break;
			case '2':
				clean_calc();
				restar();
				break;
			case '3':
				clean_calc();
				multiplicar();
				break;
			case '4':
				clean_calc();
				dividir();
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

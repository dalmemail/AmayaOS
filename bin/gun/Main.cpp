/*
 * Copyright (C) 2015 Alvaro Stagg, 2015 Dan Rulos
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
#include <amaya.h>
#include <files.h>
#include "gun.h"

void limpiar();
void menu();
int juego();
void ayuda();

int main(int argc, char* argv[])
{
    /*Limpiamos la pantalla*/
    limpiar();

    /*MENU*/
    menu();

    return 0;
}

void limpiar()
{
    /*Limpiamos la pantalla*/
    char str[] = {0x1b, 0x5b, 0x48, 0x1b, 0x5b, 0x4a, '\0'};
    printf("%s", str);
}

void menu()
{
    char seleccion = '0';

    printf("=== ADIVINANDO 0.2 ===\n");
    printf("     === MENU ===\n\n");
    printf("1. Jugar\n");
    printf("2. Ayuda\n");
    printf("3. Salir\n\n");

    printf("Tu seleccion: ");
    seleccion = getchar();
    putchar(seleccion);

    if(seleccion == '1')
    {
    	juego();
    }
    else if(seleccion == '2')
    {
    	ayuda();
    }
    else if(seleccion == '3')
    {
        /*Adios !*/
        limpiar();
    	printf("Bye !\n");
    }
    else /*El juego se puede volver "Loco" y puede crashear...*/
    {
    	limpiar();
    	printf("Por favor, elija una opcion valida...\n\n");
	pause();
	limpiar();
    	menu();
    }
}

int juego()
{
    /*Generamos el numero misterioso*/
    int numero = aleatorio();
    int intentos = 0;

    char talvezs[128];
    int talvez = 0;
    char qidn;
    int np_1 = numero - num1(1);
    int np_2 = numero + num1(2);


    if (np_1 < 0) {
	np_1 = 0;
    }
    if (np_2 > 100) {
	np_2 = 100;
    }

    do
    {
        limpiar();
        printf("Has hecho %d intentos.\n", intentos);
        printf("El numero misterioso esta entre %d y %d.\n\n", np_1, np_2);
	printf("Escribe 'e' para cerrar\n");

        printf("Tu propuesta: ");
	/* gets_s() es un fork de gets() que arregla sus fallos de seguridad */
        gets_s(talvezs, 128);
	if (talvezs[0] == 'e') {
	  limpiar();
    	  printf("Bye !\n");
	  return 0;
	}
	talvez = atoi(talvezs);
	

        intentos = intentos + 1;
    }while(talvez != numero);

    /*Adivino el numero !*/

    limpiar();
    printf("=== FELICIDADES ===\n");
    printf("  === GANASTE ===\n\n");
    printf("El numero era: %d\n\n", numero);
    printf("Lo intentaste: %d veces\n", intentos);
    printf("Quieres volver a jugar ? (S/n): ");
    qidn = getchar();
    putchar(qidn);

    if(qidn == 'S' || qidn == 's')
    {
        limpiar();
        juego();
    }
    else if(qidn == 'N' || qidn == 'n')
    {
        limpiar();
        menu();
    }
    else
    {
        limpiar();
        menu();
    }
    return 0;
}

void ayuda()
{
	limpiar();

	char op;
	printf("=== AYUDA ===\n");
	printf("Hola, en el siguiente juego tendras que adivinar un numero\na partir de una serie de pistas que se te iran dando a\nmedida que vayas digitando tu opcion.\n\n");
	printf("Entendiste (S/n) ?: ");
	op = getchar();
	putchar(op);

	if(op == 'S' || op == 's')
	{
		limpiar();
		menu();
	}
	else if(op == 'N' || op == 'n')
	{
		limpiar();
		printf("Lee bien... Si tienes alguna duda puedes\ncontactarme a traves de mi E-mail: alvarostagg@openmailbox.org\n\n");
		pause();
		ayuda();
	}
}

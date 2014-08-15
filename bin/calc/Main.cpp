/*
 * Copyright (C) 2014 Dan Rulos.
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

int getnum() /* Funcion para obtener los numeros */
{
    static int ch[1024]; /* Creamos un espacio en la memoria para trabajar con ellos */
    read(0, ch, 1); /* Leemos (read) del teclado, en la variable ch 1 caracter. */
    
    return ch[0];
}

int putnum(int ch) /* Para colocar los numeros en la pantalla */
{
    printf("%d", ch); /* Utilizamos "%d" para colocar variables de tipo int */
    return ch;
}

int main(int argc, char **argv) /* Funcion principal de la calculadora */
{
    char opcion='I'; /* Importante colocar opciones por defecto I, 0, etc Asi si el usuario pulsa enter el programa no se quedará colgado */
    int numero1=0;
    int numero2=0;
    int resultado=0;
    int resultado1=0;
    printf("CALC 0.1\r\n");
    printf("[1] Sumar\r\n");
    printf("[2] Restar\r\n");
    printf("[I] Info\r\n");
    printf("[S] Salir\r\n");
    do { /* Bucle do while */
      printf("Selecione una opcion:\r\n");
      opcion = getchar();
    } while (opcion != '1'&& opcion != '2'&& opcion != 'I'&& opcion != 'S'&& opcion != 'i'&& opcion != 's'); /* Si el usuario no introduce
     * 1, 2, I, S, i o s no continua */
    if (opcion == 'I'|| opcion == 'i') { /* Si la opcion es I o i */
      printf("CALC 0.1 corriendo sobre AmayaOS\r\n");
      printf("CALC es free software | GNU GPL v3\r\n");
      printf("CALC viene sin NINGUNA GARANTIA\r\n");
      pause();
      main(argc, argv); /* Volvemos a ejecutar la funcion principal */
    }
    if (opcion == 'S'|| opcion == 's') { /* Si la opcion es S o s */
      return EXIT_SUCCESS; /* Cerramos el programa */
    }
    if (opcion == '1') { /* Si es 1 sumamos */
      printf("\r\n", "Sumar\r\n");
      printf("Introduce numero 1 : \r\n");
      numero1 = getnum(); /* Pedimos al usuario numero1 */
      printf("Introduce numero 2 : \r\n");
      numero2 = getnum(); /* Pedimos al usuario numero2 */
      resultado = numero1 + numero2; /* Sumamos.... */
      resultado1 = resultado - 96; /* Restamos 96 para dejar el resultado correcto */
      printf("El resultado es : ");
      putnum(resultado1);
      printf("\r\n");
    }
    if (opcion == '2') { /* Si es 2 restamos */
      printf("\r\n", "Restar\r\n");
      printf("Introduce numero 1 : \r\n");
      numero1 = getnum(); /* numero1 */
      printf("Introduce numero 2 : \r\n");
      numero2 = getnum(); /* numero2 */
      resultado = numero1 - numero2;
      printf("El resultado es : ");
      putnum(resultado);
      printf("\r\n");
    }
}

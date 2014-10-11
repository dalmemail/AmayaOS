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


int main(int argc, char **argv) /* Funcion principal de la calculadora */
{
    char opcion='I'; /* Importante colocar opciones por defecto I, 0, etc Asi si el usuario pulsa enter el programa no se quedará colgado */
    char numero1[128];
    char numero2[128];
    int resultado=0;
    printf("CALC 0.2\r\n");
    printf("[1] Sumar\r\n");
    printf("[2] Restar\r\n");
    printf("[3] Multiplicar\r\n");
    printf("[4] Dividir\r\n");
    printf("[I] Info\r\n");
    printf("[S] Salir\r\n");
    do { /* Bucle do while */
      printf("Selecione una opcion:\r\n");
      opcion = getchar();
    } while (opcion != '1'&& opcion != '2'&& opcion != 'I'&& opcion != 'S'&& opcion != 'i'&& opcion != 's'&& opcion != '3'&& opcion != '4'); /* Si el usuario no introduce
     * 1, 2, I, S, i o s no continua */
    if (opcion == 'I'|| opcion == 'i') { /* Si la opcion es I o i */
      printf("CALC 0.3 corriendo sobre AmayaOS\r\n");
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
      printf("Introduce numero 1 : ");
      gets_s(numero1, 128); /* Pedimos al usuario numero1 */
      printf("Introduce numero 2 : ");
      gets_s(numero2, 128); /* Pedimos al usuario numero2 */
      resultado = atoi(numero1) + atoi(numero2); /* Sumamos.... */
      printf("El resultado es : ");
      printf("%d", resultado);
      printf("\r\n");
    }
    if (opcion == '2') { /* Si es 2 restamos */
      printf("\r\n", "Restar\r\n");
      printf("Introduce numero 1 : ");
      gets_s(numero1, 128); /* numero1 */
      printf("Introduce numero 2 : ");
      gets_s(numero2, 128); /* numero2 */
      resultado = atoi(numero1) - atoi(numero2);
      printf("El resultado es : ");
      printf("%d", resultado);
      printf("\r\n");
    }
    if (opcion == '3') { /* Si es 1 sumamos */
      printf("\r\n", "Multiplicar\r\n");
      printf("Introduce numero 1 : ");
      gets_s(numero1, 128); /* Pedimos al usuario numero1 */
      printf("Introduce numero 2 : ");
      gets_s(numero2, 128); /* Pedimos al usuario numero2 */
      resultado = atoi(numero1) * atoi(numero2); /* Sumamos.... */
      printf("El resultado es : ");
      printf("%d", resultado);
      printf("\r\n");
    }
    if (opcion == '4') { /* Si es 1 sumamos */
      printf("\r\n", "Dividir\r\n");
      printf("Introduce numero 1 : ");
      gets_s(numero1, 128); /* Pedimos al usuario numero1 */
      printf("Introduce numero 2 : ");
      gets_s(numero2, 128); /* Pedimos al usuario numero2 */
      resultado = atoi(numero1) / atoi(numero2); /* Sumamos.... */
      printf("El resultado es : ");
      printf("%d", resultado);
      printf("\r\n");
    }
}

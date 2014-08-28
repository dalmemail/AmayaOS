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
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

int nivel2() /* Nivel 2 Sudoku 0.2 */
{
    char x1;
    char x2;
    char x3;
    char x4;
    char x5;
    char x6;
    char x7;
    char x8;
    char x9;
    char x10;
    char x11;
    char x12;
    char x13;
    char x14;
    char x15;
    char x16;
    char x17;
    char x18;
    char x19;
    char x20;
    char x21;
    char x22;
    char x23;
    char x24;
    char x25;
    char roc;
    printf("SUDOku 0.2\r\n");
    printf("\r\n");
    printf("___________________\r\n");
    printf("|5|4|X|9|1|X|2|3|X|\r\n");
    printf("|X|X|3|2|8|X|6|7|X|\r\n");
    printf("|6|X|8|X|5|3|X|9|1|\r\n");
    printf("|X|5|9|X|2|X|7|8|6|\r\n");
    printf("|4|6|2|5|7|X|X|X|3|\r\n");
    printf("|8|X|1|6|3|9|5|X|4|\r\n");
    printf("|9|1|6|8|4|7|X|X|X|\r\n");
    printf("|7|3|5|X|6|2|8|4|9|\r\n");
    printf("|X|8|4|3|X|5|1|X|7|\r\n");
    printf("\r\n");
    printf("Introduce la solucion a la X1:\r\n");
    x1 = getchar(); /* Dime las soluciones */
    printf("Introduce la solucion a la X2:\r\n");
    x2 = getchar();
    printf("Introduce la solucion a la X3:\r\n");
    x3 = getchar();
    printf("Introduce la solucion a la X4:\r\n");
    x4 = getchar();
    printf("Introduce la solucion a la X5:\r\n");
    x5 = getchar();
    printf("Introduce la solucion a la X6:\r\n");
    x6 = getchar();
    printf("Introduce la solucion a la X7:\r\n");
    x7 = getchar();
    printf("Introduce la solucion a la X8:\r\n");
    x8 = getchar();
    printf("___________________\r\n");
    printf("|5|4|X|9|1|X|2|3|X|\r\n");
    printf("|X|X|3|2|8|X|6|7|X|\r\n");
    printf("|6|X|8|X|5|3|X|9|1|\r\n");
    printf("|X|5|9|X|2|X|7|8|6|\r\n");
    printf("|4|6|2|5|7|X|X|X|3|\r\n");
    printf("|8|X|1|6|3|9|5|X|4|\r\n");
    printf("|9|1|6|8|4|7|X|X|X|\r\n");
    printf("|7|3|5|X|6|2|8|4|9|\r\n");
    printf("|X|8|4|3|X|5|1|X|7|\r\n");
    printf("Introduce la solucion a la X9:\r\n");
    x9 = getchar();
    printf("Introduce la solucion a la X10:\r\n");
    x10 = getchar();
    printf("Introduce la solucion a la X11:\r\n");
    x11 = getchar();
    printf("Introduce la solucion a la X12:\r\n");
    x12 = getchar();
    printf("Introduce la solucion a la X13:\r\n");
    x13 = getchar();
    printf("Introduce la solucion a la X14:\r\n");
    x14 = getchar();
    printf("Introduce la solucion a la X15:\r\n");
    x15 = getchar();
    printf("Introduce la solucion a la X16:\r\n");
    x16 = getchar();
    printf("Introduce la solucion a la X17:\r\n");
    x17 = getchar();
    printf("___________________\r\n");
    printf("|5|4|X|9|1|X|2|3|X|\r\n");
    printf("|X|X|3|2|8|X|6|7|X|\r\n");
    printf("|6|X|8|X|5|3|X|9|1|\r\n");
    printf("|X|5|9|X|2|X|7|8|6|\r\n");
    printf("|4|6|2|5|7|X|X|X|3|\r\n");
    printf("|8|X|1|6|3|9|5|X|4|\r\n");
    printf("|9|1|6|8|4|7|X|X|X|\r\n");
    printf("|7|3|5|X|6|2|8|4|9|\r\n");
    printf("|X|8|4|3|X|5|1|X|7|\r\n");
    printf("Introduce la solucion a la X18:\r\n");
    x18 = getchar();
    printf("Introduce la solucion a la X19:\r\n");
    x19 = getchar();
    printf("Introduce la solucion a la X20:\r\n");
    x20 = getchar();
    printf("Introduce la solucion a la X21:\r\n");
    x21 = getchar();
    printf("Introduce la solucion a la X22:\r\n");
    x22 = getchar();
    printf("Introduce la solucion a la X23:\r\n");
    x23 = getchar();
    printf("Introduce la solucion a la X24:\r\n");
    x24 = getchar();
    printf("Introduce la solucion a la X25:\r\n");
    x25 = getchar();
    printf("\r\n");
    if (x1 == '7'&& x2 == '6'&& x3 == '8'&& x4 == '1'&& x5 == '9'&& x6 == '4'&& x7 == '5'&& x8 == '2'&& x9 == '7'&& x10 == '4'
      && x11 == '3'&& x12 == '4'&& x13 == '1'&& x14 == '8'&& x15 == '9'&& x16 == '1'&& x17 == '7'&& x18 == '2'&& x19 == '3'
      && x20 == '5'&& x21 == '2'&& x22 == '1'&& x23 == '2'&& x24 == '9'&& x25 == '6') { /* Si Coinciden... */
      printf("CORRECTO\r\n");
      printf("Nivel 2 Completado\r\n");
      printf("\r\n");
      printf("Juego Completo\r\n");
      return EXIT_SUCCESS; /* Salimos. Fin del juego */
    }
    if (x1 != '7'|| x2 != '6'|| x3 != '8'|| x4 != '1'|| x5 != '9'|| x6 != '4'|| x7 != '5'|| x8 != '2'|| x9 != '7'|| x10 != '4'
      || x11 != '3'|| x12 != '4'|| x13 != '1'|| x14 != '8'|| x15 != '9'|| x16 != '1'|| x17 != '7'|| x18 != '2'|| x19 != '3'
      || x20 != '5'|| x21 != '2'|| x22 != '1'|| x23 != '2'|| x24 != '9'|| x25 != '6') { /* Si una no coincide.... */
      do {
        printf("INCORRECTO\r\n"); /* NO ES CORRECTO */
        printf("Nivel 2 No completado\r\n");
        printf("[R]eintentar o [C]errar\r\n");
        roc = getchar();
      } while (roc != 'R'&& roc != 'r'&& roc != 'C'&& roc != 'c'); /* Te he dicho solo R o C, no metas ninguna letra distinta */
      if (roc == 'R'||roc == 'r') { /* Y si es R ? */
        nivel2(); /* Pues otra vez nivel2(); */
      }
      if (roc == 'C'||roc == 'c') { /* Si es C.... */
      return EXIT_SUCCESS; /* Pues salimos del juego */
      }
    }
}

int main(int argc, char **argv) /* Sudoku 0.2 */
{
    char x1;
    char x2;
    char x3;
    char x4;
    char x5;
    char x6;
    char x7;
    char x8;
    char roc;
    char noc;
    printf("SUDOku 0.2\r\n");
    printf("\r\n");
    printf("|4|X|X|1|\r\n");
    printf("|X|1|3|X|\r\n");
    printf("|X|4|1|X|\r\n");
    printf("|1|X|X|3|\r\n");
    printf("\r\n");
    printf("Introduce la solucion a la X1:\r\n");
    x1 = getchar(); /* Pedimos al usuario todas las soluciones */
    printf("Introduce la solucion a la X2:\r\n");
    x2 = getchar();
    printf("Introduce la solucion a la X3:\r\n");
    x3 = getchar();
    printf("Introduce la solucion a la X4:\r\n");
    x4 = getchar();
    printf("Introduce la solucion a la X5:\r\n");
    x5 = getchar();
    printf("Introduce la solucion a la X6:\r\n");
    x6 = getchar();
    printf("Introduce la solucion a la X7:\r\n");
    x7 = getchar();
    printf("Introduce la solucion a la X8:\r\n");
    x8 = getchar();
    printf("|4|"); /* Ponemos en la pantalla el sudoku completo con las opciones del usuario */
    putchar(x1);
    printf("|");
    putchar(x2);
    printf("|1|\r\n");
    printf("|");
    putchar(x3);
    printf("|1|3|");
    putchar(x4);
    printf("|\r\n");
    printf("|");
    putchar(x5);
    printf("|4|1|");
    putchar(x6);
    printf("|\r\n");
    printf("|1|");
    putchar(x7);
    printf("|");
    putchar(x8);
    printf("|3|\r\n");
    printf("\r\n");
    if (x1 == '3'&& x2 == '2'&& x3 == '2'&& x4 == '4'&& x5 == '3'&& x6 == '2'&& x7 == '2'&& x8 == '4') {
      printf("CORRECTO\r\n"); /* Si las respuestas son iguales a las soluciones es CORRECTO */
      printf("Nivel 1 Completado\r\n");
      do {
        printf("[N]ivel 2 o [C]errar\r\n"); /* Quieres ir al nivel2 o cerrar ?? */
        noc = getchar();
      } while (noc != 'N'&& noc != 'n'&& noc != 'C'&& noc != 'c'); /* Solo se aceptan N, n, C o c */
      if (noc == 'N'|| noc == 'n') {
        nivel2(); /* Ejecutamos el nivel2 */
        return EXIT_FAILURE;
      }
      if (noc == 'C'|| noc == 'c') {
        return EXIT_SUCCESS; /* Cerrando.... */
      }
    }
    if (x1 != '3'|| x2 != '2'|| x3 != '2'|| x4 != '4'|| x5 != '3'|| x6 != '2'|| x7 != '2'|| x8 != '4') { /* Si no coinciden INCORRECTO */
      do {
        printf("INCORRECTO\r\n");
        printf("Nivel 1 No completado\r\n");
        printf("[R]eintentar o [C]errar\r\n");
        roc = getchar();
      } while (roc != 'R'&& roc != 'r'&& roc != 'C'&& roc != 'c'); /* Reintentar ?? R o C.... no se admiten mas caracteres */
      if (roc == 'R'||roc == 'r') { /* Si reintenta.... */
        main(argc, argv); /* Volvemos al nivel1 (main()) */
      }
      if (roc == 'C'||roc == 'c') { /* Si elige cerrar... */
      return EXIT_SUCCESS; /* Cerramos! */
      }
    }
}

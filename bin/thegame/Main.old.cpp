/*
 * Copyright (C) 2014 Dan Rulos
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
#include <fcntl.h>

int getnum() /* Funcion para obtener los numeros */
{
    static int ch[1024]; /* Creamos un espacio en la memoria para trabajar con ellos */
    read(0, ch, 1); /* Leemos (read) del teclado, en la variable ch 1 caracter. */
    
    return ch[0];
}

int thegame()
{
    int f1=0;
    int f2=0;
    int f3=0;
    int f4=0;
    int f5=0;
    int f6=0;
    char jugador1[128]="Jugador1";
    char jugador2[128]="Jugador2";
    char cos='S';
    printf("Nombre del jugador 1: \r\n");
    gets(jugador1);
    printf("Nombre del jugador 2: \r\n");
    gets(jugador2);
    do {
      printf("------\r\n");
      printf("|1|2|3|\r\n");
      printf("|4|5|6|\r\n");
      printf("|7|8|9|\r\n");
      printf("------\r\n");
      printf("%s", jugador1);
      printf(" introduce tu primera ficha: \r\n");
      f1 = getnum();
      printf("%s", jugador2);
      printf(" introduce tu primera ficha: \r\n");
      f2 = getnum();
      printf("%s", jugador1);
      printf(" introduce tu segunda ficha: \r\n");
      f3 = getnum();
      printf("%s", jugador2);
      printf(" introduce tu segunda ficha: \r\n");
      f4 = getnum();
      printf("%s", jugador1);
      printf(" introduce tu tercera ficha: \r\n");
      f5 = getnum();
      printf("%s", jugador2);
      printf(" introduce tu tercera ficha: \r\n");
      f6 = getnum();
      if (f1 + f3 + f5 - 144 == 6|| f1 + f3 + f5 - 144 == 15|| f1 + f3 + f5 - 144 == 24||
        f1 + f3 + f5 - 144 == 12|| f1 + f3 + f5 - 144 == 18) {
        printf("%s", jugador1); 
        printf(" has ganado\r\n");
        return EXIT_SUCCESS;
      }
      if (f2 + f4 + f6 - 144 == 6|| f2 + f4 + f6 - 144 == 15|| f2 + f4 + f6 - 144 == 24||
        f2 + f4 + f6 - 144 == 12|| f2 + f4 + f6 - 144 == 18) {
        printf("%s", jugador2);
        printf(" has ganado\r\n");
        return EXIT_SUCCESS;
      }
      do {
        printf("[C]ontinuar o [S]alir\r\n");
        cos = getchar();
        if (cos == 'S'|| cos == 's') {
          return EXIT_SUCCESS;
        }
      } while (cos != 'S'&& cos != 's'&& cos != 'C'&& cos != 'c');
    } while (cos == 'C'|| cos == 'c');
}

int main(int argc, char **argv)
{
    char jos='S';
    printf("TheGAME v0.1\r\n");
    do {
      printf("[J]ugar o [S]alir ?\r\n");
      jos = getchar();
    } while (jos != 'J'&& jos != 'j'&& jos != 'S'&& jos != 's');
    if (jos == 'S'|| jos == 's') {
      return EXIT_SUCCESS;
    }
    if (jos == 'J'|| jos == 'j') {
      thegame();
    }
}

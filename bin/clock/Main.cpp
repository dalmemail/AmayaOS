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

int main(int argc, char **argv)
{
    printf("AmayaOS Clock 0.1\r\n");
    char horas[512];
    char minutos[512];
    char segundos[512];
    printf("Introduce la hora: ");
    gets_s(horas, 512);
    printf("Introduce los minutos: ");
    gets_s(minutos, 512);
    printf("Introduce los segundos: ");
    gets_s(segundos, 512);
    int horas1;
    int minutos1;
    int segundos1;
    /* Usamos atoi() para poder pasar las variables
    char* de las horas, minutos y segundos a int y
    asi poder operar con ellos. */
    horas1=atoi(horas);
    minutos1=atoi(minutos);
    segundos1=atoi(segundos);
    /* Si las horas son mayores de 24 */
    if (horas1 >= 24) {
      printf("%s error", argv[0]);
      return -1;
    }
    /* Si los minutos son mayores de 60 */
    if (minutos1 >= 60) {
      printf("%s error", argv[0]);
      return -1;
    }
    /* Si los segundos son mayores de 60 */
    if (segundos1 >= 60) {
      printf("%s error", argv[0]);
      return -1;
    }
    /* while(1) genera un bucle infinito */
    while(1) {
      sleep(1); // Esperamos un segundo y
      segundos1++; // Sumamos uno (variable++;)
      if (segundos1 == 60) {
        segundos1=segundos1-60;
        minutos1++;
      }
      if (minutos1 == 60) {
        minutos1=minutos1-60;
        horas1++;
      }
      if (horas1 == 24) {
        horas1=horas1-24;
      }
      /* Escribimos un reloj */
      printf("%d:%d:%d\r\n", horas1, minutos1, segundos1);
    }
}

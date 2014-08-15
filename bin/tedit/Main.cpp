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
/* tedit 0.1 TXT Edit */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int editar()
{
    char nombre[128];
    char linea[128];
    char son='N';
    int fd;
    char *newline="\r\n";
    printf("Archivo a editar: \r\n");
    gets(nombre);
    if (nombre[0] != '/') {
      printf("ERROR ! ");
      printf("%s", nombre);
      printf(" No es una ruta\r\n");
      editar();
    }
    do {
      printf("Se cambiara el contenido del archivo\r\n");
      printf(" Estas seguro ? [S/N]\r\n");
      son = getchar();
      if (son == 'N'|| son == 'n') {
        return EXIT_SUCCESS;
      }
    } while (son != 'S'&& son != 's'&& son != 'N'&& son != 'n');
    if ((fd = open(nombre, O_WRONLY)) < 0) {
        printf("Error al abrir '%s': %s\r\n",
                nombre, strerror(errno));
        return errno;
    }
    printf("Introduzca -Q para salir\r\n");
    printf("------------------------------------\r\n");
    do {
      gets(linea);
      if (linea[0] == '-'&& linea[1] == 'Q') {
        printf("\r\n");
        close(fd);
        return EXIT_SUCCESS;
      }
      /* Comienza la escritura del archivo */
      write(fd, linea, strlen(linea));
      write(fd, newline, 2);
    } while (linea[0] != '-'|| linea[1] != 'Q');
    return EXIT_SUCCESS;
}
      

int main(int argc, char **argv) /* funcion main() */
{
    char letra='S';
    printf("tedit 0.1\r\n");
    do {
      printf("[E]ditar archivo / [S]alir\r\n"); /* Opciones N, E o S */
      letra = getchar();
    } while (letra != 'E'&& letra != 'e'&& letra != 'S'&& letra != 's'); /* Si no es una de las 3 bucle */
    if (letra == 'E'|| letra == 'e') { /* Si es E */
      editar();
    }
    if (letra == 'S'|| letra == 's') { /* Si es S */
      return EXIT_SUCCESS; /* Salimos */
    }
}

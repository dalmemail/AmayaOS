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
#include <files.h>
#include <stdlib.h>

int cmp(char *archivo1, char *archivo2);

int main(int argc, char **argv)
{
    if (argc < 3) {
      printf("Uso: cmp archivo archivo\r\n");
      return EXIT_FAILURE;
    }
    cmp(argv[1], argv[2]);
}

int cmp(char *archivo1, char *archivo2)
{
    char *contenido;
    int fd;
    fd = open(archivo1, O_RDONLY);
    fread(fd, contenido);
    if (strcmp(contenido, contenido2) == 0) {
      printf("p");
      return EXIT_SUCCESS;
    }
    else {
      printf("-1\r\n");
      return EXIT_FAILURE;
    }
}

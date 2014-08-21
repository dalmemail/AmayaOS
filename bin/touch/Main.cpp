/* AMAYA OS 2014 */
/*
 * Copyright (C) 2014 Daniel Martin
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
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
int main(int argc, char **argv)
{
    int i;
    char cwd[128];
    /* Obtenemos los argumentos de la linea de comandos */
    if(argc < 2) { /* Si hay menos de 2 argumentos (palabras) en la linea de comandos avisa */
        printf("uso: %s ARCHIVO\n", argv[0]);
        return EXIT_FAILURE; /* Hala.... FAILURE! */
    }
    for (i=1; argv[i]; i++) {
      if (argv[i][0]!='/') { /* Necesito una ruta... */
        getcwd(cwd, sizeof(cwd));
        strcat(cwd, "/");
        strcat(cwd, argv[i]);
        touch(cwd, S_IWUSR | S_IRUSR);
      }
      else {
        touch(argv[i], S_IWUSR | S_IRUSR);
      }
    }
      return EXIT_SUCCESS; /* Todo ha salido bien */
}

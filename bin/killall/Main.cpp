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

int main(int argc, char **argv)
{
    /* Obtenemos los argumentos de la linea de comandos */
    if(argc < 2) {
      printf("Uso: %s PID o CMD del proceso\n", argv[0]);
      return EXIT_FAILURE;
    }

    /* Convertir char a int para usar exit() */
    int proceso = (int)argv[1];

    /* killall */
    exit(EXIT_SUCCESS);
    return EXIT_SUCCESS; /* Hecho */
}

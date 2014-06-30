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
int main(int argc, char **argv)
{
    mode_t dev;

    /* Si no hay argumento muestra 0. */
    if (argc < 2) {
        printf("0\r\n");
        return EXIT_SUCCESS;
    }
    /* Opciones como --help */
    else {
        for (int i = 0; i < argc - 1; i++) {
            if (strcmp(argv[i + 1], "-n") == 0||strcmp(argv[i + 1], "--adjustment") == 0)
                printf("nice: option requires an argument -- 'n'\r\n");
                printf("Pruebe `nice --help' para mas informacion.\r\n");
            /* Mensaje de ayuda. */
            if (strcmp(argv[i + 1], "--help") == 0) {
                printf( "uso: nice -n...\r\n"
                    "Comando nice.\r\n"
                    "\r\n"
                    "-n, --adjustment Dar prioridades a los comandos.\r\n"
                    "    --help       muestra esta ayuda.\r\n", argv[0]);
                return EXIT_SUCCESS;
            }
            /* Argumento desconocido. */
            else {
                printf( "%s: argumento invalido `%s'\r\n",
                        argv[0], argv[i + 1]);
                return EXIT_FAILURE;
            }
        }
    }
    /* Terminamos con una linea nueva. */
    printf("\r\n");
    
    /* Hecho. */
    return EXIT_SUCCESS;
}

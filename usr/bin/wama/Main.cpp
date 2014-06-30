/* Wama Loader by Dan Rulos */
/* Copyright (C) 2014 Team Espartano (AmayaOS) */
/*
# Copyright (C) 2014 Team Espartano (AmayaOS)
# 
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.*/

#include <stdio.h>
#include <stdlib.h>
#include "written.cpp" /* Importamos la libreria de Wama */
#include <errno.h>
#include <string.h>

int main(int argc, char **argv)
{

    /* If no argument given, show the system name. */
    if (argc < 2) {
        printf("WAMA Loader\r\n");
        printf("Uso : wama --help\r\n");
        return EXIT_SUCCESS;
    }
    /* Interpetar los argumentos. */
    else {
        for (int i = 0; i < argc - 1; i++) {
            /* Written. */
            if (strcmp(argv[i + 1], "-w") == 0||strcmp(argv[i + 1], "--written") == 0)
                written();

            /* Reader. */
            else if (strcmp(argv[i + 1], "-r") == 0||strcmp(argv[i + 1], "--reader") == 0)
                printf("Reader no esta disponible");

            /* Mensaje de ayuda. */
            else if (strcmp(argv[i + 1], "--help") == 0) {
                printf( "uso: %s [OPCION]...\r\n"
                    "Imprime informacion del sistema.\r\n"
                    "\r\n"
                    "-r, --reader  Inicia la parte de Wama que se dedica a la lectura.\r\n"
                    "-w, --written Inicia la parte de Wama que se dedica a la escritura.\r\n"
                    "    --help    muestra esta ayuda.\r\n", argv[0]);
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
    
    /* Terminamos con una nueva linea. */
    printf("\r\n");
    
    /* Hecho. */
    return EXIT_SUCCESS;
}

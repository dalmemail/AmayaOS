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

    /* Obtenemos los argumentos de la linea de comandos. */
    if (argc > 1) {
        printf("uso: %s ARCHIVO A SER CREADO c 1 2\r\n",
            argv[0]);
        return EXIT_FAILURE;
    }

    /* Intentamos crear el archivo. */
    if (touch(argv[1], dev) < 0) { /* Esto es lo importante "touch" */
        printf("%s: error al crear '%s': %s\r\n",
            argv[0], argv[1], strerror(errno));
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

/*
 * Copyright (C) 2009 Niek Linnenbank, 2012 Felipe Cabrera, 2014 Daniel Martin
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
#include <errno.h>
#include <string.h>
#include <sys/utsname.h>

int main(int argc, char **argv)
{
    struct utsname info;

    /* Retrieve version information. */
    if (uname(&info) < 0) {
        printf("%s: uname() failed: %s\r\n",
            argv[0], strerror(errno));
        return errno;
    }
    
    /* If no argument given, show the system name. */
    if (argc < 2) {
        printf("%s", info.sysname);
    }
    /* Otherwise, interpret argument(s). */
    else {
        for (int i = 0; i < argc - 1; i++) {
            /* System name. */
            if (strcmp(argv[i + 1], "-s") == 0||strcmp(argv[i + 1], "--kernel-name") == 0)
                printf("%s ", info.sysname);

            /* Node name. */
            else if (strcmp(argv[i + 1], "-n") == 0||strcmp(argv[i + 1], "--nodename") == 0)
                printf("%s ", info.nodename);
            
            /* Release. */
            else if (strcmp(argv[i + 1], "-r") == 0||strcmp(argv[i + 1], "--kernel-release") == 0)
                printf("%s ", info.release);

            /* Version. */
            else if (strcmp(argv[i + 1], "-v") == 0||strcmp(argv[i + 1], "--kernel-version") == 0)
                printf("%s ", info.version);

            /* Machine name. */
            else if (strcmp(argv[i + 1], "-m") == 0||strcmp(argv[i + 1], "--machine") == 0)
                printf("%s ", info.machine);

            /* OS. */
            else if (strcmp(argv[i + 1], "-os") == 0||strcmp(argv[i + 1], "--operating-system") == 0)
                printf("AmayaOS");

            /* Everything. */
            else if (strcmp(argv[i + 1], "-a") == 0||strcmp(argv[i + 1], "--all") == 0)
                printf( "%s %s %s %s %s ",
                        info.sysname,
                        info.nodename,
                        info.release,
                        info.version,
                        info.machine);

            /* Help message. */
            else if (strcmp(argv[i + 1], "--help") == 0) {
                printf( "uso: %s [OPCION]...\r\n"
                    "Imprime informacion del sistema.\r\n"
                    "\r\n"
                    "-a, --all               imprimir toda la informacion en el siguiente orden.\r\n"
                    "-s, --kernel-name       imprimir el nombre del sistema.\r\n"
                    "-n, --nodename          imprimir el host del nodo de la red.\r\n"
                    "-r, --kernel-release    imprimir la version del nucleo.\r\n"
                    "-v, --kernel-version    imprimir la version del kernel.\r\n"
                    "-m, --machine           imprimir el nombre del hardware de la maquina.\r\n"
                    "-os, --operating-system imprimir el nombre del sistema operativo.\r\n"
                    "    --help    muestra esta ayuda.\r\n", argv[0]);
                return EXIT_SUCCESS;
            }
            
            /* Unknown argument. */
            else {
                printf( "%s: argumento invalido `%s'\r\n",
                        argv[0], argv[i + 1]);
                return EXIT_FAILURE;
            }
        }
    }
    
    /* Terminate with a newline. */
    printf("\r\n");
    
    /* Done. */
    return EXIT_SUCCESS;
}

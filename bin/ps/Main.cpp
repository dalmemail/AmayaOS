/*
 * Copyright (C) 2009 Niek Linnenbank, 2012 Felipe Cabrera
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
#include <stdarg.h>
#include <string.h>
#include <errno.h>
#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>

void readfile(char *buf, Size size, char *fmt, ...)
{
    char path[128];
    int fd;
    Error e;
    va_list av;
    
    /* Damos formato a la ruta. */
    va_start(av, fmt);
    vsnprintf(path, sizeof(path), fmt, av);
    va_end(av);

    /* Intentamos abrir el archivo. */
    if ((fd = open(path, ZERO)) < 0) {
        printf("Error al abrir '%s': %s\r\n",
                path, strerror(errno));
        exit(EXIT_FAILURE);
    }
    
    /* Leemos el contenido. */
    switch ((e = read(fd, buf, size))) {
        /* Ha ocurrido un error. */
        case -1:
            printf("Error al leer '%s': %s\r\n",
                    path, strerror(errno));
            close(fd);
            exit(EXIT_FAILURE);
        /* Final del archivo. */
        case 0:
            close(fd);
            return;
        /* Listo. */
        default:
            buf[e] = ZERO;
            return;
    }
}

char *tr(char *stat)
{
    if(!strcmp(stat,"Sleeping"))
        return "Durmiendo";
    else if(!strcmp(stat,"Ready"))
        return "Listo";
    else
        return stat;
}

int main(int argc, char **argv)
{
    if(argc > 2) {
        printf("uso: %s [OPCION]...\r\n",
               argv[0]);
        return EXIT_FAILURE;
    }
    
    DIR *d;
    struct dirent *dent;
    char status[11];
    char cmdline[64];
    
    /* Intentamos abrir el directorio. */
    if (!(d = opendir("/proc"))) {
        printf("Error al abrir '/proc': %s\r\n",
            strerror(errno));
        return errno;
    }
    
    if(argc > 1) {
        if(!strcmp(argv[1],"--help")) {
            printf( "uso: %s [OPCION]...\r\n"
                    "Imprime informacion sobre los procesos.\r\n"
                    "\r\n"
                    "-a, --all               Muestra todos los procesos.\r\n"
                    "-e, --exec              Muestra todos los procesos ejecutandose.\r\n"
                    "-s, --sleep             Muestra todos los procesos durmiendo.\r\n"
                    "    --help    Muestra esta ayuda.\r\n", argv[0]); 
        } else if(!strcmp(argv[1],"-e")||!strcmp(argv[1],"--exec")) {
            /* Escribimos la cabecera. */
            printf("PID   ESTADO     CMD\r\n");
            
            /* Leemos el directorio */
            while ((dent = readdir(d))) {
                if (dent->d_name[0] != '.') {
                    /* Leemos el estado de los procesos. */
                    readfile(status,  sizeof(status),
                        "/proc/%s/status",  dent->d_name);
                    readfile(cmdline, sizeof(cmdline),
                        "/proc/%s/cmdline", dent->d_name);

                    if(strcmp(status,"Ready")==0) {
                        /* Imprimimos una linea. */ 
                        printf("%5s %10s %32s\r\n",
                                dent->d_name, tr(status), cmdline);
                    }
                }
            }
        } else if(!strcmp(argv[1],"-a")||!strcmp(argv[1],"--all")) {
            /* Escribimos la cabecera. */
            printf("PID   ESTADO     CMD\r\n");
            
            /* Leemos el directorio */
            while ((dent = readdir(d))) {
                if (dent->d_name[0] != '.') {
                    /* Leemos el estado de los procesos. */
                    readfile(status,  sizeof(status),
                        "/proc/%s/status",  dent->d_name);
                    readfile(cmdline, sizeof(cmdline),
                        "/proc/%s/cmdline", dent->d_name);

                    /* Imprimimos una linea. */ 
                    printf("%5s %10s %32s\r\n",
                            dent->d_name, tr(status), cmdline);
                }
            }
        } else if(!strcmp(argv[1],"-s")||!strcmp(argv[1],"--sleep")) {
            /* Escribimos la cabecera. */
            printf("PID   ESTADO     CMD\r\n");
            
            /* Leemos el directorio */
            while ((dent = readdir(d))) {
                if (dent->d_name[0] != '.') {
                    /* Leemos el estado de los procesos. */
                    readfile(status,  sizeof(status),
                        "/proc/%s/status",  dent->d_name);
                    readfile(cmdline, sizeof(cmdline),
                        "/proc/%s/cmdline", dent->d_name);

                    if(strcmp(status,"Sleeping")==0) {
                        /* Imprimimos una linea. */ 
                        printf("%5s %10s %32s\r\n",
                                dent->d_name, tr(status), cmdline);
                    }
                }
            }
        }
    } else {
        /* Escribimos la cabecera. */
        printf("PID   ESTADO     CMD\r\n");
        
        /* Leemos el directorio */
        while ((dent = readdir(d))) {
            if (dent->d_name[0] != '.') {
                /* Leemos el estado de los procesos. */
                readfile(status,  sizeof(status),
                        "/proc/%s/status",  dent->d_name);
                readfile(cmdline, sizeof(cmdline),
                        "/proc/%s/cmdline", dent->d_name);

                /* Imprimimos una linea. */	
                printf("%5s %10s %32s\r\n",
                        dent->d_name, tr(status), cmdline);
            }
        }
    }
    
    /* Cerrar. */
    closedir(d);
    
    /* Listo. */
    return EXIT_SUCCESS;
}

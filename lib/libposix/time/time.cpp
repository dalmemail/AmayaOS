/**
 * Copyright (C) 2012 Felipe Cabrera
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

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

/**
 * The time() function returns the value of time in seconds since the Epoch.
 * The tloc argument points to an area where the return value is also stored.
 * If tloc is a null pointer, no value is stored.
 */

/**
 * TODO: Stores the return value in tloc
 */

time_t time(time_t *tloc)
{
    char buf[1025];
    int fd, e;

    /* Limpiamos el buffer. */
    memset(buf, 0, sizeof(buf));
    
    /* Abrimos el dispositivo */
    fd = open("/dev/time", O_RDONLY);

    /* Intentamos abrir el archivo. */
    if (fd < 0)
        printf("%s", strerror(errno));
    else {
        e = read(fd, buf, sizeof(buf) - 1);
        switch (e) {
            /* Ocurrió un error. */
            case -1:
                //printf("%s", strerror(errno));
                close(fd);
                return -1;
            /* Final de archivo. */
            case 0:
                close(fd);
                break;
            default:
                buf[e] = 0;
                break;
        }
    }
    close(fd);
    return (atoi(buf));
}

time_t time(void *tloc)
{
    return time((time_t*)tloc);
}
/*
# Copyright (C) 2014 Team Espartano (AmayaOS).
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>*/

#include <stdio.h>

int written(char *archivo, char *linea)
{
    int fd;
    char *newline="\r\n";
    if ((fd = open(archivo, O_WRONLY)) < 0) {
        printf("Error al abrir '%s': %s\r\n",
                archivo, strerror(errno));
        return errno;
    }
    write(fd, linea, strlen(linea));
    write(fd, newline, 2);
}

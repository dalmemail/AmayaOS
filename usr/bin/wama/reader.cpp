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
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <files.h>
 
int reader(int argc, char *argv[])
{
    int ret = EXIT_SUCCESS, result;
    if(argc<2) 
    {
        printf("\n");
        printf("********************************************************************************\n");
        printf("***************************************  WA+  **********************************\n"); 
        printf("********************************************************************************\n");
        printf("Modulo de lectura 0.1 junglacode \n");
    }
    else
    {
    /* Obtenemos todos los archivos dados. */
    for (int i = 0; i < argc - 1 ; i++) {
        /* Intentamos mostrar el contenido. */
        file *fichero = new file();
        fichero->setpath(argv[i + 1]);
        fichero->f_open(O_RDONLY);
        char *contenido = fichero->readAll();
        fichero->f_close();
    
        printf("%s", contenido);

        /* Actualizamos el resultado si es necesario. */
        if (result > ret)
            ret = result;
    }

    }

   return ret;
}

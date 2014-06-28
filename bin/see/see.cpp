/*
 * Copyright (C) 2009 Niek Linnenbank, 2014 Daniel Martin
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
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <files.h>

int main(int argc, char **argv)
{
    int ret = EXIT_SUCCESS, result;

        printf("AMAYA-OS SEE 0.01 | It's free software\r\n",
                argv[0]);
    /* verificaamos los argumentos de la linea de comandos. */
    if (argc < 2) {
        printf("Uso de see: %s Archivo a leer\r\n",
                argv[0]);
        printf("How to use see: %s File to be read\r\n",
                argv[0]);
        return EXIT_FAILURE;
    }
    
    /* Obtenemos todos los archivos dados. */
    for (int i = 0; i < argc - 1 ; i++) {
        /* Intentamos mostrar el contenido. */
        file *f = new file();
        f->setpath(argv[i + 1]);
        f->f_open(O_RDONLY);
        char *ch = f->readAll();
        f->f_close();
    
        printf("%s", ch);

        /* Actualizamos el resultado si es necesario. */
        if (result > ret)
            ret = result;
    }
    
    /* Listo. */
    return ret;
}

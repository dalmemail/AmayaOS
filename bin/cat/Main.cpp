/*
 * Copyright (C) 2009 Niek Linnenbank, 2015 Dan Rulos
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
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#define VERSION "v0.5.7"

int f_size(char *path)
{
	struct stat st;
	int ssize;
	if ((stat(path, &st)) < 0) {
		ssize = -1;
	}
	else {
		ssize = st.st_size;
	}
	return ssize;
}

int main(int argc, char **argv)
{
    int ret = EXIT_SUCCESS, result;

    /* verificaamos los argumentos de la linea de comandos. */
    if (argc < 2) {
        printf("uso: %s FILE1 FILE2 ...\n",
                argv[0]);
        return EXIT_FAILURE;
    }
    if (argc == 2 && (strcmp(argv[1], "--help")) == 0) {
	printf("AmayaOS Coreutils %s (C) 2015 AmayaOS Team & Others\n", VERSION);
	printf("Licencia GNU GPL v3 <http://www.gnu.org/licenses/>.\n");
	printf("Uso: %s FILE1 FILE2 ...\n", argv[0]);
	printf("Reportar errores a traves de http://bugs.amayaos.com o amaya@amayaos.com\n");
	return EXIT_SUCCESS;
    }
    
    /* Obtenemos todos los archivos dados. */
    for (int i = 0; i < argc - 1 ; i++) {
        /* Intentamos mostrar el contenido. */
        int fsize = f_size(argv[i+1]);
	char *ch = new char [fsize];
	int fd;
	if ((fd = open(argv[i+1], O_RDONLY)) < 0) {
		printf("%s: error al leer '%s'\n", argv[0], argv[i+1]);
		result = EXIT_FAILURE;
	}
	else {
		read(fd, ch, fsize);
		close(fd);
		printf("%s", ch);
	}
	delete ch;

        /* Actualizamos el resultado si es necesario. */
        if (result > ret)
            ret = result;
    }
    
    /* Listo. */
    return ret;
}

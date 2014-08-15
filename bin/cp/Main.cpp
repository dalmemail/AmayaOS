/*
 * Copyright (C) 2009 Niek Linnenbank, 2014 Dan Rulos.
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
#include <errno.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

int cpdir(char *folder, char *ruta2) /* Funcion para copiar carpetas */
{
    mkdir(ruta2, S_IWUSR | S_IRUSR);
    return EXIT_SUCCESS;
}

int cptxt(char *txtin, char *txtout) /* Funcion para copiar archivos simples */
{
    char *contenido;
    touch(txtout, S_IWUSR | S_IRUSR);
    int fileopened = open(txtin, O_RDONLY);
    read(fileopened, contenido, 41);
    return EXIT_SUCCESS;
}

int cpch(char *chin, char *chout) /* Funcion para copiar character device file */
{
    dev_t dev;
    mknod(chout, S_IFCHR, dev);
    return EXIT_SUCCESS;
}

int statFile(char *prog, char *file, char *ruta)
{
    struct stat st;
    dev_t dev;
    /* Intentar stat el archivo. */
    if ((stat(file, &st)) < 0) {
        printf("%s: Error al copiar '%s': %s\r\n",
            prog, file, strerror(errno));
        return EXIT_FAILURE;
    }
    
    /* Tipo de archivo y como copiar cada uno
       de ellos. */
    if (S_ISREG(st.st_mode))
        cptxt(file, ruta);
    else if (S_ISDIR(st.st_mode))
        cpdir(file, ruta);
    else if (S_ISCHR(st.st_mode)) {
        cpch(file, ruta);
    }
    else if (S_ISBLK(st.st_mode)) {
        mknod(ruta, S_IFCHR, dev);	
    }
    else
        printf("Desconocido\r\n");

    /* Hecho. */
    return EXIT_SUCCESS;
}

int main(int argc, char **argv)
{
    int ret = EXIT_SUCCESS, result;

    /* Comprobamos los argumentos de la linea de comandos. */
    if (argc < 3)
    {
	printf("uso: %s Entrada Salida ...\r\n",
		argv[0]);
	return EXIT_FAILURE;
    }    
    /* Perform a stat for each file. */
    for (int i = 0; i < argc - 1; i++)
    {
	/* Stat the file immediately. */
	result = statFile(argv[0], argv[1], argv[2]);
	
	/* Update exit status, if needed. */
	if (result > ret)
	{
	    ret = result;
	}
    }    
    /* Success. */
    return ret;
}

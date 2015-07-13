/*
 * Copyright (C) 2015 Francisco Domínguez, 2015 Dan Rulos
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
/* tedit 0.2 TXT Edit */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int main(int argc, char **argv) /* funcion main() */
{
	printf("----------------------------------\n");
	printf("tedit 0.2 by Francisco Dominguez\n");
	printf("----------------------------------\n");
	// creamos los arrays que necesitemos
	char nombre[128];
	char option;
	char linea[128];
	char buffer[2048];
	/* number of bytes of argv[2] file (if we need to read argv[2]) */
	int n_bytes = 0;
	//creamos el puntero que usaremos como identificador del archivo
	int fd;
	FILE *input_file;
	//copiamos el primer elemento que le pasamos a tedit en el array option, si no se le pasa ninguno, se le pasa h y muestra la ayuda
	if (argc < 3) {
		option = 'h';
	}
	else {
		option = argv[1][0];
	}
	//abrimos el archivo dependiendo de que opción le pasemos
	switch (option) {
		//abre el archivo en modo overwrite
		case 'w':
			strcpy(nombre, argv[2]);
			if ((fd = open(nombre, O_WRONLY)) < 0) {
        			printf("Error al abrir '%s': %s\r\n",
                		nombre, strerror(errno));
        			return errno;
			}
			printf("\nArchivo abierto en modo overwrite, usar con precaucion\n");
			break;;
		//abre el archivo en modo append
		case 'a':
			strcpy(nombre, argv[2]);
			/* abrimos el archivo en modo lectura */
			if ((input_file = fopen(nombre, "r")) == NULL) {
				printf("Error al abrir '%s': %s\r\n",
				nombre, strerror(errno));
				return errno;
			}
			/* leemos el archivo */
			n_bytes = fread(buffer, 1, sizeof(buffer), input_file);
			/* cerramos el archivo */
			fclose(input_file);
			/* abrimos el archivo para escribir en el */
			if ((fd = open(nombre, O_WRONLY)) < 0) {
        			printf("Error al abrir '%s': %s\r\n",
                		nombre, strerror(errno));
        			return errno;
			}
			printf("\nArchivo abierto en modo append\n");
			break;;
		//Despliega la ayuda de comando
		case 'h':

			printf("\nuso: tedit opcion_abrir /ruta/de/fichero/fichero.txt\n");
			printf("--------------------\n");
			printf("opciones de apertura de ficheros:\n");
			printf("a -> abre fichero en modo append, lo que permite incluir lineas a un archivo desde el final de este\n");
			printf("w -> abre fichero en modo overwrite, lo que hace es sobreescribir el contenido del fichero, usar con precaucion\n");
			return 0;
			break;;
    
    }
    printf("Introduzca -Q para salir\r\n");
    printf("------------------------------------\r\n");
    if (option == 'a') {
	write(fd, buffer, n_bytes);
    }
    while( 1 ) {
     gets_s(linea, 128);
		//comprobamos si la nueva linea es "-Q"
        if (linea[0] == '-'&& linea[1] == 'Q') {
		//cerramos el archivo y el programa
        close(fd);
        return 0;
      }
      // Comienza la escritura del archivo
      write(fd, linea, strlen(linea));
      write(fd, "\n", 1);
    }
    close(fd);
}

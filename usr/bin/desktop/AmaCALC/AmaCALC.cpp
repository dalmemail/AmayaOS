/*
 * Copyright (C) 2015 Dan Rulos
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
#include <files.h>
#include <stdlib.h>
#include "AmaCALC.h"

/* Prototipo de la función principal */
void ama_calc();

void clean_csv()
{
    char clean[] = {0x1b, 0x5b, 0x48, 0x1b, 0x5b, 0x4a, '\0'};
    printf("%s", clean);
}

char *reader_csv(char *path)
{
    /* Abrimos y leemos el fichero */
    file *fichero = new file();
    fichero->setpath(path);
    fichero->f_open(O_RDONLY);
    char *contenido = fichero->readAll();
    fichero->f_close();
    /* Devolvemos el contenido del fichero */
    return contenido;
}

void read_csv(char *path)
{
    clean_csv();
    /* Leemos el archivo */
    char *c = reader_csv(path);
    char contenido[strlen(c)];
    strcpy(contenido, c);
    /* Número de barra lateral */
    int izq=1;
    int p = 1;
    printf("  A  	B 	C 	D 	E	F 	G 	H 	I 	J\r\n");
    /* Interpretamos el archivo CSV */
    printf("%d ", izq);
    for (int i=0; i < strlen(c); i++) {
	if (c[i-1] == '\n') {
	  izq++;
	  printf("\n%d ", izq);
	}
	if (c[i] == ';') {
	  printf("  ");
	}
	if (c[i] != ';' && c[i] != '"' && c[i] != '\n') {
	  printf("%c", c[i]);
	}
    }
    printf("\n");
    printf("PRESS ANY KEY TO CONTINUE\n");
    getchar();
    /* Volvemos al menú */
    ama_calc();
}

int new_csv(char *path)
{
     char line[128];
     char l[128];
     /* Limpiamos la pantalla */
     clean_csv();
     /* Creamos el archivo deseado */
     touch(path, S_IWUSR | S_IRUSR);
     /* Abrimos el archivo */
     int fd;
     if ((fd = open(path, O_WRONLY)) < 0) {
         printf("Error al abrir '%s': %s\r\n",
                 path, strerror(errno));
         return errno;
     }
     /* Interfaz */
     printf("  A  	B 	C 	D 	E	F 	G 	H 	I 	J\r\n");
     int izq=1;
     printf("%d ", izq);
     do {
	get_input_csv(line, 128);
	if (strcmp(line, "#exit#") != 0 && line[0] != '=' && line[strlen(line)-1] != '\n') {
	  write(fd, "\"", 1);
	  write(fd, line, strlen(line));
	  write(fd, "\"", 1);
	  write(fd, ";", 1);
	}
	if (line[strlen(line)-1] == '\n' && strcmp(line, "#exit#\n") != 0) {
	  for (int i=0; line[i] != '\n'; i++) {
		l[i] = line[i];
	  }
	  izq++;
	  write(fd, "\"", 1);
	  write(fd, l, strlen(l));
	  write(fd, "\"", 1);
	  write(fd, ";", 1);
	  write(fd, "\n", 1);
	  printf("%d ", izq);
	}
     } while(strcmp(line, "#exit#") != 0 && strcmp(line, "#exit#\n") != 0);
     /* Cerramos el archivo */
     close(fd);
     /* Volvemos al menú */
     ama_calc();
}

void ama_calc()
{
     clean_csv();
     char command[128];
     char path[128];
     printf("Welcome to Amacalc v0.2\n");
     printf("Available commands:\n");
     printf("open --> Open an existant calculation sheet\n");
     printf("new --> Create a new calculation sheet\n");
     printf("exit --> Close Amacalc and return desktop\n");
     do {
	printf("amacalc@localhost> ");
	gets_s(command, 128);
     } while(strcmp(command, "open") != 0 && strcmp(command, "exit") != 0 && strcmp(command, "new") != 0);
     if (strcmp(command, "open") == 0) {
	printf("File path: ");
	gets_s(path, 128);
	read_csv(path);
     }
     if (strcmp(command, "new") == 0) {
	printf("New file path: ");
	gets_s(path, 128);
	new_csv(path);
     }
}

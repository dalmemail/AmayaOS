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
	/* Contamos el numero de letras (A, B, C, etc) */
	int n_letters = 0;
	for (unsigned int i = 0, v = 0; i < strlen(c); i++) {
		for (v = 0; c[i] != '\n'; i++) {
			if (c[i] == ';') {
				v++;
			}
		}
		if (v > n_letters) {
			n_letters = v;
		}
	}
	/* Si el archivo CSV tiene mas letras que las existentes.. */
	if (n_letters > 26) {
		printf("ERROR: ARCHIVO CSV CORRUPTO O NO SOPORTADO\n");
		getchar();
		ama_calc();
	}
	/* Contamos el tamaño máximo de una casilla */
	int n_space = 0;
	for (unsigned int i = 0, v = 0; i < strlen(c); i++) {
		for (v = 0; c[i] != '\n' && c[i] != '"' && c[i] != ';'; i++) {
			v++;
		}
		if (v > n_space) {
			n_space = v;
		}
	}
	/* Numero de barra lateral */
	int izq=1;
	int p = 1;
	char *letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	printf("  ");
	for (int i = 0; i < n_letters; i++) {
		printf("%c", letters[i]);
		for (int v = 0; v < n_space; v++) {
			printf(" ");
		}
	}
	/* Interpretamos el archivo CSV */
	int n_chars_wrote = 0;
	printf("\n%d ", izq);
	for (unsigned int i=0, let=1; i < strlen(c); i++) {
		if (c[i-1] == '\n') {
			izq++;
			printf("\n%d ", izq);
		}
		if (c[i] == ';') {
			while (n_chars_wrote < (let * (n_space+1))) {
				printf(" ");
				n_chars_wrote++;
			}
			let++;
		}
		if (c[i] != ';' && c[i] != '"' && c[i] != '\n') {
			printf("%c", c[i]);
			n_chars_wrote++;
		}
	}
	printf("\n");
	printf("PRESS ANY KEY TO CONTINUE\n");
	getchar();
	/* Volvemos al menu */
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
	printf("  A  	B 	C 	D 	E	F\r\n");
	int izq=1;
	printf("%d ", izq);
	do {
		for (int w=0; w < 128; w++) {
			line[w] = '\0';
			l[w] = '\0';
		}
		get_input_csv(line, 128);
		/* Con 'zzz' llevamos la contabilidad de las letras */
		int zzz=0;
		int a[128];
		int b[128];
		int c[128];
		int d[128];
		int e[128];
		int f[128];
		if (strcmp(line, "#exit#") != 0 && line[0] != '=' && line[strlen(line)-1] != '\n' && numberyn(line[0]) == 1) {
			write(fd, "\"", 1);
			write(fd, line, strlen(line));
			write(fd, "\"", 1);
			write(fd, ";", 1);
		}
		if (strcmp(line, "#exit#") != 0 && line[0] != '=' && numberyn(line[0]) == 0) {
			if (line[strlen(line)-1] == '\n') {
				for (int i=0; line[i] != '\n'; i++) {
					l[i] = line[i];
				}
				write(fd, l, strlen(l));
				write(fd, ";", 1);
			}
			else {
				write(fd, line, strlen(line));
				write(fd, ";", 1);
	  		}
			char *contenido = reader_csv(path);
			int z=0;
			/* obtenemos la linea */
			for (int p=0; p < (izq - 1); z++) {
				if (contenido[z] == '\n') {
					p++;
				}
			} 
			/* obtenemos la letra */
			for (zzz=0; contenido[z] != '\n'; z++) {
				if (contenido[z] == ';') {
					zzz++;
				}
			}
			zzz=zzz-1;
			/* Guardamos el dato en el vector */
			switch (zzz) {
				case 0:
					a[izq] = atoi(line);
					break;
				case 1:
					b[izq] = atoi(line);
					break;
				case 2:
					c[izq] = atoi(line);
					break;
				case 3:
					d[izq] = atoi(line);
					break;
				case 4:
					e[izq] = atoi(line);
					break;
				case 5:
					f[izq] = atoi(line);
				break;
			}
		}
		if (line[strlen(line)-1] == '\n' && strcmp(line, "#exit#\n") != 0 && numberyn(line[0]) == 1 && line[0] != '=') {
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
		if (line[strlen(line)-1] == '\n' && strcmp(line, "#exit#\n") != 0 && numberyn(line[0]) == 0 && line[0] != '=') {
			zzz=0;
			izq++;
			write(fd, "\n", 1);
			printf("%d ", izq);
		}
		if (line[0] == '=') {
			if (numberyn(line[5]) == 1) {
				/* Aquí irán las letras de las celdas */
				char letter_1 = line[5];
				char letter_2;
				char n_1[128];
				char n_2[128];
				int numero_c1;
				int numero_c2;
				/* Obtenemos letter_2 */
				for (int i=6; line[i] != ')'; i++) {
					if (numberyn(line[i]) == 1 && line[i] != ';' && line[i] != ' ') {
						letter_2 = line[i];
					}
				}
		int i;
		int o=0;
		for (i=6; line[i] != ';'; i++) {
		  n_1[o] = line[i];
		  o++;
		}
		i=i+2;
		for (o=0; line[i] != ')'; i++) {
		  n_2[o] = line[i];
		  o++;
		}
		numero_c1 = atoi(n_1);
		numero_c2 = atoi(n_2);
		int s1;
		int s2;
		switch (letter_1) {
			case 'A':
				s1 = a[numero_c1];
		  		break;
			case 'B':
				s1 = b[numero_c1];
		  		break;
			case 'C':
				s1 = c[numero_c1];
				break;
			case 'D':
				s1 = d[numero_c1];
		  		break;
		  	case 'E':
				s1 = e[numero_c1];
		  		break;
		  	case 'F':
				s1 = f[numero_c1];
		  		break;
		}
		switch (letter_2) {
		  	case 'A':
				s2 = a[numero_c2];
		  		break;
		  	case 'B':
				s2 = b[numero_c2];
		  		break;
		  	case 'C':
				s2 = c[numero_c2];
		  		break;
		  	case 'D':
				s2 = d[numero_c2];
		  		break;
		  	case 'E':
				s2 = e[numero_c2];
		  	break;
		  	case 'F':
				s2 = f[numero_c2];
		  	break;
		}
		int res;
		if (line[1] == 'S' && line[2] == 'U' && line[3] == 'M') {
		  res = s1 + s2;
		}
		if (line[1] == 'R' && line[2] == 'E' && line[3] == 'S') {
		  res = s1 - s2;
		}
		if (line[1] == 'M' && line[2] == 'U' && line[3] == 'L') {
		  res = s1 * s2;
		}
		if (line[1] == 'D' && line[2] == 'I' && line[3] == 'V') {
		  res = s1 / s2;
		}
		char *resultado;
		itoa(resultado, 10, res);
		write(fd, resultado, strlen(resultado));
		write(fd, ";", 1);
		if (line[strlen(line)-1] == '\n') {
			write(fd, "\n", 1);
			izq++;
			printf("%d ", izq);
		}
	  }
	}
     } while(strcmp(line, "#exit#") != 0 && strcmp(line, "#exit#\n") != 0);
     /* Volvemos al menú */
     ama_calc();
}

void ama_calc()
{
	clean_csv();
	char command[128];
	char path[128];
	printf("Welcome to Amacalc v0.3.4\n");
	printf("Available commands:\n");
	printf("open --> Open an existant calculation sheet\n");
	printf("new --> Create a new calculation sheet\n");
	printf("exit --> Close Amacalc and return desktop\n");
	do {
		printf("amacalc@localhost> ");
		gets_s(command, 128);
		if (strcmp(command, "open") != 0 && strcmp(command, "exit") != 0 && strcmp(command, "new") != 0) {
			printf("AMACALC ERROR : COMMAND NOT FOUND\n");
		}
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
	clean_csv();
}

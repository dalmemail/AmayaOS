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
	if ((touch(path, S_IWUSR | S_IRUSR)) < 0 ) {
		printf("Error al crear el archivo '%s': %s\r\n",
		path, strerror(errno));
		return errno;
	}
	/* Abrimos el archivo */
	int fd;
	if ((fd = open(path, O_WRONLY)) < 0) {
		printf("Error al abrir '%s': %s\r\n",
		path, strerror(errno));
		return errno;
	}
	int n_letters = 0;
	int read_point = 0;
	int data[6][48];
	/* Interfaz */
	printf("  A  	B 	C 	D 	E	F\r\n");
	int izq=1;
	int old_izq = izq;
	printf("%d ", izq);
	do {
		old_izq = izq;
		if (izq >= 48) {
			ama_calc();
		}
		for (int w=0; w < 128; w++) {
			line[w] = '\0';
			l[w] = '\0';
		}
		get_input_csv(line, 128);
		if (strcmp(line, "#exit#") != 0 && line[0] != '=' && line[strlen(line)-1] != '\n' && numberyn(line[0]) == 1) {
			writter_csv(line, fd, 1);
		}
		if (strcmp(line, "#exit#") != 0 && line[0] != '=' && numberyn(line[0]) == 0) {
			if (line[strlen(line)-1] == '\n') {
				for (int i=0; line[i] != '\n'; i++) {
					l[i] = line[i];
				}
				writter_csv(l, fd, 0);
			}
			else {
				writter_csv(line, fd, 0);
	  		}
			char *contenido = reader_csv(path);
			/* obtenemos el punto de lectura */
			read_point = get_point(contenido, izq);
			/* obtenemos la letra */
			n_letters = get_letter(contenido, read_point);
			/* Guardamos el dato en el vector */
			data[n_letters][izq] = atoi(line);
		}
		if (line[strlen(line)-1] == '\n' && strcmp(line, "#exit#\n") != 0 && numberyn(line[0]) == 1 && line[0] != '=') {
			for (int i=0; line[i] != '\n'; i++) {
				l[i] = line[i];
			}
			izq++;
			writter_csv(l, fd, 2);
			printf("%d ", izq);
		}
		if (line[strlen(line)-1] == '\n' && strcmp(line, "#exit#\n") != 0 && numberyn(line[0]) == 0 && line[0] != '=') {
			n_letters = 0;
			izq++;
			write(fd, "\n", 1);
			printf("%d ", izq);
		}
		if (line[0] == '=' && checkCommand(line) == 0) {
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
		int l1 = get_letter_num(letter_1);
		int l2 = get_letter_num(letter_2);
		int res = 0;
		if (line[1] == 'S' && line[2] == 'U' && line[3] == 'M') {
		  res = data[l1][numero_c1] + data[l2][numero_c2];
		}
		if (line[1] == 'R' && line[2] == 'E' && line[3] == 'S') {
		  res = data[l1][numero_c1] - data[l2][numero_c2];
		}
		if (line[1] == 'M' && line[2] == 'U' && line[3] == 'L') {
		  res = data[l1][numero_c1] * data[l2][numero_c2];
		}
		if (line[1] == 'D' && line[2] == 'I' && line[3] == 'V') {
		  res = data[l1][numero_c1] / data[l2][numero_c2];
		}
		char *resultado;
		itoa(resultado, 10, res);
		writter_csv(resultado, fd, 0);
		print_line(line, resultado);
		if (line[strlen(line)-1] == '?') {
			write(fd, "\n", 1);
			izq++;
			printf("\n%d ", izq);
		}
		read_point = get_point(reader_csv(path), old_izq);
		n_letters = get_letter(reader_csv(path), read_point);
		data[n_letters][old_izq] = res;
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
	printf("Welcome to Amacalc v%s\n", AMACALC_V);
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

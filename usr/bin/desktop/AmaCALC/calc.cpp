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

/* Forked from gets_s(char*, size_t) made by Felipe Cabrera (2012)
 * See https://github.com/dalmemail/AmayaOS/blob/master/lib/libc/stdio/gets_s.c for more details
 */

#include <unistd.h>
#include "AmaCALC.h"

char *get_input_csv(char *str, size_t size)
{
	char line[1024 + size];
	Size total = 0;
	Size point = 0;

	/* Leemos una linea. */
	while (total < sizeof(line)) {
		/* Leemos un caracter. */
		read(0, line + point, 1);

		/* Procesamos el caracter. */
		switch (line[point]) {
			case '\r':
			case '\n':
				point++;
				total++;
				line[total] = ZERO;
				if (line[0] == '=' && line[point-2] == ')') {
					line[total-1] = '?';
				}
				else {
					putchar('\n');
				}
				strlcpy(str, line, size);
				return str;

			case '@':
				printf("  ");
				line[total] = ZERO;
				strlcpy(str, line, size);
				return str;

			case '\b':
				if (total > 0) {
					line[--total] = ZERO;
					point--;
					printf("\b \b");
				}
				break;
                
			case '\a':
                /*
                if (point > 0) {
                    printf("\b");
                    point--;
                }
                */
				break;
                
			default:
				printf("%c", line[point]);
				point++;
				total++;
				break;
		}
	}
    
	line[total] = ZERO;
    
}

/* Comprueba si un 'char' es un numero
 * Devuelve 0 si lo es y 1 si no lo es */
int numberyn(char number)
{
	if (number == '0' || number == '1'|| number == '2'|| number == '3'|| number == '4'|| number == '5'|| number == '6'|| number == '7'|| number == '8'|| number == '9') {
		return 0;
	}
	else {
		return 1;
	}
}

/* returns a letter code 
 * 0 A
 * 1 B
 * 2 C
 * 3 D
 * 4 E
 * 5 F
 */

int get_letter(char *c, int rp)
{
	int n_letter;
	for (n_letter = 0; c[rp] != '\n'; rp++) {
		if (c[rp] == ';') {
			n_letter++;
		}
	}
	n_letter--;
	return n_letter;
}

/* returns a point to read using get_letter() */
int get_point(char *c, int izq)
{
	int point = 0;
	for (int n_lines = 1; n_lines < izq; point++) {
		if (c[point] == '\n') {
			n_lines++;
		}
	}
	return point;
}

/* write 'c' in file 'fd' using the mode 'mode'
 * 'c' is the line to write
 * 'fd' is the file descriptor
 * 'mode' is the write mode
 */
void writter_csv(char *c, int fd, int mode)
{
	switch (mode) {
		case 0:
		case 3:
			write(fd, c, strlen(c));
			break;
		case 1:
		case 2:
			write(fd, "\"", 1);
			write(fd, c, strlen(c));
			write(fd, "\"", 1);
			break;
	}
	write(fd, ";", 1);
	if (mode >= 2) {
		write(fd, "\n", 1);
	}
}

/* cleans the internal command and print 'res' */
void print_line(char *line, char *res)
{
	int lon = strlen(line);
	if (line[lon-1] != '\n' && line[lon-1] != '?') {
		lon++;
		lon++;
	}
	else {
		lon--;
	}
	for (int i = 0; i < lon; i++) {
		printf("\b \b");
	}
	printf("%s  ", res);
}

/* returns 0 if letter == 'A'...*/
int get_letter_num(char letter)
{
	char *letters = "ABCDEF";
	for (int i = 0; i < strlen(letters); i++) {
		if (letter == letters[i]) {
			return i;
		}
	}
	return 0;
}

/* check if line it's a valid amacalc command 
 * returns 0 if yes
 * returns a negative number if not
 */
int checkCommand(char *line)
{
	int ret = 3;
	for (int i = 0; i < strlen(line); i++) {
		if (line[i] == '(' || line[i] == ';' || line[i] == ')') {
			ret--;
		}
	}
	return ret;
}

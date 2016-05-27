/*
 * Copyright (C) 2016 Dan Rulos [amaya@amayaos.com]
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
#include <sys/stat.h>
#include "wama.h"

void clean_screen()
{
	char str[] = {0x1b, 0x5b, 0x48, 0x1b, 0x5b, 0x4a, '\0'};
	printf("%s", str);
}

int checkWamaCommand(char *line)
{
	int ret = 0;
	if ((strcmp(line, "$exit")) == 0) {
		ret = 2;
	}
	else if ((strcmp(line, "$nav")) == 0) {
		ret = 1;
	}
	return ret;
}

int linecounter(char *c)
{
	int n_lines = 0;
	int c_len = strlen(c);
	for (int i = 0; i < c_len; i++) {
		if (c[i] == '\n') {
			n_lines++;
		}
	}
	return n_lines;
}

/* prototipo de get_size() */
int get_size(char *path);

char *read_file(char *path)
{
	int file_size = get_size(path);
	char *data = new char [file_size];
	int fd = open(path, O_RDONLY);
	read(fd, data, file_size);
	close(fd);
	/* Devolvemos el contenido del fichero */
	return data;
}

int get_size(char *path)
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

char *edit_lines(char *str, size_t size, char *line_to_edit)
{
    char line[1024 + size];
    Size total = 0;
    Size point = 0;
    strcpy(line, line_to_edit);

    printf("%s", line_to_edit);
    total = point = strlen(line_to_edit);

    /* Leemos una linea. */
    while (total < sizeof(line)) {
        /* Leemos un caracter. */
        read(0, line + point, 1);

        /* Procesamos el caracter. */
        switch (line[point]) {
            case '\r':
            case '\n':
                putchar('\n');
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
    
    return line_to_edit;
}

int line_navigator(char *path, int mode)
{
	int ret = 0;
	char *data = read_file(path);
	int n_lines = linecounter(data);
	int act_line = 1;
	char **lines;
	lines = new char *[n_lines];
	lines[0] = &data[0];
	int data_len = strlen(data);
	char to_find[128];
	to_find[0] = '\0';
	if (data_len > 0) {
		for (int i = 1, x = 0; data[x] != '\0'; x++) {
			if (data[x] == '\n') {
				data[x] = '\0';
				if (i < n_lines) {
					lines[i] = &data[x+1];
				}
				i++;
			}
		}
		if (n_lines > 0) {
			char char_read[2];
			do {
				clean_screen();
				int start_line = 0;
				if (n_lines >= 20 && act_line >= 20) {
					start_line = (act_line - 20);
				}
				for (int i = start_line; i < (start_line+20) && i < n_lines; i++) {
					printf("\n");
					if (i == (act_line-1)) {
						printf("#");
					}
					else {
						printf(" ");
					}
					printf("%d %s", (i+1), lines[i]);
				}
				read(0, char_read, 1);
				if (char_read[0] == 'w' && act_line < n_lines) {
					act_line++;
				}
				if (char_read[0] == 's' && act_line > 1) {
					act_line--;
				}
				if (char_read[0] == 'm') {
					char line[8];
					clean_screen();
					printf("Mover a: ");
					gets_s(line, 8);
					int line_to_move = atoi(line);
					if (line_to_move > 0 && line_to_move < n_lines) {
						act_line = line_to_move;
					}
				}
				if (char_read[0] == 'f') {
					clean_screen();
					printf("Buscar: ");
					edit_lines(to_find, 128, to_find);
					if (strlen(to_find) > 0) {
						int line_found = SearchInFile(to_find, data, data_len, act_line);
						if (line_found >= 0) {
							act_line = line_found;
						}
					}
				}
			} while(char_read[0] != '\n' && char_read[0] != 'x' && char_read[0] != 'r');
			clean_screen();
			if (char_read[0] == '\n' && mode == WRITE_MODE) {
				char edit_line[128];
				printf(" %d ", act_line);
				edit_lines(edit_line, 128, lines[(act_line-1)]);
				lines[act_line-1] = &edit_line[0];
				int fd;
				if ((fd = open(path, O_WRONLY)) < 0) {
					ret = -1;
				}
				else {
					int bytes_wrote = 0;
					for (int i = 0; i < n_lines; i++) {
						int strlen_ = strlen(lines[i]);
						write(fd, lines[i], strlen_);
						bytes_wrote += strlen_;
						write(fd, "\n", 1);
					}
					int size = get_size(path);
					if (bytes_wrote < size) {
						while (bytes_wrote++ < size) {
							write(fd, "\0", 1);
						}
					}
				}
			}
			if (char_read[0] == 'r' && mode == WRITE_MODE) {
				clean_screen();
				printf("Pulse 's' para borrar la linea %d\n", act_line);
				if (getchar() == 's') {
					int fd;
					if ((fd = open(path, O_WRONLY)) < 0) {
						ret = -1;
					}
					else {
						int bytes_wrote = 0;
						for (int i = 0; i < n_lines; i++) {
							if (i != (act_line-1)) {
								int strlen_ = strlen(lines[i]);
								write(fd, lines[i], strlen_);
								bytes_wrote += strlen_;
								write(fd, "\n", 1);
							}
						}
						int size = get_size(path);
						if (bytes_wrote < size) {
							while (bytes_wrote++ < size) {
								write(fd, "\0", 1);
							}
						}
					}
				}
				clean_screen();
			}
		}
	}
	delete lines;
	delete data;
	return ret;
}

int SearchInFile(char *string, char *c, int n_bytes, int act_line)
{
	int lines = 0;
	bool exists = false;
	for (int i = 0; i < n_bytes; i++) {
		lines++;
		for (unsigned int x = 0; c[i] != '\0' && i < n_bytes; i++) {
			if (string[x] == c[i] && !exists) {
				x++;
				if (x == strlen(string)) {
					exists = true;
				}
			}
			else if (!exists) {
				x = 0;
			}
		}
		if (exists && lines > act_line) {
			return lines;
		}
		exists = false;
	}
	return -1;
}

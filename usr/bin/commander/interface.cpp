/*
 * Copyright (C) 2016 Dan Rulos
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
#include <sys/stat.h>
#include "files.h"

void simple_interface();
void clean_screen();

void print_entry(struct dir_entry *dir_content, int cursor, int n_files)
{
	char colors[5][6] = { "\e[m", "\e[34m", "\e[32m", "\e[33m", "\e[36m"};
	char content[512] = "\0";
	char column[8];
	int i = (n_files > 19) ? cursor : 0;
	int sp = 0;
	for (int x = strlen(content); x < 512 && (i+4) < (23+cursor) && i < n_files; i++, sp++) {
		strcat(content, "\033[");
		itoa(column, 10, (sp+4));
		strcat(content, column);
		strcat(content, ";2H");
		if (i == cursor) {
			strcat(content, "\e[031m");
			x = strlen(content);
			content[x++] = 254;
		}
		else {
			x = strlen(content);
			content[x++] = ' ';
		}
		strcat(content, colors[dir_content[i].fileType]);
		strcat(content, dir_content[i].file_name);
	}
	printf("%s\033[24;80H\e[m", content);
}

void simple_interface()
{
	char bar[81];
	for (int i = 0; i < 80; i++) {
		bar[i] = 219;
	}
	bar[80] = '\0';
	printf("\033[1;1H%s\n%c\033[2;80H%c\n%s\n", bar, 179, 179, bar);
	for (int i = 4; i < 23; i++) {
		printf("%c\033[%d;80H%c\n", 179, i, 179);
	}
	printf("%s\n%c\033[24;80H%c\n%s", bar, 179, 179, bar);
}

void clean_screen()
{
	char str[] = {0x1b, 0x5b, 0x48, 0x1b, 0x5b, 0x4a, '\0'};
	printf("%s", str);
}

void print_path(char *path)
{
	char clear[78];
	unsigned int i;
	unsigned int path_size = strlen(path);
	for (i = 0; i < (79-path_size); i++) {
		clear[i] = ' ';
	}
	clear[i] = '\0';
	printf("\033[2;2H%s%s", path, clear);
}

void print_error(char *error)
{
	char clear[78];
	unsigned int i;
	unsigned int error_size = strlen(error);
	for (i = 0; i < (79-error_size); i++) {
		clear[i] = ' ';
	}
	clear[i] = '\0';
	printf("\033[24;2H%s%s", error, clear);
}

void refresh_interface(char *path)
{
	clean_screen();
	simple_interface();
	print_path(path);
}

void print_simple_window()
{
	char bar[31];
	for (int i = 0; i < 30; i++) {
		bar[i] = 219;
	}
	bar[30] = '\0';
	printf("\033[7;25H%s\033[17;25H%s", bar, bar);
	for (int i = 8; i < 17; i++) {
		printf("\033[%d;25H%c\033[%d;54H%c", i, 179, i, 179);
	}
	printf("\033[24;80H");
}

void print_info(struct stat st, char *path, char *filename)
{
	refresh_interface(path);
	print_simple_window();
	char screen[512];
	strcpy(screen, "\033[8;26HFichero: ");
	strcat(screen, filename);
	strcat(screen, "\033[9;26HTipo: ");
	if (S_ISREG(st.st_mode))
		strcat(screen, "Fichero comun");
	else if (S_ISDIR(st.st_mode))
		strcat(screen, "Directorio");
	else if (S_ISCHR(st.st_mode) || S_ISBLK(st.st_mode)) {
		(S_ISCHR(st.st_mode)) ? strcat(screen, "Character Device") : strcat(screen, "Block Device");
		strcat(screen, "\033[12;26HMajor ID: ");
		char major[4];
		itoa(major, 10, st.st_dev.major);
		strcat(screen, major);
		char minor[4];
		itoa(minor, 10, st.st_dev.minor);
		strcat(screen, "\033[13;26HMinor ID: ");
		strcat(screen, minor);
	}
	else {
		strcat(screen, "Desconocido");
	}
	strcat(screen, "\033[10;26HModo: ");
	char mode[4];
	itoa(mode, 10, st.st_mode);
	strcat(screen, mode);
	strcat(screen, "\033[11;26HSize: ");
	char size[12];
	itoa(size, 10, st.st_size);
	strcat(screen, size);
	printf("%s", screen);
}

void about_commander()
{
	print_simple_window();
	char screen[128];
	strcpy(screen, "\033[10;27HAmaya File Commander v0.1.1");
	strcat(screen, "\033[13;32Hamaya@amayaos.com");
	printf("%s", screen);
}

void print_simple_dialog()
{
	char bar[51];
	for (int i = 0; i < 50; i++) {
		bar[i] = 219;
	}
	bar[50] = '\0';
	printf("\033[12;15H%s\033[13;15H%c\033[13;64H%c\033[14;15H%c\
	\033[14;64H%c\033[15;15H%s", bar, 179, 179, 179, 179, bar);
}

char *get_string(char *message, char *str, int size)
{
	print_simple_dialog();
	printf("\033[13;16H%s\033[14;16H", message);
	char line[size];
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
				line[total] = ZERO;
				strlcpy(str, line, size);
				return str;

			case '\b':
				if (total > 0) {
					line[--total] = ZERO;
					point--;
					printf("\b \b");
					if (total > 48) {
						printf("\033[14;16H%s", &line[total-48]);
					}
					else {
						printf("\033[14;16H%s", line);
					}
				}
			break;
                
			case '\a':
			break;
                
			default:
				point++;
				total++;
				line[point] = ZERO;
				if (total > 48) {
					printf("\033[14;16H%s", &line[total-48]);
				}
				else {
					printf("\033[14;16H%s", line);
				}
			break;
		}
	}
    
	line[total] = ZERO;

	return str;
}

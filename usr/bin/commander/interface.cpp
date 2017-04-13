/*
 * Copyright (C) 2016, 2017 Daniel Martín
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

void print_entry(struct dir_entry *dir_content[2], struct dir_info dirs[2], int current_dir)
{
	char colors[5][6] = { "\e[m", "\e[34m", "\e[32m", "\e[33m", "\e[36m"};
	char content[2][512] = {"\0", "\0"};
	int init_position[2];
	for (int y = 0; y < 2; y++) {
		init_position[y] = (dirs[y].n_files < 19) ? 0 : dirs[y].cursor_position;
		int bw = 0;
		for (int x = 0; x < 19 && x < dirs[y].n_files; x++) {
			if (strlen(dir_content[y][init_position[y]+x].file_name) > 32) {
				char shortFileName[33];
				strlcpy(shortFileName, dir_content[y][init_position[y]+x].file_name, 32);
				snprintf(&shortFileName[30], 3, "..\0");
				snprintf(&content[y][bw], (512-bw), "\033[%d;%dH %s%s", (x+4), ((40*y)+2),colors[dir_content[y][init_position[y]+x].fileType],shortFileName);
			}
			else snprintf(&content[y][bw], (512-bw), "\033[%d;%dH %s%s", (x+4), ((40*y)+2),colors[dir_content[y][init_position[y]+x].fileType],dir_content[y][init_position[y]+x].file_name);
			bw = strlen(content[y]);
		}
	}
	printf("%s%s\033[%d;%dH\e[31m%c\033[24;80H\e[m", content[0], content[1], (dirs[current_dir].cursor_position+4-init_position[current_dir]), ((current_dir*40)+2), 254);
}

void simple_interface()
{
	char bar[81];
	for (int i = 0; i < 80; i++) {
		bar[i] = 219;
	}
	bar[80] = '\0';
	printf("\033[1;1H%s\n%c\033[2;41H%c\033[2;80H%c\n%s\n", bar, 179, 179, 179, bar);
	for (int i = 4; i < 23; i++) {
		printf("%c\033[%d;41H%c\033[%d;80H%c\n", 179, i, 179, i, 179);
	}
	printf("%s\n%c\033[24;80H%c\n%s", bar, 179, 179, bar);
}

void clean_screen()
{
	char str[] = {0x1b, 0x5b, 0x48, 0x1b, 0x5b, 0x4a, '\0'};
	printf("%s", str);
}

void print_path(char *first_path, char *second_path)
{
	char shortFirstPath[37];
	char shortSecondPath[37];
	if (strlen(first_path) > 36) {
		strlcpy(shortFirstPath, first_path, 36);
		snprintf(&shortFirstPath[34], 3, "..\0");
		first_path = &shortFirstPath[0];
	}
	if (strlen(second_path) > 36) {
		strlcpy(shortSecondPath, second_path, 36);
		snprintf(&shortSecondPath[34], 3, "..\0");
		second_path = &shortSecondPath[0];
	}
	printf("\033[2;2H%s\033[2;42H%s", first_path, second_path);
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

void refresh_interface(struct dir_info dirs[2])
{
	clean_screen();
	simple_interface();
	print_path(dirs[0].path, dirs[1].path);
}

void print_simple_window()
{
	char cleaner[31];
	for (int i = 0; i < 30; i++) {
		cleaner[i] = ' ';
	}
	cleaner[30] = '\0';
	char bar[31];
	for (int i = 0; i < 30; i++) {
		bar[i] = 219;
	}
	bar[30] = '\0';
	printf("\033[7;25H%s\033[17;25H%s", bar, bar);
	for (int i = 8; i < 17; i++) {
		printf("\033[%d;25H%s\033[%d;25H%c\033[%d;54H%c", i, cleaner, i, 179, i, 179);
	}
	printf("\033[24;80H");
}

void print_info(struct stat st, char *filename)
{
	char shortFileName[16] = "\0";
	if (strlen(filename) > 16) {
		strlcpy(shortFileName, filename, 16);
		snprintf(&shortFileName[14], 3, "..\0");
		filename = &shortFileName[0];
	}
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
	printf("%s\033[14;37H[ OK ]\033[14;38H", screen);
	while (getchar() != '\n');
}

void about_commander()
{
	print_simple_window();
	char screen[128];
	strcpy(screen, "\033[10;30HAmaya File Commander\033[11;34HVersion 0.3");
	strcat(screen, "\033[13;28HWritten by Daniel Martin\033[15;37H[ OK ]\033[15;38H");
	printf("%s", screen);
	while (getchar() != '\n');
}

void print_simple_dialog()
{
	char clean[51];
	char bar[51];
	for (int i = 0; i < 50; i++) {
		bar[i] = 219;
		clean[i] = ' ';
	}
	bar[50] = '\0';
	clean[50] = '\0';
	printf("\033[12;15H%s\033[13;15H%s\033[13;15H%c\033[13;64H%c\033[14;15H%s\033[14;15H%c\
	\033[14;64H%c\033[15;15H%s\033[15;15H%c\033[15;28H[ Aceptar ] [ Cancelar ]\033[15;64H%c\033[16;15H%s", bar, clean, 179, 179, clean, 179, 179, clean, 179, 179, bar);
}

char *get_string(char *message, char *str, int size)
{
	print_simple_dialog();
	printf("\033[13;16H%s", message);
	char line[size];
	Size total = 0;
	Size point = 0;
	int option = 0;

	/* Leemos una linea. */
	while (total < sizeof(line)) {
		switch (option) {
			case 0:
				printf("\033[14;%dH", (16+total));
			break;
			case 1:
				printf("\033[15;29H");
			break;
			case 2:
				printf("\033[15;41H");
			break;
		}
		/* Leemos un caracter. */
		read(0, line + point, 1);

		/* Procesamos el caracter. */
		switch (line[point]) {
			case '\r':
			case '\n':
				if (option < 2) {
					line[total] = ZERO;
					strlcpy(str, line, size);
					return str;
				}
				else return (char *)NULL;

			case '\b':
				if (!option && total > 0) {
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

			case '\t':
				if (option != 2) option++;
				else option = 0;
			break;
                
			default:
				if (!option) {
					point++;
					total++;
					line[point] = ZERO;
					if (total > 48) printf("\033[14;16H%s", &line[total-48]);
					else printf("\033[14;16H%s", line);
				}
			break;
		}
	}
    
	line[total] = ZERO;

	return str;
}

int exit_window()
{
	int option = 0;
	int ret = 0;
	char key = '\n';
	print_simple_window();
	printf("\033[10;27HDo you really want to exit?\033[13;32H[ \e[31mY\e[mes ] [ \e[31mN\e[mo ]");
	do {
		/* Set the cursor position */
		if (!option) printf("\033[13;33H");
		else printf("\033[13;41H");
		key = getchar();
		if (key == '\t') option ^= 1;
	} while(key != '\n' && key != 'y' && key != 'Y' && key != 'N' && key != 'n');
	if (key == '\n') ret = option;
	else ret = (key == 'y' || key == 'Y') ? 0 : 1;
	return ret;
}

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
#include <stdio.h>
#include "interface.h"
#include "files.h"
#include "wama.h"
#include "find.h"

#define CREATE_FILE -45

#define UP_KEY 30
#define DOWN_KEY 31
#define LEFT_KEY 28
#define RIGHT_KEY 29

struct cursor put_char(char key, char **lines, struct cursor file_cursor);

struct cursor add_line(char **lines, char **backup, struct cursor file_cursor, unsigned int nlines);

void set_cursor_(struct cursor file_cursor, int start_point);

struct cursor delete_line(char **lines, char **backup, struct cursor file_cursor, unsigned int nlines);

void delete_pointer(char **pointer, int pointer_n);

int wama_main(char *path)
{
	char prog[] = "Wama 0.8\0";
	int ret = 0;
	clean_screen();
	if (path == NULL) up_bar(prog, 25, "Nuevo Archivo", 35);
	else up_bar(prog, 25, path, 35);
	down_bar();
	int file_status;
	switch ((file_status = checkFile(path))) {
		case 1:
			add_message("Error: No es un archivo de texto");
			break;
		case CREATE_FILE:
			break;
		case 0:
			/* all ok */
			add_message("\e[36mWelcome to Wama\e[m");
			break;
		default:
			add_message(strerror(file_status));
			ret = -1;
			break;
	}
	char *data;
	unsigned int nlines;
	char **lines;
	char **backup;
	char search[60] = { '\0' };
	int start_point = 0;
	struct cursor file_cursor;
	file_cursor.ln = 0;
	file_cursor.col = 0;
	if (file_status == 0 || file_status == CREATE_FILE) data = read_file(path);
	if ((file_status == 0 || file_status == CREATE_FILE) && data != NULL) {
		nlines = linecounter(&data[0]);
		lines = new char*[nlines];
		for (unsigned int i = 0; i < nlines; i++) {
			lines[i] = new char[80];
		}
		separate_in_lines(data, lines, nlines);
		delete data;
		print_content(lines, file_cursor, nlines);
		int exit = 0;
		char key;
		while (!exit) {
			key = getchar();
			start_point = get_start_point(file_cursor.ln);
			if (key == '^') {
				key = getchar();
				switch (key) {
					case 'c':
						clean_message_line();
						printf("\e[24;30H[Line: %d Col: %d]",
						file_cursor.ln+1, file_cursor.col+1);
						set_cursor_(file_cursor, start_point);
						break;
					case 'x':
						exit = 1;
						break;
					case 'o':
						update_file_content(path, lines, nlines);
						set_cursor_(file_cursor, start_point);
						break;
					case 'w':
						get_string(search,60);
						if (search[0] != '\0') {
							file_cursor = findString(search,lines,nlines,file_cursor);
							print_content(lines,file_cursor,nlines);
							start_point = get_start_point(file_cursor.ln);
						}
						else set_cursor_(file_cursor, start_point);
						break;
					default:
						file_cursor = put_char('^', lines, file_cursor);
						break;
				}
			}
			else if (key == UP_KEY) {
				if (file_cursor.ln > 0) {
					file_cursor.ln--;
					if (strlen(lines[file_cursor.ln]) < (file_cursor.col+1)) {
						file_cursor.col = strlen(lines[file_cursor.ln]);
					}
				}
				print_content(lines, file_cursor, nlines);
			}
			else if (key == DOWN_KEY) {
				if ((file_cursor.ln+1) < nlines) {
					file_cursor.ln++;
					if (strlen(lines[file_cursor.ln]) < (file_cursor.col+1)) {
						file_cursor.col = strlen(lines[file_cursor.ln]);
					}
				}
				print_content(lines, file_cursor, nlines);
			}
			else if (key == LEFT_KEY) {
				if (file_cursor.col > 0) {
					file_cursor.col--;
				}
				else if (file_cursor.ln > 0) {
					file_cursor.ln--;
					file_cursor.col = strlen(lines[file_cursor.ln]);
				}
				printf("\e[%d;%dH", (file_cursor.ln-start_point)+4, file_cursor.col+1);
			}
			else if (key == RIGHT_KEY) {
				if (file_cursor.col < strlen(lines[file_cursor.ln])) {
					file_cursor.col++;
				}
				else if ((file_cursor.ln+1) < nlines) {
					file_cursor.ln++;
					file_cursor.col = 0;
				}
				printf("\e[%d;%dH", (file_cursor.ln-start_point)+4, file_cursor.col+1);
			}
			else if (key == '\b' && file_cursor.col == 0) {
				if (file_cursor.ln != 0 && strlen(lines[file_cursor.ln]) == 0) {
					backup = new char*[nlines];
					for (unsigned int i = 0; i < nlines; i++) {
						backup[i] = new char[80];
						strcpy(backup[i],lines[i]);
					}
					delete_pointer(lines,nlines);
					lines = new char*[nlines-1];
					for (unsigned int i = 0; i < (nlines-1); i++) {
						lines[i] = new char[80];
					}
					file_cursor = delete_line(lines, backup, file_cursor, nlines);
					delete_pointer(backup,nlines);
					nlines--;
					print_content(lines, file_cursor, nlines);
				}
			}
			else if (key == '\n') {
				backup = new char*[nlines];
				for (unsigned int i = 0; i < nlines; i++) {
					backup[i] = new char[80];
					strcpy(backup[i], lines[i]);
				}
				delete_pointer(lines,nlines);
				lines = new char*[nlines+1];
				for (unsigned int i = 0; i < (nlines+1); i++) {
					lines[i] = new char[80];
				}
				file_cursor = add_line(lines, backup,file_cursor, nlines);
				delete_pointer(backup,nlines);
				nlines++;
				print_content(lines, file_cursor, nlines);
			}
			else {
				file_cursor = put_char(key, lines, file_cursor);
				print_content(lines, file_cursor, nlines);
			}
		}
	}
	clean_screen();
	return ret;
}

struct cursor put_char(char key, char **lines, struct cursor file_cursor)
{
	if (file_cursor.col < strlen(lines[file_cursor.ln]) && file_cursor.col < 80) {
		unsigned int i;
		if (key == '\b') {
			unsigned int line_size = strlen(lines[file_cursor.ln]);
			for (i = file_cursor.col-1; i < line_size; i++) {
				lines[file_cursor.ln][i] = lines[file_cursor.ln][i+1];
			}
			lines[file_cursor.ln][i] = '\0';
			file_cursor.col--;
		}
		else {
			for (i = strlen(lines[file_cursor.ln]); i > file_cursor.col; i--) {
				lines[file_cursor.ln][i] = lines[file_cursor.ln][i-1];
			}
			lines[file_cursor.ln][file_cursor.col++] = key;
		}
	}
	else if (file_cursor.col < 80) {
		if (key == '\b') {
			lines[file_cursor.ln][--file_cursor.col] = '\0';
		}
		else {
			lines[file_cursor.ln][file_cursor.col] = key;
			lines[file_cursor.ln][++file_cursor.col] = '\0';
		}
	}
	return file_cursor;
}

struct cursor add_line(char **lines, char **backup, struct cursor file_cursor, unsigned int nlines)
{
	unsigned int new_lines = nlines+1;
	file_cursor.col = 0;
	file_cursor.ln++;
	for (unsigned int i = 0, x = 0; i < new_lines; i++) {
		if (i != file_cursor.ln) {
			strcpy(lines[i], backup[x++]);
		}
	}
	lines[file_cursor.ln][0] = '\0';
	return file_cursor;
}

void set_cursor_(struct cursor file_cursor, int start_point)
{
	printf("\e[%d;%dH",(file_cursor.ln-start_point)+4,file_cursor.col+1);
}

void delete_pointer(char **pointer, int pointer_n)
{
	for (int i = 0; i < pointer_n; i++) {
		delete pointer[i];
	}
	delete pointer;
}

struct cursor delete_line(char **lines, char **backup, struct cursor file_cursor, unsigned int nlines)
{
	file_cursor.col = strlen(backup[file_cursor.ln-1]);
	for (unsigned int i = 0, x = 0; i < nlines; i++) {
		if (i != file_cursor.ln) {
			strcpy(lines[x++], backup[i]);
		}
	}
	file_cursor.ln--;
	return file_cursor;
}

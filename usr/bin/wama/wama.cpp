/*
 * Copyright (C) 2016, 2017 Daniel Martín [amaya@amayaos.com]
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

#define ADV_MODE 1

#define UP_KEY 'w'
#define DOWN_KEY 's'
#define LEFT_KEY 'a'
#define RIGHT_KEY 'd'
#define CLOSE_KEY 'x'
#define COUNT_KEY 'c'
#define SAVE_KEY 'v'
#define SEARCH_KEY 'f'

struct cursor put_char(char key, char **lines, struct cursor file_cursor);

struct cursor add_line(char **lines, char **backup, struct cursor file_cursor, unsigned int nlines);

void set_cursor_(struct cursor file_cursor, int start_point);

struct cursor delete_line(char **lines, char **backup, struct cursor file_cursor, unsigned int nlines);

void delete_pointer(char **pointer, int pointer_n);

unsigned int longestLine(char *data);

int wama_main(char *path)
{
	char prog[] = "Wama 0.8\0";
	int ret = 0;
	int optpos = 0;
	clean_screen();
	up_bar(prog, 25, path, 35);
	down_bar(optpos);
	int file_status;
	switch ((file_status = checkFile(path))) {
		case 1:
			add_message("Error: Not a text file");
			break;
		case CREATE_FILE:
			break;
		default:
			add_message(strerror(file_status));
			ret = -1;
			break;
	}
	char *data;
	unsigned int nlines;
	char **lines;
	char search[60] = { '\0' };
	int start_point = 0;
	struct cursor file_cursor;
	file_cursor.ln = 0;
	file_cursor.col = 0;
	if (file_status == 0 || file_status == CREATE_FILE) data = read_file(path);
	if ((file_status == 0 || file_status == CREATE_FILE) && data != NULL) {
		nlines = linecounter(&data[0]);
		char msg[64];
		snprintf(msg, 64, "Read %d lines", nlines);
		add_message(msg);
		if (!nlines) nlines++;
		unsigned int MaxLenght = longestLine(&data[0]);
		lines = new char*[nlines];
		for (unsigned int i = 0; i < nlines; i++) {
			lines[i] = new char[MaxLenght];
		}
		separate_in_lines(data, lines, nlines);
		delete data;
		print_content(lines, file_cursor, nlines);
		int exit = 0;
		char key;
		while (!exit) {
			start_point = get_start_point(file_cursor.ln);
			set_cursor_(file_cursor, start_point);
			key = getchar();
			if (key == '\t') {
				optpos ^= 1;
				down_bar(optpos);
				set_cursor_(file_cursor, start_point);
			}
			if (optpos > 1) {
				printf("\e[25;%dH", ((optpos-2)*15+2));
			}
			if (!optpos && key != '\t') {
				if (key == '\n') {
					char **LinesBackup = new char*[nlines];
					for (unsigned int i = 0; i < nlines; i++) {
						unsigned int lSize = strlen(lines[i]);
						if (++lSize > MaxLenght) MaxLenght = lSize;
					}
					for (unsigned int i = 0; i < nlines; i++) {
						LinesBackup[i] = new char[MaxLenght];
						strlcpy(LinesBackup[i], lines[i], MaxLenght);
						delete lines[i];
					}
					delete lines;
					lines = new char*[++nlines];
					for (unsigned int i = 0, x = 0; i < nlines; i++) {
						lines[i] = new char[MaxLenght];
						if (i != file_cursor.ln) {
							strlcpy(lines[i], LinesBackup[x++], MaxLenght);
						}
						else {
							strlcpy(lines[i], LinesBackup[x], file_cursor.col+1);
							lines[++i] = new char[MaxLenght];
							strlcpy(lines[i], &LinesBackup[x++][file_cursor.col], MaxLenght);
						}
						delete LinesBackup[x-1];
					}
					delete LinesBackup;
					file_cursor.ln++;
					file_cursor.col = 0;
				}
				else if (key == '\b' && file_cursor.col != 0) {
					int LineSize = strlen(lines[file_cursor.ln]);
					char *LineBackup = new char[++LineSize];
					strlcpy(LineBackup, lines[file_cursor.ln], LineSize);
					delete lines[file_cursor.ln];
					lines[file_cursor.ln] = new char[LineSize];
					strlcpy(lines[file_cursor.ln], LineBackup, file_cursor.col);
					strlcpy(&lines[file_cursor.ln][strlen(lines[file_cursor.ln])], &LineBackup[file_cursor.col], LineSize-file_cursor.col);
					delete LineBackup;
					file_cursor.col--;
				}
				else if (key == '\b' && file_cursor.col == 0 && file_cursor.ln > 0) {
					char **LinesBackup = new char*[nlines];
					for (unsigned int i = 0; i < nlines; i++) {
						unsigned int lSize = strlen(lines[i]);
						if (++lSize > MaxLenght) MaxLenght = lSize;
					}
					for (unsigned int i = 0; i < nlines; i++) {
						LinesBackup[i] = new char[MaxLenght];
						strlcpy(LinesBackup[i], lines[i], MaxLenght);
						delete lines[i];
					}
					delete lines;
					lines = new char*[--nlines];
					if (strlen(LinesBackup[file_cursor.ln])+strlen(LinesBackup[file_cursor.ln-1]) > MaxLenght) MaxLenght = strlen(LinesBackup[file_cursor.ln])+strlen(LinesBackup[file_cursor.ln-1])+1;
					for (unsigned int i = 0, x = 0; i < nlines; i++) {
						lines[i] = new char[MaxLenght];
						if (i == file_cursor.ln) {
							strlcpy(&lines[i-1][strlen(lines[i-1])], LinesBackup[x++], MaxLenght-strlen(lines[i-1]));
						}
						strlcpy(lines[i], LinesBackup[x++], MaxLenght);
						delete LinesBackup[x-1];
					}
					delete LinesBackup;
					file_cursor.ln--;
					file_cursor.col = strlen(lines[file_cursor.ln]);
				}
				else if (key != '\b') {
					int LineSize = strlen(lines[file_cursor.ln]);
					char *LineBackup = new char[++LineSize];
					strlcpy(LineBackup, lines[file_cursor.ln], LineSize);
					delete lines[file_cursor.ln];
					lines[file_cursor.ln] = new char[++LineSize];
					strlcpy(lines[file_cursor.ln], LineBackup, file_cursor.col+1);
					LineSize = strlen(lines[file_cursor.ln]);
					lines[file_cursor.ln][LineSize] = key;
					lines[file_cursor.ln][LineSize+1] = '\0';
					strcat(lines[file_cursor.ln], &LineBackup[file_cursor.col]);
					delete LineBackup;
					file_cursor.col++;
				}
				print_content(lines, file_cursor, nlines);
			}
			else if (optpos == ADV_MODE) {
				if (key == UP_KEY) {
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
					print_content(lines, file_cursor, nlines);
				}
				else if (key == RIGHT_KEY) {
					if (file_cursor.col < strlen(lines[file_cursor.ln])) {
						file_cursor.col++;
					}
					else if ((file_cursor.ln+1) < nlines) {
						file_cursor.ln++;
						file_cursor.col = 0;
					}
					print_content(lines, file_cursor, nlines);
				}
				else if (key == CLOSE_KEY) exit = 1;
				else if (key == COUNT_KEY) {
					clean_message_line();
					printf("\e[24;30H[Line: %d Col: %d]",
					file_cursor.ln+1, file_cursor.col+1);
					set_cursor_(file_cursor, start_point);
				}
				else if (key == SEARCH_KEY) {
					get_string(search,60);
					if (search[0] != '\0') {
						file_cursor = findString(search,lines,nlines,file_cursor);
						print_content(lines,file_cursor,nlines);
						start_point = get_start_point(file_cursor.ln);
					}
					else set_cursor_(file_cursor, start_point);
				}
				else if (key == SAVE_KEY) {
					update_file_content(path, lines, nlines);
				}
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
	printf("\e[%d;%dH",(file_cursor.ln-start_point)+4, (file_cursor.col < 79) ? file_cursor.col+1 : (file_cursor.col < 157) ? (file_cursor.col-((file_cursor.col/79)*79)+2) : (file_cursor.col-79-(((file_cursor.col-79)/78)*78)+2));
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

unsigned int longestLine(char *data)
{
	unsigned int longest_line = 0;
	unsigned int linelenght = 0;
	for (unsigned int i = 0; data[i] != '\0'; i++) {
		if (data[i] == '\n') {
			if (linelenght > longest_line) longest_line = linelenght;
			linelenght = 0;
		}
		else linelenght++;
	}
	if (linelenght > longest_line) longest_line = linelenght;
	/* Add one char to store character 0 */
	return ++longest_line;
}

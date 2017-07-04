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
#include "wama.h"

void clean_screen()
{
	char str[] = {0x1b, 0x5b, 0x48, 0x1b, 0x5b, 0x4a, '\0'};
	printf("%s", str);
}

void up_bar(char *str1, int sp1, char *str2, int sp2)
{
	char bar[81];
	for (int i = 0; i < 80; i++) {
		bar[i] = 219;
	}
	bar[80] = '\0';
	printf("\e[1;1H%s\n%c\e[2;%dH\e[32m%s\e[2;%dH\e[33mFile: %s\e[2;80H\e[m%c\n%s", bar, 179, sp1, str1, sp2, str2, 179, bar);
}

void down_bar(int optpos)
{
	char clean[81];
	for (int i = 0; i < 80; i++) {
		clean[i] = ' ';
	}
	clean[80] = '\0';
	if (!optpos) {
		printf("\e[25;1H%s\e[25;1H[TAB] Set Advanced Options Mode\e[1;1H", clean);
	}
	else
		printf("\e[25;1H%s\e[25;1H[TAB] Set Edit Mode \e[25;22HE[\e[31mx\e[m]it\e[25;32HSa[\e[32mv\e[m]e\e[25;42H[\e[33mC\e[m]ounter\e[25;52H[\e[34mF\e[m]ind\e[25;60H[\e[35mWASD\e[m] File Scroll\e[1;1H", clean);
}

void clean_message_line()
{
	char clean[81];
	for (int i = 0; i < 80; i++) {
		clean[i] = ' ';
	}
	clean[80] = '\0';
	printf("\e[24;1H%s", clean);
}

void add_message(char *msg)
{
	clean_message_line();
	printf("\e[24;%dH[%s]", ((80-strlen(msg))/2), msg);
}

void clean_lines_screen()
{
	char clean[81];
	for (int i = 0; i < 80; i++) {
		clean[i] = ' ';
	}
	clean[80] = '\0';
	for (int i = 4; i < 24; i++) {
		printf("\e[%d;1H%s", i, clean);
	}
}

int get_start_point(int line)
{
	return (line/20)*20;
}

void print_content(char **lines, struct cursor file_cursor, int n_lines)
{
	clean_lines_screen();
	int start_point = get_start_point(file_cursor.ln);
	printf("\e[4;1H");
	for (int i = start_point; i < n_lines && i < (start_point+20); i++) {
		if (strlen(lines[i]) <= 80) printf("%s\n", lines[i]);
		else if (file_cursor.ln != (unsigned)i || file_cursor.col < 79) {
			char outline[80];
			strlcpy(outline, lines[i], 80);
			outline[79] = '$';
			outline[80] = '\0';
			printf("%s\n", outline);
		}
		else {
			char outline[80] = "$\0";
			strncat(outline, &lines[i][(file_cursor.col < 157) ? ((file_cursor.col/79)*79) : ((file_cursor.col/78)*78)+1], 79);
			if (strlen(lines[i]) > ((file_cursor.col/80)*80)+79) {
				outline[79] = '$';
				outline[80] = '\0';
			}
			printf("%s\n", outline);
		}
	}
	printf("\e[%d;%dH", ((file_cursor.ln-start_point)+4), (file_cursor.col < 79) ? (file_cursor.col-((file_cursor.col/80)*80)+1) : (file_cursor.col < 157) ? (file_cursor.col-((file_cursor.col/79)*79)+2) : (file_cursor.col-79-((file_cursor.col-79)/78)*78+2));
}

void get_string(char *str, unsigned int max)
{
	char string[128 + max];
	int point = strlen(str);
	char key;
	clean_message_line();
	printf("\e[24;1HFind: %s", str);
	while (strlen(string) < max) {
		key = getchar();
		switch (key) {
			case '\b':
				if (point > 0) {
					string[--point] = '\0';
					printf("\b \b");
				}
				break;
			case '\n':
				string[point] = '\0';
				strcpy(str, string);
				clean_message_line();
				if (point == 0) add_message("Canceled");
				return;
				break;
			default:
				string[point++] = key;
				printf("%c", key);
				break;
		}
	}
}

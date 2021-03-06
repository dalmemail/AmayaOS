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
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>

#define VERSION "1.1"

#define MANUAL_PAGES_PATH "/usr/share/man/"

/* Some of these functions come from Wama 0.7  http://git.amayaos.com */

void clean_screen()
{
	char str[] = {0x1b, 0x5b, 0x48, 0x1b, 0x5b, 0x4a, '\0'};
	printf("%s", str);
}

int linecounter(char *c)
{
	int n_lines = 0;
	for (int i = 0; c[i] != '\0'; i++) {
		if (c[i] == '\n') {
			n_lines++;
		}
	}
	return n_lines;
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

char *read_file(char *path)
{
	int file_size = get_size(path);
	char *data = new char [file_size];
	int fd = open(path, O_RDONLY);
	read(fd, data, file_size);
	close(fd);
	return data;
}

int line_navigator(char *path, char *doc_page)
{
	int ret = 0;
	char *data = read_file(path);
	int n_lines = linecounter(data);
	int act_line = 0;
	char **lines;
	lines = new char *[n_lines];
	lines[0] = &data[0];
	int data_len = strlen(data);
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
			ret = 1;
			char char_read[2];
			do {
				clean_screen();
				int start_line = act_line;
				if (start_line > (n_lines-22) && n_lines >= 22) {
					start_line = (n_lines-22);
				}
				if (n_lines < 22) {
					start_line = 0;
				}
				for (int i = start_line; i < (start_line+22) && i < n_lines; i++) {
					printf("%s\n", lines[i]);
				}
				printf("\n\nManual page for %s line %d "
				"(press 'h' for help or 'q' to exit)", doc_page, act_line+1);
				read(0, char_read, 1);
				if (char_read[0] == 'e' && act_line < n_lines) {
					act_line++;
				}
				if (char_read[0] == 'y' && act_line > 0) {
					act_line--;
				}
				if (char_read[0] == 'm') {
					char line[8];
					clean_screen();
					printf("Move to line: ");
					gets_s(line, 8);
					int line_to_move = atoi(line);
					if (line_to_move > 0 && line_to_move < n_lines) {
						act_line = (line_to_move-1);
					}
				}
				if (char_read[0] == 'h') {
					clean_screen();
					printf("\e[9;32HSUMMARY OF LESS COMMANDS\n");
					printf("\e[10;30Hh\t\tDisplay this help\n");
					printf("\e[11;30Hq\t\tExit\n");
					printf("\e[12;40HMOVING\n");
					printf("\e[13;30He\t\tForward one line\n");
					printf("\e[14;30Hy\t\tBackward one line\n");
					printf("\e[15;30Hm\t\tMove to 'n' line\n");
					printf("\e[17;35HPress 'q' when done\e[1;1H");
					while (getchar() != 'q');
				}
			} while(char_read[0] != 'q');
			clean_screen();
		}
	}
	delete lines;
	delete data;
	return ret;
}

int main(int argc, char **argv)
{
	int ret = 0;
	char manual_path[128];
	if (argc == 2) {
		if ((strcmp(argv[1], "--version")) == 0) {
			printf("AmayaOS Man %s\n", VERSION);
		}
		else if (argv[1][0] == '-') {
			printf("Error: Invalid option '%s'\n", argv[1]);
		}
		else {
			strlcpy(manual_path, MANUAL_PAGES_PATH, 128);
			strcat(manual_path, argv[1]);
			if (line_navigator(manual_path, argv[1]) <= 0) {
				printf("No manual entry for %s\n", argv[1]);
				ret = 1;
			}
		}
	}
	else if (argc == 1) {
		printf("You must specify the man page to display\n");
	}
	return ret;
}

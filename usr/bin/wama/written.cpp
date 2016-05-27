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
#include <string.h>
#include <sys/stat.h>
#include "wama.h"
#include "written.h"

#define NEW_FILE_MODE 0
#define EDIT_FILE_MODE 1

/* mode 0 new file
 * mode 1 edit file
 */
int wama_file(int mode)
{
	char path[128];
	clean_screen();
	printf("Ruta del archivo: ");
	gets_s(path, 128);
	clean_screen();
	if (path[0] != '/') {
		char dev_path[128] = "/dev/";
		strcat(dev_path, path);
		strcpy(path, dev_path);
	}
	/* creamos el archivo 'path' */
	if ((touch(path, S_IRUSR | S_IWUSR)) < 0 && mode == NEW_FILE_MODE) {
		return -1;
	}
	int line_count = 1;
	char line[128];
	int fd;
	if ((fd = open(path, O_WRONLY)) < 0) {
		return -1;
	}
	if (mode == EDIT_FILE_MODE) {
		char *ch = read_file(path);
		write(fd, ch, strlen(ch));
		line_count = linecounter(ch);
		line_count++;
	}
	printf("\n\n\n %d ", line_count);
	while ( 1 ) {
		setwindow();
		gets_s(line, 128);
		switch (checkWamaCommand(line)) {
			case 0:
				write(fd, line, strlen(line));
				write(fd, "\n", 1);
				break;
			case 2:
				close(fd);
				return 0;
				break;
			case 1:
				close(fd);
				if ((line_navigator(path, WRITE_MODE)) < 0) {
					return -1;
				}
				line_count--;
				char *data = read_file(path);
				if ((fd = open(path, O_WRONLY)) < 0) {
					return -1;
				}
				write(fd, data, strlen(data));
				delete data;
				break;
		}
		line_count++;
		printf(" %d ", line_count);
	}
}

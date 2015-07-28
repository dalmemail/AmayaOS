/*
 * Copyright (C) 2015 Dan Rulos [amaya@amayaos.com]
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

int new_wama_file()
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
	if ((touch(path, S_IRUSR | S_IWUSR)) < 0) {
		return -1;
	}
	int line_count = 1;
	char line[128];
	int fd;
	if ((fd = open(path, O_WRONLY)) < 0) {
		return -1;
	}
	printf("\n\n\n %d ", line_count);
	char *data;
	while ( 1 ) {
		setwindow();
		subwindow(line_count);
		gets_s(line, 128);
		switch (checkWamaCommand(line)) {
			case 0:
				write(fd, line, strlen(line));
				write(fd, "\n", 1);
				break;
			case 1:
				close(fd);
				if (goto_wama_command(path) < 0) {
					return -1;
				}
				data = read_file(path);
				if ((fd = open(path, O_WRONLY)) < 0) {
					return -1;
				}
				write(fd, data, strlen(data));
				line_count--;
				break;
			case 2:
				close(fd);
				return 0;
				break;
		}
		line_count++;
		printf(" %d ", line_count);
	}
}

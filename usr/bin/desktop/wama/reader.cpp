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
#include <unistd.h>
#include "wama.h"
#include "reader.h"
 
int read_wama_file()
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
	int file = open(path, O_RDONLY);
	if (file < 0) {
		return file;
	}
	char data[4];
	int file_size = get_size(path);
	printf("\n\n");
	int linecount = 0;
	char key = 's';
	for (int i = 0; i < file_size && key != 'n'; i++) {
		read(file, data, 1);
		printf("%c", data[0]);
		if (data[0] == '\n') {
			linecount++;
		}
		if (linecount == 20) {
			linecount = 0;
			do {
				printf("\nContinue? [S/N]\n");
				setwindow();
				key = getchar();
			} while (key != 's' && key != 'n');
		}
		if (i+1 == file_size) {
			printf("\nPRESS ANY KEY TO EXIT\n");
			setwindow();
			getchar();
		}
	}
	close(file);
	return 0;
}

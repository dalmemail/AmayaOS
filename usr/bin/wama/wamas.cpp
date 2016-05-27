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
#include "reader.h"
#include "written.h"
#include "wama.h"
#include "wamas.h"

#define NEW_FILE 0
#define EDIT_FILE 1
#define READ_FILE 2

#define VERSION "0.7"

int main(int argc, char **argv)
{
	int mode = EDIT_FILE;
	int ret = 0;
	int file_id = 0;
	if (argc > 2) {
		for (int i = 1; i < argc; i++) {
			if ((strcmp(argv[i], "-r") == 0)) {
				mode = READ_FILE;
			}
			else if ((strcmp(argv[i], "-n")) == 0) {
				mode = NEW_FILE;
			}
			else if ((strcmp(argv[i], "-e")) == 0) {
				mode = EDIT_FILE;
			}
			else if (argv[i][0] != '-') {
				file_id = i;
			}
		}
	}
	else if (argc == 2 && (strcmp(argv[1], "--version") == 0)) {
		printf("Wama %s\n", VERSION);
	}
	else if (argc == 2 && (strcmp(argv[1], "--help") == 0)) {
		printf("Uso: %s [OPCION] ARCHIVO\n", argv[0]);
		printf("--help\tMuestra esta ayuda\n");
		printf("--version\tMuestra la version de Wama\n");
		printf("-r\tAbre el archivo en modo lectura\n");
		printf("-e\tAbre un archivo ya existente para editarlo\n");
		printf("-n\tCrea un nuevo archivo y lo edita\n");
	}
	else {
		printf("Uso: %s [OPCION] ARCHIVO\n", argv[0]);
	}
	if (file_id != 0) {
		switch (mode) {
			case READ_FILE:
				ret = read_wama_file(argv[file_id]);
				break;
			case EDIT_FILE:
				ret = wama_file(EDIT_FILE, argv[file_id]);
				break;
			case NEW_FILE:
				ret = wama_file(NEW_FILE, argv[file_id]);
				break;
		}
	}
	return ret;
}

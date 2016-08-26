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
#include <unistd.h>
#include "wama.h"

#define VERSION "0.8"

void help(void);
void version(void);

int main(int argc, char **argv)
{
	int ret = 0;
	int hflag = 0;
	int vflag = 0;
	char *file_path = (char *)NULL;
	char path[256];
	for (int i = 1; i < argc; i++) {
		if (strcmp(argv[i], "--help") == 0) {
			hflag = 1;
		}
		else if (strcmp(argv[i], "--version") == 0) {
			vflag = 1;
		}
		else if (argv[i][0] != '-') {
			if (argv[i][0] != '/') {
				getcwd(path, 256);
				if (path[1] != '\0') strcat(path, "/");
				strcat(path, argv[i]);
				file_path = &path[0];
			}
			else file_path = &argv[i][0];
		}
		else {
			printf("Opci%cn no reconocida: %s\n", 162, argv[i]);
			hflag = 1;
			ret = EXIT_FAILURE;
		}
	}
	if (hflag) {
		help();
	}
	else if (vflag) {
		version();
	}
	else {
		ret = wama_main(file_path);
	}
	return ret;
}

void help(void)
{
	printf("Uso: wama [OPCIONES] [FICHERO]\n");
	printf("\n--help\t\tMuestra esta ayuda y cierra\n");
	printf("--version\tMuestra la versi%cn y cierra\n", 162);
}

void version(void)
{
	printf("Wama v%s\n", VERSION);
}

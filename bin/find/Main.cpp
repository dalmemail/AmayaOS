/*
 * Copyright (C) 2015, 2017 Daniel Martín [amaya@amayaos.com]
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

#include "find.h"

#define HELP_FLAG 0
#define VERSION_FLAG 1
#define O_FLAG 2

void fhelp(void) {
	printf("find (AmayaOS findutils) 0.2\nUsage: find [ARGS] [PATH] [OPTIONS]\n");
	printf("ARGS:\n\t--help     \tPrints this help\n\t--version  \tPrints find version\n");
	printf("OPTIONS:\n\t-name [FILENAME] Prints all the files called 'FILENAME' that are located\n\t\t\t in 'PATH'\n");
}

void fversion(void) {
	printf("find (AmayaOS findutils) 0.2\n");
}

int main(int argc, char **argv)
{
	int ret = EXIT_SUCCESS;
	int flags[3] = { 0,0,0 };
	char fpath[128] = "\0";
	struct find_params params = {0,(char *)NULL};
	for (int i = 1; i < argc && !ret; i++) {
		if (strcmp(argv[i], "--help") == 0) flags[HELP_FLAG] = 1;
		else if (strcmp(argv[i], "--version") == 0) flags[VERSION_FLAG] = 1;
		else if (strcmp(argv[i], "-name") == 0) {
			if ((i+1) >= argc || argv[i+1][0] == '/') {
				printf("%s: A filename is required to use the '-name' argument\n", argv[0]);
				ret = EXIT_FAILURE;
			}
			else {
				params.fname = 1;
				params.name = &argv[++i][0];
			}
			flags[O_FLAG] = 1;
		}
		else if (argv[i][0] == '-') {
			printf("%s: '%s' is not a valid argument\n", argv[0], argv[i]);
			ret = EXIT_FAILURE;
		}
		else {
			if (!flags[O_FLAG] && argv[i][0] == '/') strcpy(fpath, argv[i]);
			else if (!flags[O_FLAG] && getcwd(fpath, sizeof(fpath)) != NULL) {
				strcat(fpath, "/");
				strcat(fpath, argv[i]);
			}
			else {
				printf("%s: paths must precede expression\n", argv[0]);
				ret = EXIT_FAILURE;
			}
		}
	}
	if (!ret && !fpath[0]) {
		if (getcwd(fpath, sizeof(fpath)) == NULL) {
			printf("Error: %s\n", strerror(errno));
			ret = EXIT_FAILURE;
		}
	}
	if (!ret) {
		if (flags[HELP_FLAG]) fhelp();
		else if (flags[VERSION_FLAG]) fversion();
		else ret = find(fpath, params);
	}
	return ret;
}

/*
 * Copyright (C) 2016, 2017 Daniel Martín
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
#include <unistd.h>
#include "commander.h"

#define VERSION "0.2"

void help();

int main(int argc, char **argv)
{
	char cwd[512];
	getcwd(cwd, sizeof(cwd));
	char *path = &cwd[0];
	int hflag = 0;
	for (int i = 1; i < argc; i++) {
		if (argv[i][0] != '-') {
			path = &argv[i][0];
		}
		else if ((strcmp(argv[i], "--help") == 0)) {
			hflag = 1;
		}
	}
	if (path[0] != '/') {
		strcat(cwd, "/");
		strcat(cwd, path);
		path = &cwd[0];
	}
	if (hflag) {
		help();
	}
	else {
		commander(path, cwd);
	}
	return 0;
}

void help()
{
	printf("Amaya File Commander v%s\n", VERSION);
	printf("Uso: commander /path\n");
	printf("--help\tMuestra esta ayuda\n");
}

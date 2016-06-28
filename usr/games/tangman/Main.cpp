/*
 * Copyright (C) 2016 Dan Rulos
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
#include <string.h>
#include <fcntl.h>
#include "tangman.h"

#define VERSION "0.3"

#define FALSE_ 0
#define TRUE_ 1

void version();
void help();

int main(int argc, char **argv)
{
	int vflag = FALSE_;
	int hflag = FALSE_;
	int fd;
	int ret = 0;
	char default_word_database[] = "/etc/tangman/database";
	char *word_database_path = &default_word_database[0];
	for (int i = 1; i < argc; i++) {
		if ((strcmp(argv[i], "--version")) == 0) {
			version();
			vflag = TRUE_;
		}
		else if ((strcmp(argv[i], "--help")) == 0) {
			help();
			hflag = TRUE_;
		}
		else if ((fd = open(argv[i], O_RDONLY)) >= 0) {
			close(fd);
			word_database_path = &argv[i][0];
		}
		else {
			ret = 1;
		}
	}
	if (!vflag && !hflag) {
		tangman(word_database_path);
		clean_screen();
	}
	return ret;
}

void version()
{
	printf("Version: %s\n", VERSION);
}

void help()
{
	printf("Uso: tangman /path/to/word_database_file\n");
	printf("--version\tMuestra la version\n");
	printf("--help\tMuestra esta ayuda\n");
}

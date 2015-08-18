/*
 * Copyright (C) 2015 Dan Rulos.
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
#include <unistd.h>
#include <sys/stat.h>

int f_size(char *path)
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

void grep(char *string, char *c, int n_bytes)
{
	int final_pos = 0;
	bool exists = false;
	for (int i = 0; i < n_bytes; i++) {
		int start_check;
		for (unsigned int x = 0; c[i] != '\n' && i < n_bytes; i++) {
			if (string[x] == c[i] && !exists) {
				if (x++ == 0) {
					start_check = i;
				}
				if (x == strlen(string)) {
					exists = true;
				}
			}
			else if (!exists) {
				x = 0;
			}
		}
		if (exists) {
			final_pos = i;
			while (c[i-1] != '\n' && i > 0) {
				i--;
			}
			while (i <= final_pos) {
				printf("%c", c[i++]);
			}
		}
		exists = false;
	}
}

int main(int argc, char **argv)
{
	int ret = EXIT_SUCCESS;
	if (argc != 3) {
		printf("Uso: %s cadena archivo\r\n", argv[0]);
		ret = EXIT_FAILURE;
	}
	else {
		int fsize = f_size(argv[2]);
		char *buffer = new char [fsize];
		int fd;
		if ((fd = open(argv[2], O_RDONLY)) < 0) {
			printf("Error al leer '%s'\n", argv[2]);
			ret = EXIT_FAILURE;
		}
		else {
			read(fd, buffer, fsize);
			grep(argv[1], buffer, fsize);
		}
		close(fd);
		delete buffer;
	}
	return ret;
}

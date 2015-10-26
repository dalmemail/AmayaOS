/*
 * Copyright (C) 2015 Dan Rulos
 *      amaya@amayaos.com
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
#include <sys/stat.h>
#include <stdlib.h>

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
	/* Devolvemos el contenido del fichero */
	return data;
}

int main(int argc, char **argv)
{
	char *ch = read_file("/dev/sh_history");
	printf("1 ");
	for (int i = 0, nl = 1; ch[i] != '\0'; i++) {
		printf("%c", ch[i]);
		if (ch[i] == '\n') {
			printf("%d ", ++nl);
		}
	}
	printf("\b\b");
	return 0;
}

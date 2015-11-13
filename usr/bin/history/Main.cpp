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

int main(int argc, char **argv)
{
	int file_size = get_size("/dev/sh_history");
	char data[file_size];
	int fd;
	if ((fd = open("/dev/sh_history", O_RDONLY)) < 0) {
		printf("Error: /dev/sh_history Not Found\n");
		return -1;			
	}
	read(fd, data, file_size);
	close(fd);
	printf("1 ");
	for (int i = 0, nl = 1; i < file_size; i++) {
		printf("%c", data[i]);
		if (data[i] == '\n' && i != (file_size-1)) {
			printf("%d ", ++nl);
		}
	}
	return 0;
}

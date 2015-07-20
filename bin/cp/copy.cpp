/*
 * Copyright (C) 2015 Dan Rulos
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
#include <errno.h>
#include <sys/stat.h>
#include <unistd.h>
#include "copy.h"

int copy_file(char *originalpath, char *destination)
{
	/* the file 'originalpath' */
	FILE *file1;
	/* the file 'destination' */
	int fd;
	/* buffer to save originalpath's contains */
	char buffer[2048];
	/* number of bytes read */
	int n_bytes = 0;
	/* open origin file to read it */
	if ((file1 = fopen(originalpath, "r")) == NULL) {
		printf("El archivo de origen '%s' no existe\n", originalpath);
		return EXIT_FAILURE;
	}
	/* make the file 'destination' */
	touch(destination, S_IWUSR | S_IRUSR);
	/* open destination to write */
	if ((fd = open(destination, O_WRONLY)) < 0) {
		printf("Error al abrir '%s': %s\n", destination, strerror(errno));
		return errno;
	}
	/* read file1 data */
	n_bytes = fread(buffer, 1, sizeof(buffer), file1);
	/* write file1 data to fd */
	write(fd, buffer, n_bytes);
	/* close file1 and fd */
	fclose(file1);
	close(fd);
	/* all OK */
	return EXIT_SUCCESS;
}

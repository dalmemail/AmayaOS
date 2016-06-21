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
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <unistd.h>
#include "copy.h"

int copy_file(char *originalpath, char *destination)
{
	int ret = EXIT_SUCCESS;
	/* the file 'originalpath' */
	int read_fd;
	/* the file 'destination' */
	int write_fd;
	/* get file information */
	struct stat st;
	if ((stat(originalpath, &st)) < 0) {
		printf("Error al leer '%s': %s\n", originalpath, strerror(errno));
		ret = errno;
	}
	if ((write_fd = open(destination, O_RDONLY)) < 0) {
		/* make the file 'destination' if it not exists */
		if ((touch(destination, S_IRUSR | S_IWUSR)) < 0) {
			printf("Error al crear '%s': %s\n", destination, strerror(errno));
			ret = errno;
		}
	}
	else {
		close(write_fd);
	}
	/* open destination to write */
	if ((write_fd = open(destination, O_WRONLY)) < 0) {
		printf("Error al abrir '%s': %s\n", destination, strerror(errno));
		ret = errno;
	}
	else if ((read_fd = open(originalpath, O_RDONLY)) >= 0) {
		int fsize = st.st_size;
		char *data = new char [fsize];
		read(read_fd, data, fsize);
		write(write_fd, data, fsize);
		delete data;
	}
	else {
		printf("Error al abrir '%s': %s\n", originalpath, strerror(errno));
		ret = errno;
	}
	/* close read_fd and write_fd */
	close(read_fd);
	close(write_fd);
	/* all OK */
	return ret;
}

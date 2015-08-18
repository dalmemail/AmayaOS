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

int copy_file(char *originalpath, char *destination)
{
	int ret = EXIT_SUCCESS;
	/* the file 'originalpath' */
	int read_fd;
	/* the file 'destination' */
	int write_fd;
	/* make the file 'destination' */
	if ((touch(destination, S_IWUSR | S_IRUSR)) < 0) {
		printf("Error al crear '%s': %s\n", destination, strerror(errno));
		ret = errno;
	}
	/* open destination to write */
	else if ((write_fd = open(destination, O_WRONLY)) < 0) {
		printf("Error al abrir '%s': %s\n", destination, strerror(errno));
		ret = errno;
	}
	else if ((read_fd = open(originalpath, O_RDONLY)) >= 0) {
		int fsize = f_size(originalpath);
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

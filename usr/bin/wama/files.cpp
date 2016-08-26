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

#include <sys/stat.h>
#include "interface.h"

int checkFile(const char *path)
{
	int ret = 0;
	struct stat st;
	if ((stat(path, &st)) < 0) {
		ret = errno;
	}
	else if (!S_ISREG(st.st_mode)) {
		ret = 1;
	}
	return ret;
}

int file_size(const char *path)
{
	int fsize = 0;
	struct stat st;
	if ((stat(path, &st)) < 0) {
		fsize = -1;
	}
	else fsize = st.st_size;
	return fsize;
}

char *read_file(const char *path)
{
	int path_size = file_size(path);
	char *data = (char *)NULL;
	int fd;
	if (path_size >= 0) {
		if ((fd = open(path, O_RDONLY)) >= 0) {
			data = new char[path_size];
			read(fd, data, path_size);
			close(fd);
		}
		else {
			add_message(strerror(errno));
		}
	}
	return data;
}

int linecounter(const char *data)
{
	int nlines = 0;
	for (int i = 0; data[i] != '\0'; i++) {
		if (data[i] == '\n') {
			nlines++;
		}
	}
	return nlines;
}

void separate_in_lines(char *data, char **lines, int n_lines)
{
	/*for (int i = 0, x = 0, y = 0; data[x] != '\0'; x++) {
		if (data[x] == '\n' && i < n_lines) {
			y = 0;
			i++;
		}
		else if (y < 80) {
			lines[i][y++] = data[x];
		}
	}*/
	char **l = new char*[n_lines];
	l[0] = &data[0];
		for (int i = 1, x = 0; data[x] != '\0'; x++) {
			if (data[x] == '\n') {
				data[x] = '\0';
				if (i < n_lines) {
					l[i] = &data[x+1];
				}
				i++;
			}
		}
	for (int i = 0; i < n_lines; i++) {
		strcpy(lines[i], l[i]);
	}
	delete l;

}

void update_file_content(const char *path, char **lines, int nlines)
{
	int fd;
	int fsize = file_size(path);
	int size_wrote = 0;
	if ((fd = open(path, O_WRONLY)) >= 0) {
		for (int i = 0; i < nlines; i++) {
			size_wrote += write(fd, lines[i], strlen(lines[i]));
			write(fd, "\n", 1);
			size_wrote++;
		}
		if (size_wrote < fsize) {
			while (size_wrote++ < fsize) {
				write(fd, "\0", 1);
			}
		}
		close(fd);
		add_message("Guardado Correctamente");
	}
	else {
		add_message(strerror(errno));
	}
}

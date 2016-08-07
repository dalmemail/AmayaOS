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

#include "files.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>

unsigned int countFiles(char *path);

struct dir_entry *get_dir_content(char *path, int n_files)
{
	DIR *directory;
	struct dirent *dent;
	struct stat st;
	struct dir_entry *dir_content;
	char tmp[256];
	if (!(directory = opendir(path))) {
	}
	else {
		dir_content = (struct dir_entry*)malloc((n_files+1) * sizeof(struct dir_entry));
		strcpy(dir_content[0].file_name, "..");
		dir_content[0].fileType = DIRECTORY;
		int i = 1;
		while ((dent = readdir(directory)) && i < (n_files+1)) {
			if (dent->d_name[0] != '.') {
				strcpy(dir_content[i].file_name, dent->d_name);
				switch (dent->d_type) {
				    case DT_DIR:
					dir_content[i].fileType = DIRECTORY;
					break;

				    case DT_BLK:
				    case DT_CHR:
					dir_content[i].fileType = CHARACTER_DEVICE;
					break;
				
				    case DT_REG:
				    default:
					/* Construimos la ruta completa. */
					snprintf(tmp, sizeof(tmp),
						"%s/%s", path, dent->d_name);

					/* Es un ejecutable? */
					if (stat(tmp, &st) != -1 && st.st_mode & 0100)
					    dir_content[i].fileType = EXECUTABLE;
					else
					    dir_content[i].fileType = TEXTFILE;
				}
				i++;
			}
		}
	}
	return dir_content;
}

unsigned int countFiles(char *path)
{
	int n_files = 0;
	DIR *dir1;
	if ((dir1 = opendir(path))) {
		struct dirent *dent;
		while ((dent = readdir(dir1))) {
			if (dent->d_name[0] != '.') {
				n_files++;
			}
		}
		closedir(dir1);
	}
	return n_files;
}

char *search_parent(char *path)
{
	int i;
	int path_size = strlen(path);
	for (i = (path_size-1); path[i] != '/'; i--) {
		path[i] = '\0';
	}
	if (i != 0) {
		path[i] = '\0';
	}
	return &path[0];
}

char *get_last_path(char *path, char *last_dir_selected)
{
	int path_size = strlen(path);
	for (int i = path_size-strlen(last_dir_selected); i < (path_size-1); i++) {
		path[i] = '\0';
	}
	path_size = strlen(path);
	if (path_size > 1) {
		path[(path_size-1)] = '\0';
	}
	return &path[0];
}

char *makePath(char *path, char *filename, char *file_path)
{
	strcat(file_path, path);
	if (strcmp(path, "/") != 0) {
		strcat(file_path, "/");
	}
	strcat(file_path, filename);
	return &file_path[0];
}

void inicialice_var(char *var)
{
	int var_size = sizeof(var);
	for (int i = 0; i < var_size; i++) {
		var[i] = '\0';
	}
}

int copy_file(char *source, char *dest)
{
	int ret = 0;
	struct stat st;
	int fd;
	if (stat(source, &st) < 0) {
		ret = errno;
	}
	else {
		char *source_content = (char *)malloc(st.st_size);
		if ((fd = open(source, O_RDONLY)) >= 0) {
			read(fd, source_content, st.st_size);
			close(fd);
			if ((fd = open(dest, O_WRONLY)) >= 0) {
				write(fd, source_content, st.st_size);
				close(fd);
			}
			else {
				ret = errno;
			}
		}
		else {
			ret = errno;
		}
		free(source_content);
	}
	return ret;
}

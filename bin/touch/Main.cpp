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

#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

void make_path(const char *user_path, char *complete_path, int complete_path_size)
{
	if (user_path[0] != '/') {
		getcwd(complete_path, complete_path_size);
		if (complete_path[1] != '\0') strcat(complete_path, "/");
		strcat(complete_path, user_path);
	}
	else {
		strcpy(complete_path, user_path);
	}
}

void get_parent(const char *path, char *dest)
{
	int i;
	strcpy(dest, path);
	for (i = strlen(dest); dest[i] != '/'; i--) {
		dest[i] = '\0';
	}
	if (i > 1) dest[i] = '\0';
}

int checkDir(const char *path)
{
	int ret = 0;
	struct stat st;
	DIR *dir1;
	if (stat(path, &st) < 0) ret = errno;
	else if (S_ISDIR(st.st_mode)) {
		(!(dir1 = opendir(path))) ? ret = errno : closedir(dir1);
	}
	else ret = ENOTDIR;
	return ret;
}

int create_file(char *prog, char *path)
{
	int ret = EXIT_SUCCESS;
	char file_path[256];
	char file_parent[256];
	/* check if 'path' is a real file path */
	make_path(path, file_path, 256);
	/* we get the file parent to check if exists */
	get_parent(file_path, file_parent);
	/* check if parent directory exists */
	if ((ret = checkDir(file_parent)) != 0) {
		printf("%s: error al abrir '%s': %s\n", prog, file_parent, strerror(ret));
	}
	else if ((ret = touch(file_path, S_IRUSR | S_IWUSR)) < 0) {
		printf("%s: error al abrir '%s': %s\n",
                prog, file_path, strerror(errno));
	}
	return ret;
}

int main(int argc, char **argv)
{
	int i, ret, result = EXIT_SUCCESS;
	if (argc < 2) {
		printf("uso: %s FILE1 FILE2 ...\n", argv[0]);
	}
	else {
		for (i = 1; i < argc; i++) {
			ret = create_file(argv[0], argv[i]);
			if (ret < result) result = ret;
		}
	}
	return result;
}

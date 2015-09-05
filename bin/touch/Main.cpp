/* AMAYA OS 2014 */
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

#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

int mkfile(char *prog, char *path)
{
	int ret = EXIT_SUCCESS;
	char final_path[128];
	/* if there isn't a path */
	if (path[0] != '/') {
		getcwd(final_path, sizeof(final_path));
		if ((strcmp(final_path, "/")) != 0) {
			strcat(final_path, "/");
		}
		strcat(final_path, path);
	}
	else {
		strcpy(final_path, path);
	}
	if ((touch(final_path, S_IRUSR | S_IWUSR)) < 0) {
		printf("%s: error al abrir '%s': %s\r\n",
                prog, path, strerror(errno));
		ret = EXIT_FAILURE;
	}
	return ret;
}

int main(int argc, char **argv)
{
	int i, ret, result = EXIT_SUCCESS;
	if (argc < 2) {
		printf("uso: %s FILE1 FILE2 ...\n", argv[0]);
		result = EXIT_SUCCESS;
	}
	for (i = 1; i < argc; i++) {
		ret = mkfile(argv[0], argv[i]);
		if (ret > result) {
			result = ret;
		}
	}
	return result;
}

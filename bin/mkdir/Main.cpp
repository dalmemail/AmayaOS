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

int mkfolder(char *prog, char *path)
{
	char *final_path;
	/* if there isn't a path */
	if (path[0] != '/') {
		final_path = new char [128];
		getcwd(final_path, sizeof(final_path));
		if ((strcmp(final_path, "/")) != 0) {
			strcat(final_path, "/");
		}
		strcat(final_path, path);
	}
	else {
		final_path = new char [strlen(path)];
		strcpy(final_path, path);
	}
	if ((mkdir(final_path, S_IRUSR | S_IWUSR)) < 0) {
		printf("%s: error al abrir '%s': %s\r\n",
                prog, path, strerror(errno));
		return EXIT_FAILURE;
	}
	delete final_path;
	return EXIT_SUCCESS;
}

int main(int argc, char **argv)
{
	int i, ret = EXIT_SUCCESS;
	if (argc < 2) {
		printf("uso: %s DIRECTORIO1 DIRECTORIO2 ...\n", argv[0]);
		return EXIT_SUCCESS;
	}
	for (i = 1; i < argc; i++) {
		ret = mkfolder(argv[0], argv[i]);
	}
	return ret;
}

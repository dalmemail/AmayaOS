/*
 * Copyright (C) 2009 Niek Linnenbank, 2012 Felipe Cabrera, 2016-2017 Daniel Martín
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
#include <dirent.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>
#include <TerminalCodes.h>

#define OPT_A 1

int listDir(char *dirName, unsigned char listOpt)
{
	DIR *d;
	struct dirent *dent;
	struct stat st;
	char tmp[256];

	/* Intentamos abrir el directorio. */
	if (!(d = opendir(dirName))) {
		printf("ls: error al abrir '%s': %s\n", dirName, strerror(errno));
		return EXIT_FAILURE;
	}
    
	/* Leemos el directorio. */
	while ((dent = readdir(d))) {
		if(dent->d_name[0]=='.' && !(listOpt & OPT_A))
			continue;
		/* Esta es la parte entretenida. A colorear! */
		switch (dent->d_type) {
			case DT_DIR:
				printf("%s", BLUE);
			break;

			case DT_BLK:
			case DT_CHR:
				printf("%s", YELLOW);
	                break;

			case DT_REG:
			default:
				/* Construimos la ruta completa. */
				snprintf(tmp, sizeof(tmp), "%s/%s", dirName, dent->d_name);

				/* Es un ejecutable? */
				if (stat(tmp, &st) != -1 && st.st_mode & 0100) 
					printf("%s", GREEN);
				else
					printf("%s", WHITE);
		}
		printf("%s ", dent->d_name);
	}

	printf("%s\n\n", WHITE);

	/* Cerramos. */
	closedir(d);

	return EXIT_SUCCESS;
}

unsigned int IsDir(char *path)
{
	unsigned int ret = 0;
	struct stat st;
	if ((stat(path, &st)) >= 0) {
		if (S_ISDIR(st.st_mode)) ret = 1;
	}
	return ret;
}

int main(int argc, char **argv)
{
	unsigned int FilesNum = 0;
	unsigned int BadArg = 0;
	unsigned char listOpt = 0;
	char currentPath[256];
	for (unsigned int i = 1; i < (unsigned)argc; i++) {
		if (!strcmp(argv[i], "-a") || !strcmp(argv[i], "--all")) listOpt |= OPT_A;
		else if (argv[i][0] != '-') FilesNum++;
		else {
			BadArg = 1;
			printf("%s: Invalid option '%s'\n", argv[0], argv[i]);
		}
	}
	if (BadArg) return EXIT_FAILURE;
	for (unsigned int i = 1; i < (unsigned)argc; i++) {
		if (argv[i][0] != '-') {
			if (FilesNum > 1) printf("%s:\n", argv[i]);
			if (IsDir(argv[i])) listDir(argv[i], listOpt);
			else printf("%s\n", argv[i]);
		}
	}
	if (!FilesNum) {
		getcwd(currentPath, sizeof(currentPath));
		listDir(currentPath, listOpt);
	}
	return EXIT_SUCCESS;
}

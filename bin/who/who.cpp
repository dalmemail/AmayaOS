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

#include "who.h"
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <fcntl.h>
#include <sys/stat.h>

void who(char *host)
{
	char *path[5] = {"tty0", "tty1", "tty2", "tty3", "tty4"};
	char path_actual[64];
	struct stat st;
	for (int i = 0; i < 5; i++) {
		strcpy(path_actual, "/dev/");
		strcat(path_actual, path[i]);
		if ((stat(path_actual, &st)) == 0) {
			printf("%s\t%s\n", host, path[i]);
		}
	}
}

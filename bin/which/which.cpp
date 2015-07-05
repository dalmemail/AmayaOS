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

#include "which.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#include <sys/stat.h>

unsigned int which(char *command)
{
	char *path[3] = {"/bin/", "/sbin/", "/usr/bin/"};
	char path_actual[64];
	struct stat st;
	for (int i = 0; i < 3; i++) {
		strcpy(path_actual, path[i]);
		strcat(path_actual, command);
		if ((stat(path_actual, &st)) == 0) {
			printf("%s/%s\n", path_actual, command);
			return 0;
		}
	}
	return 0;
}

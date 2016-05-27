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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include "wama.h"
#include "reader.h"
 
int read_wama_file(char *path)
{
	int ret = 0;
	if (path[0] != '/') {
		char dev_path[128] = "/dev/";
		strcat(dev_path, path);
		strcpy(path, dev_path);
	}
	if ((open(path, O_RDONLY)) < 0) {
		printf("Error abriendo '%s':%s.\n", path, strerror(errno));
		ret = -1;
	}
	else {
		ret = line_navigator(path, READ_MODE);
	}
	return ret;
}

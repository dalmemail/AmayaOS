/*
 * Copyright (C) 2015 Dan Rulos [amaya@amayaos.com]
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
#include "find.h"

int main(int argc, char **argv)
{
	int ret;
	if (argc < 4) {
		printf("%s: path -name file\n", argv[0]);
		ret = EXIT_FAILURE;
	}
	else {
		if ((strcmp(argv[2], "-name")) == 0) {
			ret = find(argv[1], argv[3]);
		}
		else {
			printf("%s: command not found\n", argv[2]);
			ret = EXIT_FAILURE;
		}
	}
	return ret;
}

/*
 * Copyright (C) 2015 Dan Rulos.
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
#include "calculator.h"

#define VERSION "0.7"

/* main function */
int main(int argc, char **argv)
{
	int ret = EXIT_SUCCESS;
	if (argc == 2 && (strcmp(argv[1], "--temp")) == 0) {
		ret = temp();
	}
	else if (argc == 2 && (strcmp(argv[1], "--version")) == 0) {
		printf("Version: %s\n", VERSION);
	}
	else if (argc < 4) {
		printf("uso: %s num1 operator1 num2 operator2 num3 ...\n", argv[0]);
		ret = EXIT_FAILURE;
	}
	else if (argc >= 4) {
		int result = atoi(argv[1]);
		int i = 2;
		do {
			result = calculator(result, argv[i][0], atoi(argv[i+1]));
		} while((i += 2) < argc);
	}
	return ret;
}

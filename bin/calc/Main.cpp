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

#define VERSION "0.6"

/* main function */
int main(int argc, char **argv)
{
	int ret = EXIT_SUCCESS;
	if (argc == 2 && (strcmp(argv[1], "--temp")) == 0) {
		ret = temp();
		return ret;
	}
	if (argc != 4) {
		printf("uso: %s num1 operador num2\n", argv[0]);
		return EXIT_FAILURE;
	}
	ret = calculator(atoi(argv[1]), argv[2][0], atoi(argv[3]));
	return ret;
}

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

#include "stdlib.h"
#include <string.h>

double atof(char *input)
{
	double n = 0;
	double div = 10;
	unsigned int i;
	for (i = 0; i < strlen(input); i++) {
		if (input[i] >= '0' && input[i] <= '9') {
			n *= 10;
			n += (input[i] - '0');
		}
		if (input[i] == '.') {
			i++;
			while (i < strlen(input)) {
				n += ((input[i++] - '0') / div);
				div *= 10;
			}
		}
	}
	if (input[0] == '-') {
		n *= -1;
	}
	return n;
}

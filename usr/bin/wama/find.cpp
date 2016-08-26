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

#include "wama.h"
#include <string.h>

struct cursor findString(char *string, char **lines, int n_lines, struct cursor start_point)
{
	struct cursor final_point;
	int line = start_point.ln;
	int col = start_point.col;
	int stringSize = strlen(string);
	int exists = 0;
	while (line < n_lines && !exists) {
		int lineSize = strlen(lines[line]);
		int x = 0;
		while (col < lineSize && !exists) {
			if (lines[line][col] == string[x]) {
				x++;
				if (x == stringSize) {
					exists = 1;
					final_point.ln = line;
					final_point.col = col+1;
				}
			}
			else {
				x = 0;
			}
			col++;
		}
		col = 0;
		line++;
	}
	if (!exists) {
		final_point.ln = start_point.ln;
		final_point.col = start_point.col;
	}
	return final_point;
}

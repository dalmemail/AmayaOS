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

#include "wc.h"

#define _FALSE 0
#define _TRUE 1

struct wc wordcount(char *file_content)
{
	struct wc file_wc;
	file_wc.words = 0;
	file_wc.lines = 0;
	int new_word = _TRUE;
	for (file_wc.chars = 0; file_content[file_wc.chars] != '\0'; file_wc.chars++) {
		if (file_content[file_wc.chars] == '\n') {
			file_wc.lines++;
			new_word = _TRUE;
		}
		else if (file_content[file_wc.chars] == '\t'
			|| file_content[file_wc.chars] == ' ') {
			new_word = _TRUE;
		}
		else if (new_word) {
			new_word = _FALSE;
			file_wc.words++;
		}
	}
	return file_wc;
}

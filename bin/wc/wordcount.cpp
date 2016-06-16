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

#include "wordcount.h"

unsigned int wordcount(char *ch)
{
	int state = OUT;
	unsigned int nw = 0;
	unsigned int ch_len = strlen(ch);
	for (unsigned int i = 0; i < ch_len; i++) {
		if (ch[i] == '\n' || ch[i] == ' ' || ch[i] == '\t') {
			state = OUT;
		}
		else if (state == OUT) {
			state = IN;
			nw++;
		}
	}
	return nw;
}

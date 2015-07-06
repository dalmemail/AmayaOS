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

#include <stdlib.h>
#include <files.h>
#include "minesweeper.h"

/* getchar() modificado para leer numeros */
int getnum()
{
	static char ch[1024];
	read(0, ch, 1);
	int n = atoi(ch);
    
	return n;
}

int getTime()
{
	file *f = new file();
	f->setpath("/dev/time");
	f->f_open(O_RDONLY);
	char *ch = f->readAll();
	f->f_close();
	return atoi(ch);
}

unsigned int timeplaying(int starttime)
{
	return (getTime() - starttime);
}

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

#include <files.h>
#include <stdlib.h>
#include "gun.h"

int ntime()
{
	file *f = new file();
	f->setpath("/dev/time");
	f->f_open(O_RDONLY);
	char *ch = f->readAll();
	f->f_close();
	return atoi(ch);
}

int aleatorio()
{
	int n = ntime();
	int k = n % 10;
	n = n / 10;
	n = n % 10;
	return n * 10 + k;
}

int num1(int seeder)
{
	int n = aleatorio();
	switch (seeder) {
		case 2:
			n = n / 10;
			return n % 10;
			break;
		case 1:
		default:
			return n % 10;
			break;
	}	
}

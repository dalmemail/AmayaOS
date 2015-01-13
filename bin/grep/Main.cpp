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
#include <files.h>

int main(int argc, char **argv)
{
    if (argc < 3) {
	printf("Uso: %s archivo cadena\r\n", argv[0]);
	return -1;
    }
    file *f = new file();
    f->setpath(argv[1]);
    f->f_open(O_RDONLY);
    char *ch = f->readAll();
    f->f_close();
    int i;
    char v[512];
    int z=0;
    int x=0;
    for(i=0; i <= strlen(ch); i++) {
	if (argv[2][x]==ch[i]) {
	  if (argv[2][x-1]==ch[i-1]) {
	    v[z]=ch[i];
	    z++;
	    x++;
	  }
	  if (x == 0) {
	    v[z]=ch[i];
	    z++;
	    x++;
	  }
	}
    }
    //printf("%s\r\n", v);
    if ((strcmp(v, argv[2]))==0) {
	printf("%s\r\n", v);
	return 0;
    }
    return 0;
}

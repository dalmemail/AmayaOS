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
	printf("Uso: %s cadena archivo\r\n", argv[0]);
	return -1;
    }
    // Leemos el fichero (argv[2])
    file *f = new file();
    f->setpath(argv[2]);
    f->f_open(O_RDONLY);
    char *ch = f->readAll();
    f->f_close();
    int i;
    char v[512];
    /* El punto de la palabra en el vector v[] */
    int z=0;
    /* El punto de la palabra en el vector argv[1][] */
    int x=0;
    /* El punto del vector ch[] en el que comienza la frase
     * donde está la palabra que hemos buscado. */
    int point=0;
    for(i=0; i <= strlen(ch); i++) {
	if (argv[1][x]==ch[i]) {
	  if (argv[1][x-1]==ch[i-1]) {
	    v[z]=ch[i];
	    z++;
	    x++;
	  }
	  if (x == 0) {
	    v[z]=ch[i];
	    z++;
	    x++;
	  }
	  if (x == strlen(argv[1])) {
	    point=i;
	    x++;
	  }
	}
    }
    if (strcmp(argv[1], v)==0 || strlen(argv[1]) < strlen(v)) {
	for (point=point; ch[point-1] != '\n'&& point > -1; point--) {
	}
        for (point=point; ch[point] != '\n' && point <= i; point++) {
	  printf("%c", ch[point]);
	}
    	printf("\r\n");
    }
    else {
	printf("Cadena no encontrada\n");
    }
    return 0;
}

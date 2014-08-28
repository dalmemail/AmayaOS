/*
 * Copyright (C) 2014 Dan Rulos.
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
#include <string.h>
#include <files.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    if (argc < 2) {
      printf("Uso: wc archivo\r\n");
      return EXIT_FAILURE;
    }
    file *f = new file();
    f->setpath(argv[1]);
    f->f_open(O_RDONLY);
    char *ch = f->readAll();
    f->f_close();
    printf("%d", strlen(ch));
    printf("\r\n");
    return EXIT_SUCCESS;
}

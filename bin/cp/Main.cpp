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
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <files.h>

int main(int argc, char **argv)
{
    if (argc < 3) {
      printf("Uso: cp origen destino\r\n");
      return EXIT_FAILURE;
    }
    int fd;
    char *newline="\r\n";
    file *f = new file();
    f->setpath(argv[1]);
    f->f_open(O_RDONLY);
    char *ch = f->readAll();
    f->f_close();
    if ((fd = open(argv[2], O_WRONLY)) < 0) {
        printf("Error al abrir '%s': %s\r\n",
                argv[2], strerror(errno));
        return errno;
    }
    write(fd, ch, strlen(ch));
    write(fd, newline, 2);
}

/*
 * Copyright (C) 2014 Daniel Martin
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
#include <unistd.h>
#include <dirent.h>

int main(int argc, char **argv)
{
    if (argc < 2) {
      printf("Uso: %s software\r\n", argv[0]);
      return -1;
    }
    DIR *d;
    char path[255]="/bin/";
    strcat(path, argv[1]);
    if (!(d = opendir(path))) {
    }
    else {
      printf("%s", path);
      printf("\r\n");
    }
    char path2[255]="/sbin/";
    strcat(path2, argv[1]);
    if (!(d = opendir(path2))) {
    }
    else {
      printf("%s", path2);
      printf("\r\n");
    }
    char path3[255]="/usr/bin/";
    strcat(path3, argv[1]);
    if (!(d = opendir(path3))) {
    }
    else {
      printf("%s", path3);
      printf("\r\n");
    }
    return 0;
}

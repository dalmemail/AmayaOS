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
#include <dirent.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    char roc;
    DIR *dir;
    struct dirent *dent;
    struct stat st;
    char path[255], tmp[255];
    /* Obtenemos los argumentos, en caso de existir */
    if (argc < 3) {
      printf("Uso: find ruta nombre\r\n");
      return EXIT_FAILURE;
    }
    /* Intentamos abrir el directorio. */
    if (argc == 3) {
      if (!(dir = opendir(argv[1]))) {
          printf("%s: error al abrir '%s': %s\r\n",
                  argv[0], argv[1], strerror(errno));
          return EXIT_FAILURE;
      }
      /* Leemos el directorio. */
      while ((dent = readdir(dir))) {
          if(dent->d_name[0]=='.')
              continue;
            if (!strncmp(dent->d_name, argv[2], strlen(argv[2])) ||
                !strncmp(dent->d_name, argv[2], strlen(argv[2]))) {
                printf(argv[1]);
                printf(argv[2]);
            }
      }
    }
}

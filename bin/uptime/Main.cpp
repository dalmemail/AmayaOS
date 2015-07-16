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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "uptime.h"
#include "uptime_server.h"
#include "uptime_path.h"

int main(int argc, char **argv)
{
     if (argc == 2) {
	if (strcmp(argv[1], "--version") == 0 || strcmp(argv[1], "-v") == 0) {
	  printf("%s (AmayaCoreutils) 0.4\n", argv[0]);
	  printf("Copyright (C) 2015 AmayaOS Team.\n");
	  printf("License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>.\n");
	  printf("This is free software: you are free to change and redistribute it.\n");
	  printf("There is NO WARRANTY, to the extent permitted by law.\n\n");
	  printf("Escrito por Dan Rulos.\n");
	  return 0;
	}
	if (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0) {
	  printf("Usage: %s \n\n", argv[0]);
	  printf("Imprime el tiempo que lleva encendido el ordenador.\n");
	  printf("-v --version imprime la version de AmayaCoreutils.\n");
	  return 0;
	}
     }
    /* Averiguamos si es la primera vez que se ejecuta o no */
    if ((open(UPTIME_, O_RDONLY)) < 0) {
	/* Ejecutamos el server de uptime */
	uptime_server();
	return 0;
    }
    else {
	uptime();
	return 0;
    }
    return 0;
}

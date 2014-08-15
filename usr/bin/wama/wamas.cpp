/* Wa+ junglaCODE.org Villagran-Cortazar Guanajuato  */
/* @utores: Fernando{fercho} Juan Luis {monolinux} 
  email: developer@junglacode.org  web: www.junglacode.org*/
/* Copyright (C) 2014 Team Espartano (AmayaOS) */
/*
# Copyright (C) 2014 Team Espartano (AmayaOS).
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/> */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "reader.cpp"
#include "written.cpp"
#include <amaya.h>

int main(int argc, char *argv[])
{
    char opcion='S';
    if (argc > 1) {
      if (strcmp(argv[1], "-h") == 0||strcmp(argv[1], "--help") == 0) {
          printf("WAMA corriendo sobre AmayaOS\r\n");
          printf("Como usar WAMA: \r\n");
          printf("wama archivoaleer.txt | Lee un archivo\r\n");
          printf("wama --help | Muestra la ayuda general\r\n");
          printf("wama --version / -v | Muestra la version de wama\r\n");
          printf("\r\n");
          return EXIT_SUCCESS;
      }
      if (strcmp(argv[1], "-v") == 0||strcmp(argv[1], "--version") == 0) {
          printf("WA+ 0.2 corriendo sobre AmayaOS 0.06\r\n");
          return EXIT_SUCCESS;
      }
      if (argc == 2) {
        reader(argc, argv);
      }
      if (argc > 2) {
        printf("Demasiados argumentos\r\n");
      }
    }
    if (argc == 1) {
      printf("WAMA 0.2 | JunglaCode.org\r\n");
      printf("Copyright 2014 Team Espartano\r\n");
      printf("\r\n");
      printf("[N]uevo archivo\r\n");
      printf("[A]brir archivo\r\n");
      printf("[C]errar\r\n");
      do {
        printf("Escoja una opcion:\r\n");
        opcion = getchar();
      } while (opcion != 'N'&& opcion != 'n'&& opcion != 'A'&& opcion != 'a'&& opcion != 'C'&& opcion != 'c');
      if (opcion == 'C'|| opcion == 'c') {
        return EXIT_SUCCESS;
      }
    }
}

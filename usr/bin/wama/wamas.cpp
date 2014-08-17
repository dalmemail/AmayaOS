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
#include <TerminalCodes.h>
#include <sys/stat.h>

int wama_a()
{
    return EXIT_SUCCESS;
}

int wama_n()
{
    char ruta[128];
    printf("################################################################################\r\n");
    printf("# WA+ 0.2                                                                      #\r\n");
    printf("################################################################################\r\n");
    printf("#                                                                              #\r\n");
    printf("#                                                                              #\r\n");
    printf("#                                                                              #\r\n");
    printf("#                                                                              #\r\n");
    printf("#                                                                              #\r\n");
    printf("#                                                                              #\r\n");
    printf("#                                                                              #\r\n");
    printf("#                                                                              #\r\n");
    printf("#                                                                              #\r\n");
    printf("#                                                                              #\r\n");
    printf("#                                                                              #\r\n");
    printf("#                                                                              #\r\n");
    printf("#                                                                              #\r\n");
    printf("#                                                                              #\r\n");
    printf("#                                                                              #\r\n");
    printf("#                                                                              #\r\n");
    printf("#                                                                              #\r\n");
    printf("#                                                                              #\r\n");
    printf("#                                                                              #\r\n");
    printf("################################################################################\r\n");
    do {
      printf("Nombre del nuevo archivo (ruta completa) : \r\n");
      gets(ruta);
    } while (ruta[0] != '/');
    touch(ruta, S_IWUSR | S_IRUSR);
}

int wama()
{
    char opcion;
    printf("################################################################################\r\n");
    printf("# WA+ 0.2                                                                      #\r\n");
    printf("################################################################################\r\n");
    printf("# [-M] Menu | [-G] Guardar | [-S] Salir (sin guardar)                          #\r\n");
    printf("################################################################################\r\n");
    printf("# Bienvenido a WA+ 0.2 un componente de AmayaOS/FreeNOS                        #\r\n");
    printf("# Proyecto por Team Espartano & AmayaOS Team                                   #\r\n");
    printf("################################################################################\r\n");
    printf("# Menu                                                                         #\r\n");
    printf("# [A] Abrir un archivo existente                                               #\r\n");
    printf("# [N] Nuevo archivo                                                            #\r\n");
    printf("# [S] Salir de WA+                                                             #\r\n");
    printf("################################################################################\r\n");
    printf("# WA+ es un producto licenciado bajo la GNU GPL v3 que respeta su libertad     #\r\n");
    printf("# WA+ es un editor de texto inspirado en GNU Emacs escrito por Richard Stallman#\r\n");
    printf("# en 1975. Esta escrito en C++.                                                #\r\n");
    printf("# Sitio web oficial de WA+ ");
    printf(GREEN "http://gitlab.com/team-espartano/wama");
    printf(WHITE "              #\r\n");
    printf("# Sitio web team espartano ");
    printf(BLUE "http://junglacode.org");
    printf(WHITE "                               #\r\n");
    printf("#                                                                              #\r\n");
    printf("#                                                                              #\r\n");
    printf("#                                                                              #\r\n");
    printf("#                                                                              #\r\n");
    printf("################################################################################\r\n");
    do {
      printf("Introduce una opcion : \r\n");
      opcion = getchar();
    } while (opcion != 'A'&& opcion != 'a'&& opcion != 'N'&& opcion != 'n'&& opcion != 'S'&& opcion != 's');
    if (opcion == 'A'|| opcion == 'a') {
      wama_a();
    }
    if (opcion == 'N'|| opcion == 'n') {
      wama_n();
    }
    if (opcion == 'S'|| opcion == 's') {
      return EXIT_SUCCESS;
    }
}

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
        wama();
      }
    }
    if (argc == 1) {
      wama();
    }
}

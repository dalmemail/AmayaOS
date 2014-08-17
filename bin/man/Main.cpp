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
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main(int argc, char **argv)
{
    if (argc < 2) {
      printf("Uso: man comando\r\n");
      return EXIT_FAILURE;
    }
    if (strcmp(argv[1], "ps") == 0) {
      printf("NOMBRE\r\n");
      printf("ps - muestra el estado de los procesos\r\n");
      printf("SINTAXIS\r\n");
      printf("ps [Opciones]\r\n");
      return EXIT_SUCCESS;
    }
    if (strcmp(argv[1], "memstat") == 0) {
      printf("NOMBRE\r\n");
      printf("memstat - muestra el estado de la memoria ram\r\n");
      printf("SINTAXIS\r\n");
      printf("memstat\r\n");
      return EXIT_SUCCESS;
    }
    if (strcmp(argv[1], "pwd") == 0) {
      printf("NOMBRE\r\n");
      printf("pwd - muestra el directorio actual\r\n");
      printf("SINTAXIS\r\n");
      printf("pwd\r\n");
      return EXIT_SUCCESS;
    }
    if (strcmp(argv[1], "mkdir") == 0) {
      printf("NOMBRE\r\n");
      printf("mkdir - crea una nueva carpeta\r\n");
      printf("SINTAXIS\r\n");
      printf("mkdir directorio\r\n");
      return EXIT_SUCCESS;
    }
    if (strcmp(argv[1], "ls") == 0) {
      printf("NOMBRE\r\n");
      printf("ls - muestra los archivos de un directorio\r\n");
      printf("SINTAXIS\r\n");
      printf("ls directorio\r\n");
      return EXIT_SUCCESS;
    }
    if (strcmp(argv[1], "hostname") == 0) {
      printf("NOMBRE\r\n");
      printf("hostname - muestra el usuario actual\r\n");
      printf("SINTAXIS\r\n");
      printf("hostname\r\n");
      return EXIT_SUCCESS;
    }
    if (strcmp(argv[1], "tedit") == 0) {
      printf("NOMBRE\r\n");
      printf("tedit - simple editor de texto\r\n");
      printf("SINTAXIS\r\n");
      printf("tedit\r\n");
      return EXIT_SUCCESS;
    }
    if (strcmp(argv[1], "touch") == 0) {
      printf("NOMBRE\r\n");
      printf("touch - crea un nuevo archivo simple\r\n");
      printf("SINTAXIS\r\n");
      printf("touch directorio\r\n");
      return EXIT_SUCCESS;
    }
    if (strcmp(argv[1], "mount") == 0) {
      printf("NOMBRE\r\n");
      printf("mount - muestra los sistemas de archivos montados\r\n");
      printf("SINTAXIS\r\n");
      printf("mount\r\n");
      return EXIT_SUCCESS;
    }
    if (strcmp(argv[1], "cp") == 0) {
      printf("NOMBRE\r\n");
      printf("cp - copia un archivo\r\n");
      printf("SINTAXIS\r\n");
      printf("cp archivo ruta\r\n");
      return EXIT_SUCCESS;
    }
    if (strcmp(argv[1], "uname") == 0) {
      printf("NOMBRE\r\n");
      printf("uname - muestra el nombre del kernel e información sobre el mismo\r\n");
      printf("SINTAXIS\r\n");
      printf("uname [Opciones]\r\n");
      return EXIT_SUCCESS;
    }
    if (strcmp(argv[1], "mknod") == 0) {
      printf("NOMBRE\r\n");
      printf("mknod - crea un archivo de un dispositivo\r\n");
      printf("SINTAXIS\r\n");
      printf("mknod ruta tipo mayor menor\r\n");
      return EXIT_SUCCESS;
    }
    if (strcmp(argv[1], "sh") == 0) {
      printf("NOMBRE\r\n");
      printf("sh - ejecuta scripts de terminal\r\n");
      printf("SINTAXIS\r\n");
      printf("sh script\r\n");
      return EXIT_SUCCESS;
    }
    if (strcmp(argv[1], "calc") == 0) {
      printf("NOMBRE\r\n");
      printf("calc - Calculadora simple\r\n");
      printf("SINTAXIS\r\n");
      printf("calc\r\n");
      return EXIT_SUCCESS;
    }
    if (strcmp(argv[1], "sudoku") == 0) {
      printf("NOMBRE\r\n");
      printf("sudoku - sencillo juego de sudoku\r\n");
      printf("SINTAXIS\r\n");
      printf("sudoku\r\n");
      return EXIT_SUCCESS;
    }
    if (strcmp(argv[1], "sleep") == 0) {
      printf("NOMBRE\r\n");
      printf("sleep - duerme el sistema operativo\r\n");
      printf("SINTAXIS\r\n");
      printf("sleep segundos\r\n");
      return EXIT_SUCCESS;
    }
    if (strcmp(argv[1], "stat") == 0) {
      printf("NOMBRE\r\n");
      printf("stat - Muestra toda la información de un archivo\r\n");
      printf("SINTAXIS\r\n");
      printf("stat archivo\r\n");
      return EXIT_SUCCESS;
    }
    if (strcmp(argv[1], "echo") == 0) {
      printf("NOMBRE\r\n");
      printf("echo - muestra en la pantalla un mensaje\r\n");
      printf("SINTAXIS\r\n");
      printf("echo mensaje\r\n");
      return EXIT_SUCCESS;
    }
    if (strcmp(argv[1], "cat") == 0) {
      printf("NOMBRE\r\n");
      printf("cat - muestra en la pantalla el contenido de un archivo\r\n");
      printf("SINTAXIS\r\n");
      printf("cat archivo\r\n");
      return EXIT_SUCCESS;
    }
    if (argv[1]) {
      printf("Comando desconocido\r\n");
      return EXIT_FAILURE;
    }
}

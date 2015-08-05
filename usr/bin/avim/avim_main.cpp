/*
 * Copyright (C) 2015 Alvaro Stagg. [alvarostagg@openmailbox.org]
 *		 2015 Dan Rulos. [amaya@amayaos.com]
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
#include <sys/stat.h>
#include <unistd.h>
#include "avim_command.h"
#include "avim_colores.h"
#include "avim_version.h"

#define FILE_LINE 0
#define AVIM_COMMAND 1

#define _FALSE 0
#define _TRUE 1

void cls();
void editor(int n_linea);
int lineCount(char c[2048], int nb);

int fp;

char* n_archivo;

int show_line_number = _TRUE;

int main(int argc, char* argv[])
{
  if(argc < 2)
  {
    printf(VERDE "Uso: " NORMAL "avim archivo.ext\n");
    return -1;
  }
  else if(argc > 3)
  {
    printf(VERDE "Uso: " NORMAL "avim archivo.ext\n");
    return -1;
  }
  else
  {
    n_archivo = argv[1];

    if((fp = open(argv[1], O_WRONLY | O_TRUNC)) < 0)
    {
      /* el archivo no existe, tal vez sea un comando*/
      int n = avim_command_execute(argv[1]);

      /* quiere que creemos un archivo */
      if(n == 3 && argc == 3)
      {
        n_archivo = argv[2];

	touch(argv[2], S_IWUSR | S_IRUSR);
        if((fp = open(argv[2], O_WRONLY)) < 0)
        {
          printf(ROJO "Error: " NORMAL "el archivo no pudo ser creado.\n");
          return -1;
        }
        else
        {
          /* comienza la edición */
          cls();
          editor(1);

          /* salida exitosa */
          return 0;
        }
      }
      else if(n == 4 && argc == 3)
      {
        n_archivo = argv[2];

	FILE *file1;
	if ((file1 = fopen(argv[2], "r")) == NULL) {
		printf("El archivo de origen '%s' no existe\n", argv[2]);
		return -1;
	}
	char contenido[2048];
	int n_bytes = fread(contenido, 1, sizeof(contenido), file1);
	fclose(file1);
        if((fp = open(argv[2], O_WRONLY)) < 0)
        {
          printf(ROJO "Error: " NORMAL "el archivo %s no pudo ser abierto.\n", argv[0]);
          return -1;
        }
        else
        {
          /* comienza la ediciÃ³n */
          cls();
	  write(fp, contenido, n_bytes);
          editor(lineCount(contenido, n_bytes));

          /* salida exitosa */
          return 0;
        }
      }
    }
    else
    {
      /* comienza la ediciÃ³n */
      cls();
      editor(1);
    }
  }
  /* salida exitosa */
  return 0;
}

void cls()
{
  char str[] = {0x1b, 0x5b, 0x48, 0x1b, 0x5b, 0x4a, '\0'};
  printf("%s", str);
}

void editor(int n_linea)
{
  char linea[128];
  int last_line = FILE_LINE;

  printf(VERDE "AVIM %s" NORMAL " | Editando archivo: " VERDE "%s " NORMAL "|\n\n", VERSION, n_archivo);
  do
  {
    if (show_line_number) {
	printf("%d ", n_linea);
    }
    gets_s(linea, 128);

    if(linea[0] == ':')
    {
	last_line = AVIM_COMMAND;
	if (linea[1] == 'x') {
		close(fp);
	}
	if (linea[1] == 'e') {
		close(fp);
		printf("Nombre del archivo: ");
		gets_s(linea, 128);
		cls();
        	if((fp = open(linea, O_WRONLY)) < 0)
        	{
          		printf(ROJO "Error: " NORMAL "el archivo %s no pudo ser abierto.\n", linea);
        	}
		else {
			n_archivo = linea;
			editor(1);
		}
	}
	if (linea[1] == 'c' && linea[2] == 'f') {
		close(fp);
		printf("Archivo a crear: ");
		gets_s(linea, 128);
		touch(linea, S_IWUSR | S_IRUSR);
        	if((fp = open(linea, O_WRONLY)) < 0)
        	{
          		printf(ROJO "Error: " NORMAL "el archivo %s no pudo ser abierto.\n", linea);
        	}
		n_archivo = linea;
		cls();
		editor(1);
	}
	if (linea[1] == 'o' && linea[2] == 'a' && linea[3] == 'e') {
		close(fp);
		printf("Archivo a abrir: ");
		gets_s(linea, 128);
        	if((fp = open(linea, O_WRONLY)) < 0)
        	{
          		printf(ROJO "Error: " NORMAL "el archivo %s no pudo ser abierto.\n", linea);
        	}
		FILE *file1;
		file1 = fopen(linea, "r");
		char contenido[2048];
		int n_bytes = fread(contenido, 1, sizeof(contenido), file1);
		fclose(file1);
		write(fp, contenido, n_bytes);
		n_archivo = linea;
		cls();
		editor(lineCount(contenido, n_bytes));
	}
	if (linea[1] == 's' && linea[2] == 'e' && linea[3] == 't' && linea[4] == ' ' && linea[5] == 'n' && linea[6] == 'u' 		    && linea[7] == 'm' && linea[8] == 'b' && linea[9] == 'e' && linea[10] == 'r') {
		if (show_line_number) {
			show_line_number = _FALSE;
		}
		else {
			show_line_number = _TRUE;
		}
		cls();
		close(fp);
        	if((fp = open(n_archivo, O_WRONLY)) < 0)
        	{
          		printf(ROJO "Error: " NORMAL "el archivo %s no pudo ser abierto.\n", linea);
        	}
		FILE *file1;
		file1 = fopen(n_archivo, "r");
		char contenido[2048];
		int n_bytes = fread(contenido, 1, sizeof(contenido), file1);
		fclose(file1);
		write(fp, contenido, n_bytes);
		editor(n_linea);
	}
    }
    else {
	last_line = FILE_LINE;
	n_linea++;

	write(fp, linea, strlen(linea));
	write(fp, "\n", 1);
    }
  } while (last_line != AVIM_COMMAND);

  cls();
}

int lineCount(char c[2048], int nb) {
	int n_lines = 1;
	for (int i = 0; i < nb; i++) {
		if (c[i] == '\n') {
			n_lines++;
		}
	}
	return n_lines;
}

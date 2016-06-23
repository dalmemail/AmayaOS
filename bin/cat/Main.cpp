/*
 * Copyright (C) 2009 Niek Linnenbank, 2016 Dan Rulos, 2016 Alvaro Stagg [alvarostagg@openmailbox.org]
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
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#define VERSION "v0.6.1"

static int hflag, vflag, ret = 0;
static int flags[2];

static void usage(void);
static void version(void);
static void cat(char **filePaths, int n_files, int flags[2]);
int lineCounter(char *c);
static void read_file(const char *fileName, int flags[2]);
int getNumberOfFiles(int argc, char **argv);

int get_file_size(const char *fileName);

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("Uso: %s [OPCION]... [FICHERO]...\n", argv[0]);
        return 1;
    }

    for (int i = 0; i < 2; i++)
    	flags[i] = 0;

	int n_files = getNumberOfFiles(argc, argv);
	char **filePaths = new char *[n_files];

    for (int i = 1, act_file = 0; i < argc; i++)
    {
    	if (strcmp(argv[i], "--help") == 0)
    	{
    		hflag = 1;
    		usage();
		break;
    	}
    	else if ((strcmp(argv[i], "--version") == 0))
    	{
    		vflag = 1;
    		version();
    		break;
    	}
    	else if ((strcmp(argv[i], "-n") == 0) || (strcmp(argv[i], "--number") == 0)) {
		flags[0] = 1;
	}
	else if ((strcmp(argv[i], "-E") == 0) || (strcmp(argv[i], "--show-ends") == 0) || (strcmp(argv[i], "-e") == 0)) {
		flags[1] = 1;
	}
	else {
		filePaths[act_file] = &argv[i][0];
		act_file++;
	}
    }

	if (!hflag && !vflag) {
		cat(filePaths, n_files, flags);
	}

	delete filePaths;
    return ret;
}

static void usage(void)
{
	printf("Modo de empleo: cat [OPCION]... [FICHERO]...\n\n");

	printf("  -e                       Lo mismo que -E.\n");
	printf("  -E, --show-ends          Muestra un $ al final de cada linea.\n");
	printf("  -n, --number             Enumera cada linea.\n");
	printf("      --help               Muestra esta ayuda y finaliza.\n");
	printf("      --version            Informa de la version y finaliza.\n\n");

	printf("AmayaOS Coreutils %s (C) 2016 AmayaOS Team & Others\n", VERSION);
	printf("Licencia GNU GPL v3 <http://www.gnu.org/licenses/>.\n");
	printf("Reportar errores a traves de http://bugs.amayaos.com o amaya@amayaos.com\n");
}

static void version(void)
{
	printf("cat (AmayaOS CoreUtils) %s\n", VERSION);
	printf("Copyright (C) 2016 AmayaOS, Inc.\n");
	printf("Licencia GPLv3+: GPL de GNU versión 3 o posterior\n");
	printf("<http://gnu.org/licenses/gpl.html>.\n");
	printf("Esto es software libre: usted es libre de cambiarlo y redistribuirlo.\n");
	printf("No hay NINGUNA GARANTIA, hasta donde permite la ley.\n\n");
}

static void cat(char **filePaths, int n_files, int flags[2])
{
	for (int i = 0; i < n_files; i++)
	{
		read_file(filePaths[i], flags);
	}
}

int lineCounter(char *c)
{
	int n_lines = 0;
	for (int i = 0; c[i] != '\0'; i++) {
		if (c[i] == '\n') {
			n_lines++;
		}
	}
	return n_lines;
}

static void read_file(const char *fileName, int flags[2])
{

	int fd;
	if ((fd = open(fileName, O_RDONLY)) < 0)
	{
		printf("cat: %s: No existe el fichero o el directorio.\n", fileName);
		ret = 1;
	}
	else
	{
		int file_size = get_file_size(fileName);
		char *cnt = new char[file_size];
		read(fd, cnt, file_size);
		int n_lines = lineCounter(cnt);
		char **lines;
		lines = new char *[n_lines];
		lines[0] = &cnt[0];
		int data_len = strlen(cnt);
		if (data_len > 0) {
			for (int i = 1, x = 0; cnt[x] != '\0'; x++) {
				if (cnt[x] == '\n') {
					cnt[x] = '\0';
					if (i < n_lines) {
						lines[i] = &cnt[x+1];
					}
					i++;
				}
			}
			for (int act_line = 0; act_line < n_lines; act_line++) {
				if (flags[0]) {
					printf("%d ", (act_line+1));
				}
				printf("%s", lines[act_line]);
				if (flags[1]) {
					printf("$");
				}
				printf("\n");
			}
		}
		delete lines;
		delete cnt;
		close(fd);
	}
}

int get_file_size(const char *fileName)
{
	struct stat st;

	if (stat(fileName, &st) < 0)
		return -1;
	else
		return st.st_size;
}

int getNumberOfFiles(int argc, char **argv)
{
	int n_files = (argc-1);
	for (int i = 1; i < argc; i++) {
    		if ((strcmp(argv[i], "-n") == 0) || (strcmp(argv[i], "--number") == 0)) {
			n_files--;
		}
		else if ((strcmp(argv[i], "-E") == 0) || (strcmp(argv[i], "--show-ends") == 0) || (strcmp(argv[i], "-e") == 0)) {
			n_files--;
		}
	}
	return n_files;
}

/*
 * Copyright (C) 2009 Niek Linnenbank, 2014-2017 Daniel Martín, 2016-2017 Alvaro Stagg [alvarostagg@openmailbox.org]
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
#include <sys/stat.h>

#define VERSION "0.6.2"

static int hflag = 0, vflag = 0;
static int nflag = 0, eflag = 0, tflag = 0, bflag = 0;

static void usage(void);
static void version(void);

static int read_file(int, char*);
static size_t get_file_size(const char *);

int main(int argc, char* argv[])
{
    int ret = 0, i = 1;
    for (; i < argc; i++)
    {
        if (strcmp(argv[i], "--help") == 0)
        {
            hflag = 1;
            usage();
            break;
        }
        else if (strcmp(argv[i], "--version") == 0)
        {
            vflag = 1;
            version();
            break;
        }
        else if ((strcmp(argv[i], "-n") == 0) || (strcmp(argv[i], "--number") == 0))
            nflag = 1;
        else if ((strcmp(argv[i], "-E") == 0) || (strcmp(argv[i], "--show-ends") == 0) || (strcmp(argv[i], "-e") == 0))
            eflag = 1;
        else if ((strcmp(argv[i], "-t") == 0) || (strcmp(argv[i], "-T") == 0) || (strcmp(argv[i], "--show-tabs") == 0))
            tflag = 1;
        else if ((strcmp(argv[i], "-b") == 0) || (strcmp(argv[i], "--number-nonblank") == 0))
        {
            nflag = 0;
            bflag = 1;
        }
        else
        {
            if (argv[i][0] == '-')
            {
                if (argv[i][1] == '-')
                    printf("%s: unrecognized option '%s'\n", argv[0], argv[i]);
                else
                {
                    printf("%s: invalid option -- '", argv[0]);
                    for (unsigned int j = 0; j <= strlen(argv[i]); j++)
                    {
                        if (argv[i][j] == '-')
                            continue;
                        else
                            printf("%c", argv[i][j]);
                    }

                    printf("'\n");
                }

                ret = -1;
            }
        }
    }

    if (ret < 0)
    {
        printf("Pruebe '%s --help' para más información.\n", argv[0]);
        return ret;
    }

    if (hflag || vflag)
        return ret;

    for (i = 1; i < argc; i++)
    {
        if (argv[i][0] == '-')
            continue;
        else
        {
            ret = read_file(argc, argv[i]);
            if (ret < 0)
            {
                printf("%s: no se pudo abrir el archivo %s.\n", argv[0], argv[i]);
                break;
            }
        }
    }

    return ret;
}

static int read_file(int argc, char* fileName)
{
    FILE* file = fopen(fileName, "r");
    if (!file)
        return -1;

    int fnsize = get_file_size(fileName);
    char *cnt = (char *)malloc(fnsize);
    unsigned int n_bytes = fread(cnt, 1, fnsize, file);

    int lines = 1;
    if (nflag)
        printf("   %d  ", lines);

    for (unsigned int i = 0; i < n_bytes; i++)
    {
        if (cnt[i] == '\n')
        {
            if (eflag)
                printf("$");
            if (nflag)
            {
                if (cnt[i + 1] == 0)
                    continue;
                lines++;
                printf("%c   %d  ", cnt[i], lines);
                cnt[i] = 0;
            }
            if (bflag)
            {
                if (cnt[i + 1] != '\n')
                {
                    lines++;
                    printf("%c   %d  ", cnt[i], lines);
                    cnt[i] = 0;
                }
                else
                    lines += 0;
            }
        }

        if (tflag)
        {
            if (cnt[i] == '\t')
            {
                printf("^I");
                continue;
            }
        }

        printf("%c", cnt[i]);
    }

    printf("\n");
    fclose(file);
    free(cnt);

    return 0;
}

static void usage(void)
{
    printf("Modo de empleo: cat [OPCIÓN]... [FICHERO]...\n\n"
           "  -b, --number-nonblank    No enumera las lineas en blanco, remplaza -n.\n"
           "  -e                       Lo mismo que -E.\n"
           "  -E, --show-ends          Muestra un $ al final de cada linea.\n"
           "  -n, --number             Enumera cada linea.\n"
           "  -t                       Lo mismo que -T.\n"
           "  -T, --show-tabs          Muestra los caracteres de tabulación como ^I\n"
           "      --help               Muestra esta ayuda y finaliza.\n"
           "      --version            Informa de la versión y finaliza.\n\n"

           "AmayaOS Coreutils %s (C) 2017 AmayaOS Team\n"
           "Licencia GNU GPL v3 <http://www.gnu.org/licenses/>.\n"
           "Reportar errores a través de http://bugs.amayaos.com o alvarostagg@openmailbox.org\n", VERSION);
}

static void version(void)
{
    printf("cat (AmayaOS Coreutils) v%s\n"
           "Copyright © 2017 AmayaOS Team.\n"
           "Licencia GPLv3+: GPL de GNU versión 3 o posterior\n"
           "<http://gnu.org/licenses/gpl.html>.\n"
           "Esto es software libre: usted es libre de cambiarlo y redistribuirlo.\n"
           "No hay NINGUNA GARANTÍA, hasta donde permite la ley.\n\n", VERSION);
}

static size_t get_file_size(const char *fileName)
{
    struct stat st;
    if (stat(fileName, &st) < 0)
        return -1;

    return st.st_size;
}

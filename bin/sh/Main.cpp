/*
 * Copyright (C) 2009 Niek Linnenbank, 2014 Dan Rulos
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

#include <API/ProcessCtl.h>
#include <Config.h>
#include <StringTokenizer.h>
#include "Shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(int argc, char **argv)
{
    Shell sh;
    FILE *fp;
    struct stat st;
    char *contents;

    /* Obtenemos los argumentos de la linea de comandos. */
    if (argc >= 2) {
        /* Ejecuta los comandos en cada archivo. */
        for (int i = 0; i < argc - 1; i++) {
            /* Revisamos el tamaño del archivo. */
            if (stat(argv[i + 1], &st) != 0) {
                printf("%s: error en stat() '%s': %s\r\n",
                        argv[0], argv[i + 1], strerror(errno));
                continue;
            }
            /* Abrimos el archivo. */
            if ((fp = fopen(argv[i + 1], "r")) == NULL) {
                printf("%s: error en fopen() '%s': %s\r\n",
                        argv[0], argv[i + 1], strerror(errno));
                continue;
            }
            /* Alojamos los datos almacenados en el buffer. */
            contents = new char[st.st_size];
            
            /* Leemos el archivo completo en la memoria. */
            if (fread(contents, st.st_size, 1, fp) != (size_t) st.st_size) {
                printf("%s: error en fread() '%s': %s\r\n",
                        argv[0], argv[i + 1], strerror(errno));
                fclose(fp);
                continue;
            }
            /* Parse it into lines. */
            StringTokenizer tok(contents, '\n');

            /* Ejecutamos cada comando. */
            while (tok.hasNext()) {
                char *next = tok.next();
                if(next[0] == '#')
                    continue;
                sh.execute(next);
            }
            
            /* Limpiamos. */
            delete contents;
            fclose(fp);
        }
    }
    
    /* Ejecuta una consola interactiva. */
    else {
        /* Reabre la E/S estándar. */
        for (Size i = 0; i < 2; i++) {
            close(i);
            open("/dev/tty0", O_RDWR);
        }
        /* Show the user where to get help. */
        printf("\r\n"
                /*"Entering Shell. Type 'help' for the command list.\r\n"
                "\r\n"*/);

        /* Entramos al modo grafico */
        int ix=0;
        for (ix=0; ix < 1; ix++) {
          sh.execute("sh /home/live/mode2");
        }
        /* Entra al bucle. */
        return sh.run();
    }
    
    /* Listo. */
    return EXIT_SUCCESS;
}

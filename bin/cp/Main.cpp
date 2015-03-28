/*
 * Copyright (C) 2015 Dan Rulos.
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
#include <errno.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <files.h>

char *sp(char *path)
{
     int p=0;
     for (int i=0; i <= strlen(path); i++) {
	if (path[i] == '/') {
	  p = i;
	}
     }
     char name[128];
     int z=0;
     for (int i=p; i <= strlen(path); i++) {
	name[z] = path[i];
	z++;
     }
     return name;
}

/* NOT SUPPORTED */
int cp_dir(char *origen, char *destino)
{
    printf("Operacion no soportada\n");
    return 0;
}

int cp_ch(char *origen, char *destino, dev_t id)
{
    int fd;
    file *f = new file();
    f->setpath(origen);
    f->f_open(O_RDONLY);
    char *ch = f->readAll();
    f->f_close();
    char ruta[512];
    strcpy(ruta, destino);
    char *pathorigen = sp(origen);
    strcat(ruta, pathorigen);
    /* comprobamos que la ruta esté disponible */
    if (strcmp(ruta, origen) == 0) {
	printf("Error al crear '%s': Ruta en uso.\n", ruta);
	return -1;
    }
    /* crear el archivo de destino */
    mknod(ruta, S_IFCHR, id);
    if ((fd = open(ruta, O_WRONLY)) < 0) {
        printf("Error al abrir '%s': %s\r\n",
                ruta, strerror(errno));
        return errno;
    }
    write(fd, ch, strlen(ch));
    return 0;
}

int cp_simple(char *origen, char *destino)
{
    int fd;
    file *f = new file();
    f->setpath(origen);
    f->f_open(O_RDONLY);
    char *ch = f->readAll();
    f->f_close();
    char ruta[512];
    strcpy(ruta, destino);
    char *pathorigen = sp(origen);
    strcat(ruta, pathorigen);
    /* comprobamos que la ruta esté disponible */
    if (strcmp(ruta, origen) == 0) {
	printf("Error al crear '%s': Ruta en uso.\n", ruta);
	return -1;
    }
    /* crear el archivo de destino */
    touch(ruta, S_IWUSR | S_IRUSR);
    if ((fd = open(ruta, O_WRONLY)) < 0) {
        printf("Error al abrir '%s': %s\r\n",
                ruta, strerror(errno));
        return errno;
    }
    write(fd, ch, strlen(ch));
    return 0;
}

int main(int argc, char **argv)
{
    if (argc < 3) {
      printf("Uso: %s origen destino\r\n", argv[0]);
      return EXIT_FAILURE;
    }
    struct stat st;

    /* Intentar stat el archivo. */
    if ((stat(argv[1], &st)) < 0) {
        printf("%s: failed to stat '%s': %s\r\n",
            argv[0], argv[1], strerror(errno));
        return EXIT_FAILURE;
    }
    /* tipo de archivo */
    if (S_ISREG(st.st_mode)) {
	/* fichero común */
        cp_simple(argv[1], argv[2]);
    }
    else if (S_ISDIR(st.st_mode)) {
	/* directorio */
        cp_dir(argv[1], argv[2]);
    }
    else if (S_ISCHR(st.st_mode)) {
	/* character device */
	dev_t id;
	id.major = st.st_dev.major;
	id.minor = st.st_dev.minor;
        cp_ch(argv[1], argv[2], id);
    }
    else if (S_ISBLK(st.st_mode)) {
	/* block device */
        printf("Operación no soportada\r\n");	
    }
    else {
	/* desconocido */
        printf("Operación no soportada\r\n");
    }
}

#include "files.h"

int files::readAll(char *dest, char *path, int n)
{
    char buf[n];
    int fd, e;

    /* Limpiamos el buffer. */
    memset(buf, 0, sizeof(buf));
    
    fd = open(path, O_RDONLY);

    /* Intentamos abrir el archivo. */
    if (fd < 0)
        printf("%s", strerror(errno));
    else {
        e = read(fd, buf, n);
        switch (e) {
            /* Ocurrió un error. */
            case -1:
                printf("%s", strerror(errno));
                close(fd);
                return -1;
            /* Final de archivo. */
            case 0:
                close(fd);
                break;
            default:
                buf[e] = ZERO;
                break;
        }
    }
    
    close(fd);
    strlcpy(dest, buf, n);
    
    return 0;
}
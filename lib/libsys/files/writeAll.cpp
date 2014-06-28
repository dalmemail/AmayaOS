#include "files.h"

int files::writeAll(char *src, char *path, int n)
{
    int fd, e;
    
    fd = open(path, O_WRONLY);

    /* Intentamos abrir el archivo. */
    if (fd < 0) {
        printf("%s", strerror(errno));
        close(fd);
        return 0;
    }
    else {
        e = write(fd, src, n);
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
                break;
        }
    }
    close(fd);
    return 0;
}
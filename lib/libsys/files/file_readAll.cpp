#include <files.h>

char *file::readAll()
{
    char buffer[1024];
    int e, n = 1024;

    /* Limpiamos el buffer. */
    memset(buffer, 0, n);

    /* Intentamos abrir el archivo. */
    if (fd < 0)
        printf("%s", strerror(errno));
    else {
        e = read(fd, buffer, n);
        switch (e) {
            /* Ocurrió un error. */
            case -1:
                printf("%s", strerror(errno));
                return (char*)NULL;
            /* Final de archivo. */
            case 0:
                break;
            default:
                buffer[e] = ZERO;
                break;
        }
    }
    
    return buffer;
}
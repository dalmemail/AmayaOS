#include <files.h>

void file::f_close()
{
    close(fd);
    opened = false;
}
#include <files.h>

void file::setpath(char *path_s)
{
    if(!opened)
        path = path_s;
}
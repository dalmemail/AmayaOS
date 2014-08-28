#include <files.h>

int file::writeAll(char *buffer_s)
{
    if(opened)
        return files::writeAll(buffer_s, path, strlen(buffer_s));
    
    return -1;
}
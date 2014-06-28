#include <files.h>

int file::write_s(char *buffer_s, int n)
{
    if(opened)
        return files::writeAll(buffer_s, path, n);
    
    return -1;
}
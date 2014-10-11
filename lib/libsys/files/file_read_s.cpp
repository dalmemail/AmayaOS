#include <files.h>

char *file::read_s(int n)
{
    char *buffer;
    
    if(opened) {
        files::readAll(buffer, path, n);
        return buffer;
    }
    
    return (char*)NULL;
}
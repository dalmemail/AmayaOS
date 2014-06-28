#include <files.h>

file::file()
{
    opened = false;
}

file::~file()
{
    if(opened)
        close(fd);
}
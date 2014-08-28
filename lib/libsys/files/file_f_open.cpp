#include <files.h>

void file::f_open(int mode)
{
    fd = open(path, mode);
    opened = true;
}
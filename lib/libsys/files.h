#ifndef __LIBSYS_FILES_H
#define __LIBSYS_FILES_H

#include <unistd.h>
#include <fcntl.h>
#include <string.h>

namespace files
{  
    int readAll(char *dest, char *path, int n);
    int writeAll(char *src, char *path, int n);
};

class file
{
public:
    file();
    ~file();
    bool is_open();
    void f_open(int mode);
    void f_close();
    void setpath(char *path_s);
    char *readAll();
    char *read_s(int n);
    int writeAll(char *buffer_s);
    int write_s(char *buffer_s, int n);
    
private:
    bool opened;
    int fd;
    char *path;
};

#endif /* __LIBSYS_FILES_H */
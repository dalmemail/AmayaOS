#ifndef __LIBSYS_DEBUG_H
#define __LIBSYS_DEBUG_H

#include <stdio.h>
#include <Types.h>
#include <TerminalCodes.h>

namespace debug
{
    class out_t
    {
    public:
        out_t operator<< (const char *buffer);
        out_t operator<< (int buffer);
        out_t operator<< (u64 buffer);
        out_t operator<< (u32 buffer);
        out_t operator<< (u16 buffer);
        out_t operator<< (u8 buffer);
    };
    
    out_t out();
    
    class warning_t
    {
    public:
        warning_t operator<< (const char *buffer);
        warning_t operator<< (int buffer);
        warning_t operator<< (u64 buffer);
        warning_t operator<< (u32 buffer);
        warning_t operator<< (u16 buffer);
        warning_t operator<< (u8 buffer);
    };
    
    warning_t warning();
    
    class error_t
    {
    public:
        error_t operator<< (const char *buffer);
        error_t operator<< (int buffer);
        error_t operator<< (u64 buffer);
        error_t operator<< (u32 buffer);
        error_t operator<< (u16 buffer);
        error_t operator<< (u8 buffer);
    };
    
    error_t error();
    
    static char *endl = "\n";
};

#endif /* __LIBSYS_DEBUG_H */
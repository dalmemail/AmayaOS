#include <debug.h>

debug::out_t debug::out_t::operator<< (const char *buffer)
{
    printf(CYAN "%s" WHITE, buffer);
}

debug::out_t debug::out_t::operator<< (int buffer)
{
    printf(CYAN "%d" WHITE, buffer);
}

debug::out_t debug::out_t::operator<< (u64 buffer)
{
    printf(CYAN "%u" WHITE, buffer);
}

debug::out_t debug::out_t::operator<< (u32 buffer)
{
    printf(CYAN "%u" WHITE, buffer);
}

debug::out_t debug::out_t::operator<< (u16 buffer)
{
    printf(CYAN "%u" WHITE, buffer);
}

debug::out_t debug::out_t::operator<< (u8 buffer)
{
    printf(CYAN "%u" WHITE, buffer);
}

debug::out_t debug::out()
{   
}
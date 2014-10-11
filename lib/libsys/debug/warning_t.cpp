#include <debug.h>

debug::warning_t debug::warning_t::operator<< (const char *buffer)
{
    printf(YELLOW "%s" WHITE, buffer);
}

debug::warning_t debug::warning_t::operator<< (int buffer)
{
    printf(YELLOW "%d" WHITE, buffer);
}

debug::warning_t debug::warning_t::operator<< (u64 buffer)
{
    printf(YELLOW "%u" WHITE, buffer);
}

debug::warning_t debug::warning_t::operator<< (u32 buffer)
{
    printf(YELLOW "%u" WHITE, buffer);
}

debug::warning_t debug::warning_t::operator<< (u16 buffer)
{
    printf(YELLOW "%u" WHITE, buffer);
}

debug::warning_t debug::warning_t::operator<< (u8 buffer)
{
    printf(YELLOW "%u" WHITE, buffer);
}

debug::warning_t debug::warning()
{   
}
#include <debug.h>

debug::error_t debug::error_t::operator<< (const char *buffer)
{
    printf(RED "%s" WHITE, buffer);
}

debug::error_t debug::error_t::operator<< (int buffer)
{
    printf(RED "%d" WHITE, buffer);
}

debug::error_t debug::error_t::operator<< (u64 buffer)
{
    printf(RED "%u" WHITE, buffer);
}

debug::error_t debug::error_t::operator<< (u32 buffer)
{
    printf(RED "%u" WHITE, buffer);
}

debug::error_t debug::error_t::operator<< (u16 buffer)
{
    printf(RED "%u" WHITE, buffer);
}

debug::error_t debug::error_t::operator<< (u8 buffer)
{
    printf(RED "%u" WHITE, buffer);
}

debug::error_t debug::error()
{
}
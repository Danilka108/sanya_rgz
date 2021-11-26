#include <cstdlib>

#ifndef SANYA_RGZ_CONFIG_HPP
#define SANYA_RGZ_CONFIG_HPP

enum class Sign
{
    positive,
    negative,
};

enum class Compare
{
    smaller,
    equal,
    bigger,
};

struct Str_num
{
    char *chars;
    size_t len;
    Sign sign;
};

#endif //SANYA_RGZ_CONFIG_HPP

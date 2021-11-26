#include "io.hpp"

Str_num *scan_str_num()
{
    auto str = new char[1024];
    scanf("%1023s", str);
    return new_str_num_from_str(str);
}

void print_str_num(Str_num *num)
{
    if (num->sign == Sign::negative) printf("-");
    
    for (size_t i = 0, is_insignificant_zeros = 1; i < num->len; i++)
    {
        if (num->chars[i] == '0' && i != num->len - 1 && is_insignificant_zeros) continue;
        is_insignificant_zeros = 0;
        printf("%c", num->chars[i]);
    }
}

#include "multiply.hpp"

Str_num *multiply_unsigned_str_num_to_char(Str_num *str_num, char char_num)
{
    auto new_num = new_str_num(str_num->len + 1);
    
    int buffer = 0;
    for (ssize_t i = str_num->len - 1; i >= 0; i--)
    {
        int multiply = buffer + (str_num->chars[i] - '0') * (char_num - '0');
        new_num->chars[i + 1] = '0' + multiply % 10;
        buffer = multiply / 10;
    }
    
    new_num->chars[0] = '0' + buffer;
    trim_str_num_zeros(&new_num);
    
    return new_num;
}

Str_num *multiply_unsigned_str_nums(Str_num *max_num, Str_num *min_num)
{
    auto new_num = new_str_num_from_str("0");
    
    for (ssize_t i = min_num->len - 1; i >= 0; i--)
    {
        auto multiply_num = multiply_unsigned_str_num_to_char(max_num, min_num->chars[i]);
        add_zeros_to_str_num(&multiply_num, min_num->len - 1 - i);
        
        update_str_num(&new_num, sum_str_nums(new_num, multiply_num));
    }
    
    return new_num;
}

Str_num *multiply_str_nums(Str_num *a_num, Str_num *b_num)
{
    auto zero = new_str_num_from_str("0");
    
    auto is_a_num_zero = compare_unsigned_str_nums(a_num, zero) == Compare::equal;
    auto is_b_num_zero = compare_unsigned_str_nums(b_num, zero) == Compare::equal;
    
    if (is_a_num_zero || is_b_num_zero) return zero;
    delete zero;
    
    auto compare = compare_unsigned_str_nums(a_num, b_num);
    auto max_num = compare == Compare::bigger ? a_num : b_num;
    auto min_num = compare == Compare::smaller ? a_num : b_num;
    
    auto new_num = multiply_unsigned_str_nums(max_num, min_num);
    new_num->sign = a_num->sign == b_num->sign ? Sign::positive : Sign::negative;
    
    return new_num;
}
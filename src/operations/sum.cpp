#include "sum.hpp"

Str_num *sum_unsigned_str_nums(Str_num *max_num, Str_num *min_num)
{
    auto new_num = new_str_num(max_num->len + 1);
    auto delta_len = max_num->len - min_num->len;
    
    int buffer = 0;
    for (ssize_t i = max_num->len - 1; i >= 0; i--)
    {
        int sum = i < delta_len
                  ? (max_num->chars[i] - '0')
                  : (max_num->chars[i] - '0') + (min_num->chars[i - delta_len] - '0');
        sum += buffer;
        
        new_num->chars[i + 1] = '0' + sum % 10;
        buffer = sum / 10;
    }
    
    new_num->chars[0] = '0' + buffer;
    
    return new_num;
}

Str_num *subtract_unsigned_str_nums(Str_num *max_num, Str_num *min_num)
{
    auto new_num = new_str_num(max_num->len);
    size_t delta_len = max_num->len - min_num->len;
    
    int buffer = 0;
    for (ssize_t i = max_num->len - 1; i >= 0; i--)
    {
        int subtract = i >= delta_len
                       ? (max_num->chars[i] - '0') - (min_num->chars[i - delta_len] - '0')
                       : (max_num->chars[i] - '0');
        subtract += buffer;
        
        if (subtract < 0)
        {
            buffer = -1;
            subtract += 10;
        } else
        {
            buffer = subtract / 10;
        }
        
        new_num->chars[i] = '0' + subtract % 10;
    }
    
    return new_num;
}

Str_num *sum_str_nums(Str_num *a_num, Str_num *b_num, Sign sign)
{
    auto zero = new_str_num_from_str("0");
    
    auto *b_num_copy = copy_str_num(b_num);
    b_num_copy->sign = b_num_copy->sign == sign
                       ? Sign::positive
                       : Sign::negative;
    
    auto compare = compare_unsigned_str_nums(a_num, b_num);
    
    if (a_num->sign != b_num_copy->sign && compare == Compare::equal)
    {
        delete b_num_copy;
        return zero;
    }
    
    delete zero;
    
    auto max_num = compare == Compare::bigger ? a_num : b_num_copy;
    auto min_num = compare == Compare::smaller ? a_num : b_num_copy;
    
    auto new_num = a_num->sign == b_num_copy->sign
                   ? sum_unsigned_str_nums(max_num, min_num)
                   : subtract_unsigned_str_nums(max_num, min_num);
    
    new_num->sign = max_num->sign;
    trim_str_num_zeros(&new_num);
    
    delete b_num_copy;
    return new_num;
}
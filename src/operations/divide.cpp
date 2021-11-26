#include "divide.hpp"

Str_num *divide_remainder(Str_num **dividend, Str_num *divisor)
{
    auto one = new_str_num_from_str("1");
    auto quotient = new_str_num_from_str("0");
    auto remainder = new_str_num_from_str("0");
    
    Compare compare;
    do
    {
        update_str_num(&quotient, sum_str_nums(quotient, one));
        auto multiply_num = multiply_str_nums(divisor, quotient);
        
        compare = compare_unsigned_str_nums(multiply_num, *dividend);
        
        if (compare == Compare::bigger)
        {
            update_str_num(&quotient, sum_str_nums(quotient, one, Sign::negative));
            delete multiply_num;
            break;
        }
        
        update_str_num(&remainder, sum_str_nums(*dividend, multiply_num, Sign::negative));
        delete multiply_num;
    } while (compare == Compare::smaller);
    
    update_str_num(dividend, remainder);
    delete one;
    return quotient;
}

Str_num *divide_str_nums(Str_num *dividend, Str_num *divisor)
{
    auto one = new_str_num_from_str("1");
    auto zero = new_str_num_from_str("0");
    
    auto quotient = new_str_num_from_str("0");
    auto remainder = new_str_num_from_str("0");
    
    size_t slice_start = 0, slice_end = divisor->len;
    Compare compare;
    do
    {
        auto slice = get_str_num_slice(dividend, slice_start, slice_end);
        
        if (compare_unsigned_str_nums(remainder, zero) == Compare::equal)
        {
            update_str_num(&remainder, slice);
        } else
        {
            concat_str_num(&remainder, slice);
            delete slice;
        }
        
        if (compare_unsigned_str_nums(remainder, zero) == Compare::equal)
        {
            add_zeros_to_str_num(&quotient, 1);
            slice_start = slice_end;
            slice_end++;
            continue;
        }
        
        compare = compare_unsigned_str_nums(divisor, remainder);
        
        if (compare == Compare::bigger && slice_end > dividend->len)
        {
            add_zeros_to_str_num(&quotient, 1);
            break;
        }
        
        if (compare == Compare::bigger)
        {
            slice_start = slice_end;
            slice_end++;
            continue;
        }
        
        if (compare == Compare::equal)
        {
            concat_str_num(&quotient, one);
            update_str_num(&remainder, zero);
            
            slice_start = slice_end;
            slice_end++;
            continue;
        }
        
        concat_str_num(&quotient, divide_remainder(&remainder, divisor));
        
        slice_start = slice_end;
        slice_end++;
    } while (slice_end <= dividend->len);
    
    quotient->sign = dividend->sign == divisor->sign
                     ? Sign::positive
                     : Sign::negative;
    
    delete zero;
    delete one;
    delete remainder;
    
    return quotient;
}

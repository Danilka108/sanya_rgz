#include "str_num.hpp"

Str_num *new_str_num(size_t str_len, Sign sign)
{
    auto new_num = new Str_num;
    new_num->chars = new char[str_len];
    new_num->len = str_len;
    new_num->sign = sign;
    
    return new_num;
}

Str_num *new_str_num_from_str(const char *str)
{
    size_t copied_str_len = strlen(str);
    auto copied_str = new char[copied_str_len];
    Sign copied_str_sign = Sign::positive;
    
    for (int i = 0; i < copied_str_len; i++)
        copied_str[i] = str[i];
    
    if (copied_str[0] == '-')
    {
        copied_str_sign = Sign::negative;
        copied_str++;
        copied_str_len--;
    }
    
    auto new_num = new_str_num(copied_str_len, copied_str_sign);
    new_num->chars = copied_str;
    
    if (!validate_str_num(new_num))
    {
        printf("Ошбика! Недействительное значение числа.");
        exit(0);
    }
    
    return new_num;
}

void update_str_num(Str_num **num, Str_num *new_value)
{
    delete *num;
    *num = new_value;
}

Str_num *copy_str_num(Str_num *num)
{
    auto new_num = new_str_num(num->len, num->sign);
    
    for (size_t i = 0; i < num->len; i++)
        new_num->chars[i] = num->chars[i];
    
    return new_num;
}

void trim_str_num_zeros(Str_num **num)
{
    auto new_num = new_str_num((*num)->len, (*num)->sign);
    
    for (size_t i = 0, j = 0, is_insignificant_zeros = 1; i < (*num)->len; i++)
    {
        if ((i == 0 || is_insignificant_zeros) && i != (*num)->len - 1 && (*num)->chars[i] == '0')
            continue;
        
        is_insignificant_zeros = 0;
        
        new_num->chars[j++] = (*num)->chars[i];
        new_num->len = j;
    }
    
    update_str_num(num, new_num);
}

Str_num *get_str_num_slice(Str_num *num, size_t slice_start, size_t slice_end)
{
    auto new_num = new_str_num(slice_end - slice_start, num->sign);
    
    for (size_t i = slice_start, j = 0; i < slice_end && i < num->len; i++)
    {
        new_num->chars[j++] = num->chars[i];
        new_num->len = j;
    }
    
    return new_num;
}

void concat_str_num(Str_num **num, Str_num *additional_num)
{
    auto new_num = new_str_num((*num)->len + additional_num->len, (*num)->sign);
    
    for (size_t i = 0; i < new_num->len; i++)
    {
        if (i < (*num)->len) new_num->chars[i] = (*num)->chars[i];
        else new_num->chars[i] = additional_num->chars[i - (*num)->len];
    }
    
    update_str_num(num, new_num);
}

void add_zeros_to_str_num(Str_num **num, size_t zeros_count)
{
    auto new_num = new_str_num((*num)->len + zeros_count, (*num)->sign);
    
    for (int i = 0; i < new_num->len; i++)
        new_num->chars[i] = i < (*num)->len ? (*num)->chars[i] : '0';
    
    update_str_num(num, new_num);
}

Compare compare_unsigned_str_nums(Str_num *a_num, Str_num *b_num)
{
    if (a_num->len < b_num->len) return Compare::smaller;
    if (a_num->len > b_num->len) return Compare::bigger;
    
    for (size_t i = 0; i < a_num->len; i++)
    {
        if (a_num->chars[i] < b_num->chars[i]) return Compare::smaller;
        if (a_num->chars[i] > b_num->chars[i]) return Compare::bigger;
    }
    
    return Compare::equal;
}

int validate_str_num(Str_num *num)
{
    if (num->len > 1 && num->chars[0] == '0') return 0;
    
    for (size_t i = 0; i < num->len; i++)
    {
        if (num->chars[i] >= '0' && num->chars[i] <= '9') continue;
        return 0;
    }
    
    return 1;
}

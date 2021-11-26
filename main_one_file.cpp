#include <cstdlib>
#include <cstring>
#include <cstdio>

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

Str_num *new_str_num(size_t, Sign = Sign::positive);

Str_num *new_str_num_from_str(const char *);

void update_str_num(Str_num **, Str_num *);

Str_num *copy_str_num(Str_num *);

void trim_str_num_zeros(Str_num **);

Str_num *get_str_num_slice(Str_num *, size_t, size_t);

void concat_str_num(Str_num **, Str_num *);

void add_zeros_to_str_num(Str_num **num, size_t zeros_count);

Compare compare_unsigned_str_nums(Str_num *, Str_num *);

int validate_str_num(Str_num *);

Str_num *scan_str_num();

void print_str_num(Str_num *);

Str_num *sum_unsigned_str_nums(Str_num *, Str_num *);

Str_num *subtract_unsigned_str_nums(Str_num *, Str_num *);

Str_num *sum_str_nums(Str_num *, Str_num *, Sign = Sign::positive);

Str_num *multiply_unsigned_str_num_to_char(Str_num *, char);

Str_num *multiply_unsigned_str_nums(Str_num *, Str_num *);

Str_num *multiply_str_nums(Str_num *, Str_num *);

Str_num *divide_str_nums(Str_num *, Str_num *);

Str_num *divide_remainder(Str_num **, Str_num *);

void choose_operation();

int main()
{
    choose_operation();
    return 0;
}

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

void choose_operation()
{
    printf("Операции:\n 1 - сложение\n 2 - вычитание\n 3 - умножение\n 4 - деление\n");
    
    int operation;
    printf("Выберете операцию: ");
    scanf("%d", &operation);
    
    if (operation < 1 || operation > 4)
    {
        printf("Ошибка! Неверная операция.");
        exit(0);
    }
    
    printf("Введите первое число: ");
    auto a_num = scan_str_num();
    
    printf("Введите второе число: ");
    auto b_num = scan_str_num();
    
    Str_num *num;
    switch (operation)
    {
        case 1:
            num = sum_str_nums(a_num, b_num);
            break;
        case 2:
            num = sum_str_nums(a_num, b_num, Sign::negative);
            break;
        case 3:
            num = multiply_str_nums(a_num, b_num);
            break;
        case 4:
            num = divide_str_nums(a_num, b_num);
            break;
        default:
            printf("Ошибка! Неверная операция.");
            exit(0);
    }
    
    print_str_num(num);
}

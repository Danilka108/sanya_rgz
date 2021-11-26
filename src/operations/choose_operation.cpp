#include "choose_operation.hpp"

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

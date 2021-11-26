#include "../config.hpp"
#include <cstring>
#include <cstdio>

#ifndef SANYA_RGZ_LONG_NUM_HPP
#define SANYA_RGZ_LONG_NUM_HPP

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

#endif //SANYA_RGZ_LONG_NUM_HPP

#ifndef UTILITIES_H_
#define UTILITIES_H_

#include <stdbool.h>
#include <stdint.h>
#include <gmp.h>

void print_num(uint64_t *num);
void print_num_gmp(mpz_t num_gmp);
void clear_num(uint64_t *num);
void convert_gmp_to_num(uint64_t *num, mpz_t num_gmp);
void convert_num_to_gmp(mpz_t num_gmp, uint64_t *num);
bool is_equal_gmp_gmp(mpz_t num_gmp1, mpz_t num_gmp2);
bool is_equal_num_num(uint64_t *num1, uint64_t *num2);
bool is_equal_num_gmp(uint64_t *num, mpz_t num_gmp);

#endif

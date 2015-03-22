#ifndef UTILITIES_H_
#define UTILITIES_H_

#include <stdbool.h>
#include <stdint.h>
#include <gmp.h>

void print_num(uint64_t const * const num);
void print_num_gmp(mpz_t const num_gmp);
void clear_num(uint64_t * const num);
void convert_gmp_to_num(uint64_t * const num, mpz_t const num_gmp);
void convert_num_to_gmp(mpz_t num_gmp, uint64_t const * const num);
bool is_equal_num_num(uint64_t const * const num1, uint64_t const * const num2);
bool is_equal_num_gmp(uint64_t const * const num, mpz_t const num_gmp);
int cmp_num_gmp(uint64_t const * const num, mpz_t const num_gmp);
void generate_random_gmp(mpz_t num_gmp, unsigned int const precision_in_bits, uint64_t const * const strict_upper_bound, gmp_randstate_t gmp_random_state);

#endif

#ifndef UTILITIES_H_
#define UTILITIES_H_

#include <stdbool.h>
#include <stdint.h>
#include <gmp.h>
#include "constants.h"

// Only possible if you use gcc as the compiler
// typedef unsigned __int128 uint128_t;

void print_num(uint64_t const * const num, unsigned int const num_limbs);
void print_num_gmp(mpz_t const num_gmp, unsigned int const num_limbs);
void clear_num(uint64_t * const num, unsigned int const num_limbs);
void convert_gmp_to_num(uint64_t * const num, mpz_t const num_gmp, unsigned int const num_limbs);
void convert_num_to_gmp(mpz_t num_gmp, uint64_t const * const num, unsigned int const num_limbs);
bool is_equal_num_num(uint64_t const * const num1, uint64_t const * const num2, unsigned int const num_limbs);
bool is_equal_num_gmp(uint64_t const * const num, mpz_t const num_gmp, unsigned int const num_limbs);
int cmp_num_gmp(uint64_t const * const num, mpz_t const num_gmp, unsigned int const num_limbs);
void generate_random_gmp_less_than(mpz_t num_gmp, unsigned int const precision_in_bits, mpz_t strict_upper_bound_gmp, gmp_randstate_t gmp_random_state);
void generate_random_gmp_number(mpz_t num_gmp, unsigned int const precision_in_bits, gmp_randstate_t gmp_random_state);
void generate_random_prime_gmp_number(mpz_t num_gmp, unsigned int const precision_in_bits, gmp_randstate_t gmp_random_state);

#endif

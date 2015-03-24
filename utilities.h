#ifndef UTILITIES_H_
#define UTILITIES_H_

#include <stdbool.h>
#include <stdint.h>
#include <gmp.h>
#include "constants.h"

// Only possible if you use gcc as the compiler
//typedef unsigned __int128 uint128_t;

void print_num(uint64_t const *num, unsigned int const num_limbs);
void print_num_gmp(mpz_t const num_gmp, unsigned int const num_limbs);
void clear_num(uint64_t *num, unsigned int const num_limbs);
void convert_gmp_to_num(uint64_t *num, mpz_t const num_gmp, unsigned int const num_limbs);
void convert_num_to_gmp(mpz_t num_gmp, uint64_t const *num, unsigned int const num_limbs);
bool is_equal_num_num(uint64_t const *num1, uint64_t const * num2, unsigned int const num_limbs);
bool is_equal_num_gmp(uint64_t const num[NUM_LIMBS], mpz_t const num_gmp, unsigned int const num_limbs);
int cmp_num_gmp(uint64_t const num[NUM_LIMBS], mpz_t const num_gmp, unsigned int const num_limbs);
void generate_random_gmp(mpz_t num_gmp, unsigned int const precision_in_bits, uint64_t const *strict_upper_bound, unsigned int const upper_bound_num_limbs, gmp_randstate_t gmp_random_state);

#endif

#ifndef UTILITIES_H_
#define UTILITIES_H_

#include <stdbool.h>
#include <stdint.h>
#include <gmp.h>
#include "constants.h"

void print_num(uint64_t const num[NUM_LIMBS]);
void print_num_gmp(mpz_t const num_gmp);
void clear_num(uint64_t num[NUM_LIMBS]);
void convert_gmp_to_num(uint64_t num[NUM_LIMBS], mpz_t const num_gmp);
void convert_num_to_gmp(mpz_t num_gmp, uint64_t const num[NUM_LIMBS]);
bool is_equal_num_num(uint64_t const num1[NUM_LIMBS], uint64_t const num2[NUM_LIMBS]);
bool is_equal_num_gmp(uint64_t const num[NUM_LIMBS], mpz_t const num_gmp);
int cmp_num_gmp(uint64_t const num[NUM_LIMBS], mpz_t const num_gmp);
void generate_random_gmp(mpz_t num_gmp, unsigned int const precision_in_bits, uint64_t const strict_upper_bound[NUM_LIMBS], gmp_randstate_t gmp_random_state);

#endif

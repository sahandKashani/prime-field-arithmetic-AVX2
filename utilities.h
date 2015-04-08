#ifndef UTILITIES_H_
#define UTILITIES_H_

#include <stdbool.h>
#include <stdint.h>
#include <gmp.h>
#include "constants.h"

// Only possible if you use gcc as the compiler
// typedef unsigned __int128 uint128_t;

typedef struct {
	mpz_t big;
	mpz_t middle;
	mpz_t small;
} three_sorted_gmp;

void print_num(uint64_t const * const num, unsigned int const num_limbs);
void print_num_gmp(mpz_t const num_gmp, unsigned int const num_limbs);
void clear_num(uint64_t * const num, unsigned int const num_limbs);
void convert_gmp_to_num(uint64_t * const num, mpz_t const num_gmp, unsigned int const num_limbs);
void convert_num_to_gmp(mpz_t num_gmp, uint64_t const * const num, unsigned int const num_limbs);
bool is_equal_num_num(uint64_t const * const num1, uint64_t const * const num2, unsigned int const num_limbs);
bool is_equal_num_gmp(uint64_t const * const num, mpz_t const num_gmp, unsigned int const num_limbs);
int cmp_num_gmp(uint64_t const * const num, mpz_t const num_gmp, unsigned int const num_limbs);
void generate_random_gmp_less_than(mpz_t num_gmp, mpz_t strict_upper_bound_gmp, gmp_randstate_t gmp_random_state);
void generate_random_gmp_number(mpz_t num_gmp, unsigned int const precision_in_bits, gmp_randstate_t gmp_random_state);
void generate_random_prime_gmp_number(mpz_t num_gmp, unsigned int const precision_in_bits, gmp_randstate_t gmp_random_state);
three_sorted_gmp get_three_sorted_gmp(unsigned int precision_in_bits, gmp_randstate_t gmp_random_state);
void clear_three_sorted_gmp(three_sorted_gmp x);
void copy_num(uint64_t * const b, uint64_t const * const a, unsigned int const num_limbs);
void standard_to_montgomery(mpz_t montgomery, mpz_t standard, mpz_t mod);
void montgomery_to_standard(mpz_t standard, mpz_t montgomery, mpz_t mod);

#endif

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include "utilities.h"
#include "constants.h"
#include "prime_field_arithmetic.h"

void print_num(uint64_t const * const num, unsigned int const num_limbs) {
	for (unsigned int i = 0; i < num_limbs; i++) {
		printf("%0*" PRIx64, LIMB_SIZE_IN_HEX, num[num_limbs - i - 1]);
	}
	printf("\n");
}

void print_num_gmp(mpz_t const num_gmp, unsigned int const num_limbs) {
	gmp_printf("%0*Zx\n", num_limbs * LIMB_SIZE_IN_HEX, num_gmp);
}

void clear_num(uint64_t * const num, unsigned int const num_limbs) {
	for (unsigned int i = 0; i < num_limbs; i++) {
		num[i] = 0;
	}
}

void convert_gmp_to_num(uint64_t * const num, mpz_t const num_gmp, unsigned int const num_limbs) {
	// must clear the number, because GMP will only fill enough words that is
	// needed, so the last words of num may not be set automatically.
	clear_num(num, num_limbs);
	mpz_export(num, NULL, -1, LIMB_SIZE_IN_BYTES, 0, 0, num_gmp);
}

void convert_num_to_gmp(mpz_t num_gmp, uint64_t const * const num, unsigned int const num_limbs) {
	mpz_import(num_gmp, num_limbs, -1, LIMB_SIZE_IN_BYTES, 0, 0, num);
}

bool is_equal_num_num(uint64_t const * const num1, uint64_t const * const num2, unsigned int const num_limbs) {
	for (unsigned int i = 0; i < num_limbs; i++) {
		if (num1[i] != num2[i]) {
			return false;
		}
	}
	return true;
}

bool is_equal_num_gmp(uint64_t const * const num, mpz_t const num_gmp, unsigned int const num_limbs) {
	return cmp_num_gmp(num, num_gmp, num_limbs) == 0;
}

int cmp_num_gmp(uint64_t const * const num, mpz_t const num_gmp, unsigned int const num_limbs) {
	mpz_t tmp;
	mpz_init(tmp);
	convert_num_to_gmp(tmp, num, num_limbs);
	int result = mpz_cmp(tmp, num_gmp);
	mpz_clear(tmp);
	return result;
}

void generate_random_gmp(mpz_t num_gmp, unsigned int const precision_in_bits, uint64_t const * const strict_upper_bound, unsigned int const upper_bound_num_limbs, gmp_randstate_t gmp_random_state) {
	do {
		mpz_urandomb(num_gmp, gmp_random_state, precision_in_bits);
	} while (cmp_num_gmp(strict_upper_bound, num_gmp, upper_bound_num_limbs) != 1);
}

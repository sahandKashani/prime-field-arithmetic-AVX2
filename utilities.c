#include <inttypes.h>
#include <stdio.h>
#include "utilities.h"
#include "constants.h"
#include "prime_field_arithmetic.h"

void print_num(uint64_t const num[NUM_LIMBS]) {
	for (int i = NUM_LIMBS-1; i >= 0; i--) {
		printf("%0*" PRIx64, LIMB_SIZE_IN_HEX, num[i]);
	}
	printf("\n");
}

void print_num_gmp(mpz_t const num_gmp) {
	gmp_printf("%0*Zx\n", PRIME_FIELD_FULL_HEX_LENGTH, num_gmp);
}

void clear_num(uint64_t num[NUM_LIMBS]) {
	for (unsigned int i = 0; i < NUM_LIMBS; i++) {
		num[i] = 0;
	}
}

void convert_gmp_to_num(uint64_t num[NUM_LIMBS], mpz_t const num_gmp) {
	// must clear the number, because GMP will only fill enough words that is
	// needed, so the last words of num may not be set automatically.
	clear_num(num);
	mpz_export(num, NULL, -1, LIMB_SIZE_IN_BYTES, 0, 0, num_gmp);
}

void convert_num_to_gmp(mpz_t num_gmp, uint64_t const num[NUM_LIMBS]) {
	mpz_import(num_gmp, NUM_LIMBS, -1, LIMB_SIZE_IN_BYTES, 0, 0, num);
}

bool is_equal_num_num(uint64_t const num1[NUM_LIMBS], uint64_t const num2[NUM_LIMBS]) {
	for (unsigned int i = 0; i < NUM_LIMBS; i++) {
		if (num1[i] != num2[i]) {
			return false;
		}
	}
	return true;
}

bool is_equal_num_gmp(uint64_t const num[NUM_LIMBS], mpz_t const num_gmp) {
	uint64_t tmp[NUM_LIMBS];
	convert_gmp_to_num(tmp, num_gmp);
	return is_equal_num_num(tmp, num);
}

int cmp_num_gmp(uint64_t const num[NUM_LIMBS], mpz_t const num_gmp) {
	uint64_t tmp[NUM_LIMBS];
	convert_gmp_to_num(tmp, num_gmp);
	return cmp(num, tmp);
}

void generate_random_gmp(mpz_t num_gmp, unsigned int const precision_in_bits, uint64_t const strict_upper_bound[NUM_LIMBS], gmp_randstate_t gmp_random_state) {
	do {
		mpz_urandomb(num_gmp, gmp_random_state, precision_in_bits);
	} while (cmp_num_gmp(strict_upper_bound, num_gmp) != 1);
}

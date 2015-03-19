#include <inttypes.h>
#include <stdio.h>
#include "utilities.h"
#include "constants.h"

void print_num(uint64_t *num) {
	for (int i = NUM_LIMBS-1; i >= 0; i--) {
		printf("%0*" PRIx64, LIMB_SIZE_IN_HEX, num[i]);
	}
	printf("\n");
}

void print_num_gmp(mpz_t num_gmp) {
	gmp_printf("%0*Zx\n", PRIME_FIELD_FULL_HEX_LENGTH, num_gmp);
}

void clear_num(uint64_t *num) {
	for (unsigned int i = 0; i < NUM_LIMBS; i++) {
		num[i] = 0;
	}
}

void convert_gmp_to_num(uint64_t *num, mpz_t num_gmp) {
	// must clear the number, because GMP will only fill enough words that is
	// needed, so the last words of num may not be set automatically.
	clear_num(num);
	mpz_export(num, NULL, -1, LIMB_SIZE_IN_BYTES, 0, 0, num_gmp);
}

void convert_num_to_gmp(mpz_t num_gmp, uint64_t *num) {
	mpz_import(num_gmp, NUM_LIMBS, -1, LIMB_SIZE_IN_BYTES, 0, 0, num);
}

bool is_equal_gmp_gmp(mpz_t num_gmp1, mpz_t num_gmp2) {
	return (mpz_cmp(num_gmp1, num_gmp2) == 0);
}

bool is_equal_num_num(uint64_t *num1, uint64_t *num2) {
	for (unsigned int i = 0; i < NUM_LIMBS; i++) {
		if (num1[i] != num2[i]) {
			return false;
		}
	}
	return true;
}

bool is_equal_num_gmp(uint64_t *num, mpz_t num_gmp) {
	uint64_t tmp[NUM_LIMBS];
	convert_gmp_to_num(tmp, num_gmp);
	return is_equal_num_num(tmp, num);
}

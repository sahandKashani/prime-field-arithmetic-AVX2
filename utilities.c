#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
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

void generate_random_gmp_less_than(mpz_t num_gmp, mpz_t strict_upper_bound_gmp, gmp_randstate_t gmp_random_state) {
	mpz_urandomm(num_gmp, gmp_random_state, strict_upper_bound_gmp);
}

void generate_random_gmp_number(mpz_t num_gmp, unsigned int const precision_in_bits, gmp_randstate_t gmp_random_state) {
	mpz_rrandomb(num_gmp, gmp_random_state, precision_in_bits);
}

void generate_random_prime_gmp_number(mpz_t num_gmp, unsigned int const precision_in_bits, gmp_randstate_t gmp_random_state) {
	do {
		mpz_rrandomb(num_gmp, gmp_random_state, precision_in_bits);
	} while (mpz_probab_prime_p(num_gmp, 25) == 0); // definitely not composite
}

void standard_to_montgomery(mpz_t montgomery, mpz_t standard, mpz_t mod) {
	mpz_t R;
	mpz_init(R);
	mpz_ui_pow_ui(R, 2, NUM_MONTGOMERY_SHIFT_LIMBS * LIMB_SIZE_IN_BITS);

	mpz_mul(montgomery, standard, R);
	mpz_mod(montgomery, montgomery, mod);

	mpz_clear(R);
}

void montgomery_to_standard(mpz_t standard, mpz_t montgomery, mpz_t mod) {
	mpz_t R;
	mpz_init(R);
	mpz_ui_pow_ui(R, 2, NUM_MONTGOMERY_SHIFT_LIMBS * LIMB_SIZE_IN_BITS);

	mpz_t invR;
	mpz_init(invR);
	mpz_invert(invR, R, mod);

	mpz_mul(standard, montgomery, invR);
	mpz_mod(standard, standard, mod);

	mpz_clear(R);
	mpz_clear(invR);
}

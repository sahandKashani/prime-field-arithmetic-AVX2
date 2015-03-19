#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <gmp.h>
#include "constants.h"
#include "prime_field_arithmetic.h"

#define NUM_ITERATIONS (10000000L)
#define SEED (12345)

const uint64_t PRIME_MODULUS[] = {0x04L, 0x8E1D43F293469E33L, 0x194C43186B3ABC0BL};

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

bool test_add(unsigned int number_of_tests, unsigned int seed) {
	gmp_randstate_t gmp_random_state;
	gmp_randinit_default(gmp_random_state);
	gmp_randseed_ui(gmp_random_state, seed);

	mpz_t op1_gmp;
	mpz_t op2_gmp;
	mpz_t res_gmp;
	mpz_init(op1_gmp);
	mpz_init(op2_gmp);
	mpz_init(res_gmp);

	uint64_t op1[NUM_LIMBS];
	uint64_t op2[NUM_LIMBS];
	uint64_t res[NUM_LIMBS];

	for (unsigned int i = 0; i < number_of_tests; i++) {
		mpz_urandomb(op1_gmp, gmp_random_state, PRIME_FIELD_BINARY_BIT_LENGTH);
		mpz_urandomb(op2_gmp, gmp_random_state, PRIME_FIELD_BINARY_BIT_LENGTH);

		clear_num(op1);
		clear_num(op2);
		clear_num(res);

		convert_gmp_to_num(op1, op1_gmp);
		convert_gmp_to_num(op2, op2_gmp);
		convert_gmp_to_num(res, res_gmp);

		mpz_add(res_gmp, op1_gmp, op2_gmp);
		add(res, op1, op2, 0, NUM_LIMBS);

		if (!is_equal_num_gmp(res, res_gmp)) {
			is_equal_num_gmp(res, res_gmp);
			print_num_gmp(op1_gmp);
			print_num(op1);

			print_num_gmp(op2_gmp);
			print_num(op2);

			print_num_gmp(res_gmp);
			print_num(res);

			return false;
		}
	}

	return true;
}

bool test_sub(unsigned int number_of_tests, unsigned int seed) {
	gmp_randstate_t gmp_random_state;
	gmp_randinit_default(gmp_random_state);
	gmp_randseed_ui(gmp_random_state, seed);

	mpz_t op1_gmp;
	mpz_t op2_gmp;
	mpz_t res_gmp;
	mpz_init(op1_gmp);
	mpz_init(op2_gmp);
	mpz_init(res_gmp);

	uint64_t op1[NUM_LIMBS];
	uint64_t op2[NUM_LIMBS];
	uint64_t res[NUM_LIMBS];

	for (unsigned int i = 0; i < number_of_tests; i++) {
		mpz_urandomb(op1_gmp, gmp_random_state, PRIME_FIELD_BINARY_BIT_LENGTH);
		mpz_urandomb(op2_gmp, gmp_random_state, PRIME_FIELD_BINARY_BIT_LENGTH);

		// op1_gmp has to be bigger than op2_gmp, because this is normal
		// subtraction (no modular arithmetic)
		if (mpz_cmp(op1_gmp, op2_gmp) < 0) {
			mpz_swap(op1_gmp, op2_gmp);
		}

		clear_num(op1);
		clear_num(op2);
		clear_num(res);

		convert_gmp_to_num(op1, op1_gmp);
		convert_gmp_to_num(op2, op2_gmp);
		convert_gmp_to_num(res, res_gmp);

		mpz_sub(res_gmp, op1_gmp, op2_gmp);
		sub(res, op1, op2, 0, NUM_LIMBS);

		if (!is_equal_num_gmp(res, res_gmp)) {
			is_equal_num_gmp(res, res_gmp);
			print_num_gmp(op1_gmp);
			print_num(op1);

			print_num_gmp(op2_gmp);
			print_num(op2);

			print_num_gmp(res_gmp);
			print_num(res);

			return false;
		}
	}

	return true;
}

int main(void) {
	if (test_add(NUM_ITERATIONS, SEED)) {
		printf("Add: Success\n");
	} else {
		printf("Add: Failed\n");
	}

	if (test_sub(NUM_ITERATIONS, SEED)) {
		printf("Sub: Success\n");
	} else {
		printf("Sub: Failed\n");
	}

	return EXIT_SUCCESS;
}

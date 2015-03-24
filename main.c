#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <gmp.h>
#include "utilities.h"
#include "constants.h"
#include "prime_field_arithmetic.h"

#define NUM_ITERATIONS (100000L)
#define SEED (12345)

const uint64_t PRIME_MODULUS[] = {0x04L, 0x8E1D43F293469E33L, 0x194C43186B3ABC0BL};

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

	bool success = true;

	for (unsigned int i = 0; (i < number_of_tests) && success; i++) {
		generate_random_gmp(op1_gmp, PRIME_FIELD_BINARY_BIT_LENGTH, PRIME_MODULUS, NUM_LIMBS, gmp_random_state);
		generate_random_gmp(op2_gmp, PRIME_FIELD_BINARY_BIT_LENGTH, PRIME_MODULUS, NUM_LIMBS, gmp_random_state);

		clear_num(op1, NUM_LIMBS);
		clear_num(op2, NUM_LIMBS);
		clear_num(res, NUM_LIMBS);

		convert_gmp_to_num(op1, op1_gmp, NUM_LIMBS);
		convert_gmp_to_num(op2, op2_gmp, NUM_LIMBS);

		mpz_add(res_gmp, op1_gmp, op2_gmp);
		add(res, op1, op2, 0);

		if (!is_equal_num_gmp(res, res_gmp, NUM_LIMBS)) {
			print_num(op1, NUM_LIMBS);
			print_num(op2, NUM_LIMBS);
			print_num(res, NUM_LIMBS);
			success = false;
		}
	}

	mpz_clear(op1_gmp);
	mpz_clear(op2_gmp);
	mpz_clear(res_gmp);

	return success;
}

bool test_add_overlap_operands(unsigned int number_of_tests, unsigned int seed) {
	gmp_randstate_t gmp_random_state;
	gmp_randinit_default(gmp_random_state);
	gmp_randseed_ui(gmp_random_state, seed);

	mpz_t op1_gmp_before;
	mpz_t op1_gmp;
	mpz_t op2_gmp;
	mpz_init(op1_gmp_before);
	mpz_init(op1_gmp);
	mpz_init(op2_gmp);

	uint64_t op1_before[NUM_LIMBS];
	uint64_t op1[NUM_LIMBS];
	uint64_t op2[NUM_LIMBS];

	bool success = true;

	for (unsigned int i = 0; (i < number_of_tests) && success; i++) {
		generate_random_gmp(op1_gmp, PRIME_FIELD_BINARY_BIT_LENGTH, PRIME_MODULUS, NUM_LIMBS, gmp_random_state);
		generate_random_gmp(op2_gmp, PRIME_FIELD_BINARY_BIT_LENGTH, PRIME_MODULUS, NUM_LIMBS, gmp_random_state);
		mpz_set(op1_gmp_before, op1_gmp);

		clear_num(op1_before, NUM_LIMBS);
		clear_num(op1, NUM_LIMBS);
		clear_num(op2, NUM_LIMBS);

		convert_gmp_to_num(op1_before, op1_gmp_before, NUM_LIMBS);
		convert_gmp_to_num(op1, op1_gmp, NUM_LIMBS);
		convert_gmp_to_num(op2, op2_gmp, NUM_LIMBS);

		mpz_add(op1_gmp, op1_gmp, op2_gmp);
		add(op1, op1, op2, 0);

		if (!is_equal_num_gmp(op1, op1_gmp, NUM_LIMBS)) {
			print_num(op1_before, NUM_LIMBS);
			print_num(op2, NUM_LIMBS);
			print_num(op1, NUM_LIMBS);
			success = false;
		}
	}

	mpz_clear(op1_gmp);
	mpz_clear(op2_gmp);
	mpz_clear(op1_gmp_before);

	return success;
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

	bool success = true;

	for (unsigned int i = 0; (i < number_of_tests) && success; i++) {
		generate_random_gmp(op1_gmp, PRIME_FIELD_BINARY_BIT_LENGTH, PRIME_MODULUS, NUM_LIMBS, gmp_random_state);
		generate_random_gmp(op2_gmp, PRIME_FIELD_BINARY_BIT_LENGTH, PRIME_MODULUS, NUM_LIMBS, gmp_random_state);

		// op1_gmp has to be bigger than op2_gmp, because this is normal
		// subtraction (no modular arithmetic)
		if (mpz_cmp(op1_gmp, op2_gmp) == -1) {
			mpz_swap(op1_gmp, op2_gmp);
		}

		clear_num(op1, NUM_LIMBS);
		clear_num(op2, NUM_LIMBS);
		clear_num(res, NUM_LIMBS);

		convert_gmp_to_num(op1, op1_gmp, NUM_LIMBS);
		convert_gmp_to_num(op2, op2_gmp, NUM_LIMBS);

		mpz_sub(res_gmp, op1_gmp, op2_gmp);
		sub(res, op1, op2, 0);

		if (!is_equal_num_gmp(res, res_gmp, NUM_LIMBS)) {
			print_num(op1, NUM_LIMBS);
			print_num(op2, NUM_LIMBS);
			print_num(res, NUM_LIMBS);
			success = false;
		}
	}

	mpz_clear(op1_gmp);
	mpz_clear(op2_gmp);
	mpz_clear(res_gmp);

	return success;
}

bool test_sub_overlap_operands(unsigned int number_of_tests, unsigned int seed) {
	gmp_randstate_t gmp_random_state;
	gmp_randinit_default(gmp_random_state);
	gmp_randseed_ui(gmp_random_state, seed);

	mpz_t op1_gmp_before;
	mpz_t op1_gmp;
	mpz_t op2_gmp;
	mpz_init(op1_gmp_before);
	mpz_init(op1_gmp);
	mpz_init(op2_gmp);

	uint64_t op1_before[NUM_LIMBS];
	uint64_t op1[NUM_LIMBS];
	uint64_t op2[NUM_LIMBS];

	bool success = true;

	for (unsigned int i = 0; (i < number_of_tests) && success; i++) {
		generate_random_gmp(op1_gmp, PRIME_FIELD_BINARY_BIT_LENGTH, PRIME_MODULUS, NUM_LIMBS, gmp_random_state);
		generate_random_gmp(op2_gmp, PRIME_FIELD_BINARY_BIT_LENGTH, PRIME_MODULUS, NUM_LIMBS, gmp_random_state);

		// op1_gmp has to be bigger than op2_gmp, because this is normal
		// subtraction (no modular arithmetic)
		if (mpz_cmp(op1_gmp, op2_gmp) < 0) {
			mpz_swap(op1_gmp, op2_gmp);
		}

		mpz_set(op1_gmp_before, op1_gmp);

		clear_num(op1_before, NUM_LIMBS);
		clear_num(op1, NUM_LIMBS);
		clear_num(op2, NUM_LIMBS);

		convert_gmp_to_num(op1_before, op1_gmp_before, NUM_LIMBS);
		convert_gmp_to_num(op1, op1_gmp, NUM_LIMBS);
		convert_gmp_to_num(op2, op2_gmp, NUM_LIMBS);

		mpz_sub(op1_gmp, op1_gmp, op2_gmp);
		sub(op1, op1, op2, 0);

		if (!is_equal_num_gmp(op1, op1_gmp, NUM_LIMBS)) {
			print_num(op1_before, NUM_LIMBS);
			print_num(op2, NUM_LIMBS);
			print_num(op1, NUM_LIMBS);
			success = false;
		}
	}

	mpz_clear(op1_gmp);
	mpz_clear(op2_gmp);
	mpz_clear(op1_gmp_before);

	return success;
}

bool test_mul(unsigned int number_of_tests, unsigned int seed) {
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
	uint64_t res[2 * NUM_LIMBS];

	bool success = true;

	for (unsigned int i = 0; (i < number_of_tests) && success; i++) {
		generate_random_gmp(op1_gmp, PRIME_FIELD_BINARY_BIT_LENGTH, PRIME_MODULUS, NUM_LIMBS, gmp_random_state);
		generate_random_gmp(op2_gmp, PRIME_FIELD_BINARY_BIT_LENGTH, PRIME_MODULUS, NUM_LIMBS, gmp_random_state);

		clear_num(op1, NUM_LIMBS);
		clear_num(op2, NUM_LIMBS);
		clear_num(res, 2 * NUM_LIMBS);

		convert_gmp_to_num(op1, op1_gmp, NUM_LIMBS);
		convert_gmp_to_num(op2, op2_gmp, NUM_LIMBS);

		mpz_mul(res_gmp, op1_gmp, op2_gmp);
		mul(res, op1, op2);

		if (!is_equal_num_gmp(res, res_gmp, 2 * NUM_LIMBS)) {
			print_num(op1, NUM_LIMBS);
			print_num(op2, NUM_LIMBS);
			print_num(res, 2 * NUM_LIMBS);
			success = false;
		}
	}

	mpz_clear(op1_gmp);
	mpz_clear(op2_gmp);
	mpz_clear(res_gmp);

	return success;
}

bool test_cmp(unsigned int number_of_tests, unsigned int seed) {
	gmp_randstate_t gmp_random_state;
	gmp_randinit_default(gmp_random_state);
	gmp_randseed_ui(gmp_random_state, seed);

	mpz_t op1_gmp;
	mpz_t op2_gmp;
	mpz_init(op1_gmp);
	mpz_init(op2_gmp);

	uint64_t op1[NUM_LIMBS];
	uint64_t op2[NUM_LIMBS];

	bool success = true;

	for (unsigned int i = 0; (i < number_of_tests) && success; i++) {
		generate_random_gmp(op1_gmp, PRIME_FIELD_BINARY_BIT_LENGTH, PRIME_MODULUS, NUM_LIMBS, gmp_random_state);
		generate_random_gmp(op2_gmp, PRIME_FIELD_BINARY_BIT_LENGTH, PRIME_MODULUS, NUM_LIMBS, gmp_random_state);

		clear_num(op1, NUM_LIMBS);
		clear_num(op2, NUM_LIMBS);

		convert_gmp_to_num(op1, op1_gmp, NUM_LIMBS);
		convert_gmp_to_num(op2, op2_gmp, NUM_LIMBS);

		if (mpz_cmp(op1_gmp, op2_gmp) != cmp(op1, op2)) {
			print_num(op1, NUM_LIMBS);
			print_num(op2, NUM_LIMBS);

			success = false;
		}
	}

	mpz_clear(op1_gmp);
	mpz_clear(op2_gmp);

	return success;
}

bool test_add_mod(unsigned int number_of_tests, unsigned int seed) {
	gmp_randstate_t gmp_random_state;
	gmp_randinit_default(gmp_random_state);
	gmp_randseed_ui(gmp_random_state, seed);

	mpz_t op1_gmp;
	mpz_t op2_gmp;
	mpz_t mod_gmp;
	mpz_t res_gmp;
	mpz_init(op1_gmp);
	mpz_init(op2_gmp);
	mpz_init(mod_gmp);
	mpz_init(res_gmp);

	uint64_t op1[NUM_LIMBS];
	uint64_t op2[NUM_LIMBS];
	uint64_t mod[NUM_LIMBS];
	uint64_t res[NUM_LIMBS];

	bool success = true;

	for (unsigned int i = 0; (i < number_of_tests) && success; i++) {
		generate_random_gmp(mod_gmp, PRIME_FIELD_BINARY_BIT_LENGTH, PRIME_MODULUS, NUM_LIMBS, gmp_random_state);

		clear_num(mod, NUM_LIMBS);
		convert_gmp_to_num(mod, mod_gmp, NUM_LIMBS);

		generate_random_gmp(op1_gmp, PRIME_FIELD_BINARY_BIT_LENGTH, mod, NUM_LIMBS, gmp_random_state);
		generate_random_gmp(op2_gmp, PRIME_FIELD_BINARY_BIT_LENGTH, mod, NUM_LIMBS, gmp_random_state);

		clear_num(op1, NUM_LIMBS);
		clear_num(op2, NUM_LIMBS);
		clear_num(res, NUM_LIMBS);

		convert_gmp_to_num(op1, op1_gmp, NUM_LIMBS);
		convert_gmp_to_num(op2, op2_gmp, NUM_LIMBS);

		// modular addition
		mpz_add(res_gmp, op1_gmp, op2_gmp);
		mpz_mod(res_gmp, res_gmp, mod_gmp);
		add_mod(res, op1, op2, mod);

		if (!is_equal_num_gmp(res, res_gmp, NUM_LIMBS)) {
			print_num(op1, NUM_LIMBS);
			print_num(op2, NUM_LIMBS);
			print_num(mod, NUM_LIMBS);
			print_num(res, NUM_LIMBS);
			success = false;
		}
	}

	mpz_clear(op1_gmp);
	mpz_clear(op2_gmp);
	mpz_clear(mod_gmp);
	mpz_clear(res_gmp);

	return success;
}

bool test_sub_mod(unsigned int number_of_tests, unsigned int seed) {
	gmp_randstate_t gmp_random_state;
	gmp_randinit_default(gmp_random_state);
	gmp_randseed_ui(gmp_random_state, seed);

	mpz_t op1_gmp;
	mpz_t op2_gmp;
	mpz_t mod_gmp;
	mpz_t res_gmp;
	mpz_init(op1_gmp);
	mpz_init(op2_gmp);
	mpz_init(mod_gmp);
	mpz_init(res_gmp);

	uint64_t op1[NUM_LIMBS];
	uint64_t op2[NUM_LIMBS];
	uint64_t mod[NUM_LIMBS];
	uint64_t res[NUM_LIMBS];

	bool success = true;

	for (unsigned int i = 0; (i < number_of_tests) && success; i++) {
		generate_random_gmp(mod_gmp, PRIME_FIELD_BINARY_BIT_LENGTH, PRIME_MODULUS, NUM_LIMBS, gmp_random_state);

		clear_num(mod, NUM_LIMBS);
		convert_gmp_to_num(mod, mod_gmp, NUM_LIMBS);

		generate_random_gmp(op1_gmp, PRIME_FIELD_BINARY_BIT_LENGTH, mod, NUM_LIMBS, gmp_random_state);
		generate_random_gmp(op2_gmp, PRIME_FIELD_BINARY_BIT_LENGTH, mod, NUM_LIMBS, gmp_random_state);

		clear_num(op1, NUM_LIMBS);
		clear_num(op2, NUM_LIMBS);
		clear_num(res, NUM_LIMBS);

		convert_gmp_to_num(op1, op1_gmp, NUM_LIMBS);
		convert_gmp_to_num(op2, op2_gmp, NUM_LIMBS);

		// modular subtraction
		mpz_sub(res_gmp, op1_gmp, op2_gmp);
		mpz_mod(res_gmp, res_gmp, mod_gmp);
		sub_mod(res, op1, op2, mod);

		if (!is_equal_num_gmp(res, res_gmp, NUM_LIMBS)) {
			print_num(op1, NUM_LIMBS);
			print_num(op2, NUM_LIMBS);
			print_num(mod, NUM_LIMBS);
			print_num(res, NUM_LIMBS);
			success = false;
		}
	}

	mpz_clear(op1_gmp);
	mpz_clear(op2_gmp);
	mpz_clear(mod_gmp);
	mpz_clear(res_gmp);

	return success;
}

int main(void) {
	printf("Add: ");
	if (test_add(NUM_ITERATIONS, SEED)) {
		printf("Success\n");
	} else {
		printf("Failed\n");
	}

	printf("Sub: ");
	if (test_sub(NUM_ITERATIONS, SEED)) {
		printf("Success\n");
	} else {
		printf("Failed\n");
	}

	printf("Add with operand overlap: ");
	if (test_add_overlap_operands(NUM_ITERATIONS, SEED)) {
		printf("Success\n");
	} else {
		printf("Failed\n");
	}

	printf("Sub with operand overlap: ");
	if (test_sub_overlap_operands(NUM_ITERATIONS, SEED)) {
		printf("Success\n");
	} else {
		printf("Failed\n");
	}

	printf("cmp: ");
	if (test_cmp(NUM_ITERATIONS, SEED)) {
		printf("Success\n");
	} else {
		printf("Failed\n");
	}

	printf("Add Mod: ");
	if (test_add_mod(NUM_ITERATIONS, SEED)) {
		printf("Success\n");
	} else {
		printf("Failed\n");
	}

	printf("Sub Mod: ");
	if (test_sub_mod(NUM_ITERATIONS, SEED)) {
		printf("Success\n");
	} else {
		printf("Failed\n");
	}

	mul(NULL, NULL, NULL);

	return EXIT_SUCCESS;
}

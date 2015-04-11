#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <gmp.h>
#include "utilities.h"
#include "constants.h"
#include "prime_field_arithmetic.h"

#define NUM_ITERATIONS (100000L)
#define SEED (12345)

bool test_add(unsigned int number_of_tests, unsigned int seed) {
	gmp_randstate_t gmp_random_state;
	gmp_randinit_default(gmp_random_state);
	gmp_randseed_ui(gmp_random_state, seed);

	mpz_t op1_gmp;
	mpz_t op2_gmp;
	mpz_t res_gmp;
	mpz_t mod_gmp;
	mpz_init(op1_gmp);
	mpz_init(op2_gmp);
	mpz_init(res_gmp);
	mpz_init(mod_gmp);

	uint64_t op1[NUM_LIMBS];
	uint64_t op2[NUM_LIMBS];
	uint64_t res[NUM_LIMBS];

	bool success = true;

	for (unsigned int i = 0; (i < number_of_tests) && success; i++) {
		three_sorted_gmp operands = get_three_sorted_gmp(PRIME_FIELD_BINARY_BIT_LENGTH, gmp_random_state);
		mpz_set(op1_gmp, operands.small);
		mpz_set(op2_gmp, operands.middle);
		mpz_set(mod_gmp, operands.big);

		clear_num(op1, NUM_LIMBS);
		clear_num(op2, NUM_LIMBS);
		clear_num(res, NUM_LIMBS);

		convert_gmp_to_num(op1, op1_gmp, NUM_LIMBS);
		convert_gmp_to_num(op2, op2_gmp, NUM_LIMBS);

		mpz_add(res_gmp, op1_gmp, op2_gmp);
		add(res, op1, op2, NUM_LIMBS, 0);

		if (!is_equal_num_gmp(res, res_gmp, NUM_LIMBS)) {
			print_num_gmp(op1_gmp, NUM_LIMBS);
			print_num(op1, NUM_LIMBS);
			print_num_gmp(op2_gmp, NUM_LIMBS);
			print_num(op2, NUM_LIMBS);
			print_num_gmp(res_gmp, NUM_LIMBS);
			print_num(res, NUM_LIMBS);
			success = false;
		}

		clear_three_sorted_gmp(operands);
	}

	mpz_clear(op1_gmp);
	mpz_clear(op2_gmp);
	mpz_clear(res_gmp);
	mpz_clear(mod_gmp);
	gmp_randclear(gmp_random_state);

	return success;
}

bool test_add_num_64(unsigned int number_of_tests, unsigned int seed) {
	gmp_randstate_t gmp_random_state;
	gmp_randinit_default(gmp_random_state);
	gmp_randseed_ui(gmp_random_state, seed);

	mpz_t op1_gmp;
	mpz_t op2_gmp;
	mpz_t res_gmp;
	mpz_t mod_gmp;
	mpz_init(op1_gmp);
	mpz_init(op2_gmp);
	mpz_init(res_gmp);
	mpz_init(mod_gmp);

	uint64_t op1[NUM_LIMBS];
	uint64_t op2;
	uint64_t res[NUM_LIMBS];

	bool success = true;

	for (unsigned int i = 0; (i < number_of_tests) && success; i++) {
		three_sorted_gmp operands = get_three_sorted_gmp(PRIME_FIELD_BINARY_BIT_LENGTH, gmp_random_state);
		mpz_set(op1_gmp, operands.middle);
		mpz_set(mod_gmp, operands.big);

		generate_random_gmp_number(op2_gmp, LIMB_SIZE_IN_BITS, gmp_random_state);

		clear_num(op1, NUM_LIMBS);
		op2 = 0;
		clear_num(res, NUM_LIMBS);

		convert_gmp_to_num(op1, op1_gmp, NUM_LIMBS);
		convert_gmp_to_num(&op2, op2_gmp, 1);

		mpz_add(res_gmp, op1_gmp, op2_gmp);
		add_num_64(res, op1, op2, NUM_LIMBS, 0);

		if (!is_equal_num_gmp(res, res_gmp, NUM_LIMBS)) {
			print_num_gmp(op1_gmp, NUM_LIMBS);
			print_num(op1, NUM_LIMBS);
			print_num_gmp(op2_gmp, NUM_LIMBS);
			printf("%0*" PRIx64 "\n", LIMB_SIZE_IN_HEX, op2);
			print_num_gmp(res_gmp, NUM_LIMBS);
			print_num(res, NUM_LIMBS);
			success = false;
		}

		clear_three_sorted_gmp(operands);
	}

	mpz_clear(op1_gmp);
	mpz_clear(op2_gmp);
	mpz_clear(res_gmp);
	mpz_clear(mod_gmp);
	gmp_randclear(gmp_random_state);

	return success;
}

bool test_sub(unsigned int number_of_tests, unsigned int seed) {
	gmp_randstate_t gmp_random_state;
	gmp_randinit_default(gmp_random_state);
	gmp_randseed_ui(gmp_random_state, seed);

	mpz_t op1_gmp;
	mpz_t op2_gmp;
	mpz_t res_gmp;
	mpz_t mod_gmp;
	mpz_init(op1_gmp);
	mpz_init(op2_gmp);
	mpz_init(res_gmp);
	mpz_init(mod_gmp);

	uint64_t op1[NUM_LIMBS];
	uint64_t op2[NUM_LIMBS];
	uint64_t res[NUM_LIMBS];

	bool success = true;

	for (unsigned int i = 0; (i < number_of_tests) && success; i++) {
		three_sorted_gmp operands = get_three_sorted_gmp(PRIME_FIELD_BINARY_BIT_LENGTH, gmp_random_state);
		// op2 has to be smaller than op1 since this is normal subtraction (not modular)
		mpz_set(op1_gmp, operands.middle);
		mpz_set(op2_gmp, operands.small);
		mpz_set(mod_gmp, operands.big);

		clear_num(op1, NUM_LIMBS);
		clear_num(op2, NUM_LIMBS);
		clear_num(res, NUM_LIMBS);

		convert_gmp_to_num(op1, op1_gmp, NUM_LIMBS);
		convert_gmp_to_num(op2, op2_gmp, NUM_LIMBS);

		mpz_sub(res_gmp, op1_gmp, op2_gmp);
		sub(res, op1, op2, NUM_LIMBS, 0);

		if (!is_equal_num_gmp(res, res_gmp, NUM_LIMBS)) {
			print_num_gmp(op1_gmp, NUM_LIMBS);
			print_num(op1, NUM_LIMBS);
			print_num_gmp(op2_gmp, NUM_LIMBS);
			print_num(op2, NUM_LIMBS);
			print_num_gmp(res_gmp, NUM_LIMBS);
			print_num(res, NUM_LIMBS);
			success = false;
		}

		clear_three_sorted_gmp(operands);
	}

	mpz_clear(op1_gmp);
	mpz_clear(op2_gmp);
	mpz_clear(res_gmp);
	mpz_clear(mod_gmp);
	gmp_randclear(gmp_random_state);

	return success;
}

bool test_mul64_to_128(unsigned int number_of_tests, unsigned int seed) {
	gmp_randstate_t gmp_random_state;
	gmp_randinit_default(gmp_random_state);
	gmp_randseed_ui(gmp_random_state, seed);

	mpz_t op1_gmp;
	mpz_t op2_gmp;
	mpz_t res_gmp;
	mpz_init(op1_gmp);
	mpz_init(op2_gmp);
	mpz_init(res_gmp);

	uint64_t op1;
	uint64_t op2;
	uint64_t res[2];

	bool success = true;

	for (unsigned int i = 0; (i < number_of_tests) && success; i++) {
		generate_random_gmp_number(op1_gmp, LIMB_SIZE_IN_BITS, gmp_random_state);
		generate_random_gmp_number(op2_gmp, LIMB_SIZE_IN_BITS, gmp_random_state);

		op1 = 0;
		op2 = 0;
		clear_num(res, 2);

		convert_gmp_to_num(&op1, op1_gmp, 1);
		convert_gmp_to_num(&op2, op2_gmp, 1);

		mpz_mul(res_gmp, op1_gmp, op2_gmp);
		mul64_to_128(res + 1, res, op1, op2);

		if (!is_equal_num_gmp(res, res_gmp, 2)) {
			print_num_gmp(op1_gmp, NUM_LIMBS);
			printf("%0*" PRIx64 "\n", LIMB_SIZE_IN_HEX, op1);
			print_num_gmp(op2_gmp, NUM_LIMBS);
			printf("%0*" PRIx64 "\n", LIMB_SIZE_IN_HEX, op2);
			print_num_gmp(res_gmp, NUM_LIMBS);
			print_num(res, 2);
			success = false;
		}
	}

	mpz_clear(op1_gmp);
	mpz_clear(op2_gmp);
	mpz_clear(res_gmp);
	gmp_randclear(gmp_random_state);

	return success;
}

bool test_mul_num_64(unsigned int number_of_tests, unsigned int seed) {
	gmp_randstate_t gmp_random_state;
	gmp_randinit_default(gmp_random_state);
	gmp_randseed_ui(gmp_random_state, seed);

	mpz_t op1_gmp;
	mpz_t op2_gmp;
	mpz_t res_gmp;
	mpz_t mod_gmp;
	mpz_init(op1_gmp);
	mpz_init(op2_gmp);
	mpz_init(res_gmp);
	mpz_init(mod_gmp);

	uint64_t op1[NUM_LIMBS];
	uint64_t op2;
	uint64_t res[NUM_LIMBS + 1];

	bool success = true;

	for (unsigned int i = 0; (i < number_of_tests) && success; i++) {
		three_sorted_gmp operands = get_three_sorted_gmp(PRIME_FIELD_BINARY_BIT_LENGTH, gmp_random_state);
		mpz_set(op1_gmp, operands.middle);
		mpz_set(mod_gmp, operands.big);

		generate_random_gmp_number(op2_gmp, LIMB_SIZE_IN_BITS, gmp_random_state);

		clear_num(op1, NUM_LIMBS);
		op2 = 0;
		clear_num(res, NUM_LIMBS);

		convert_gmp_to_num(op1, op1_gmp, NUM_LIMBS);
		convert_gmp_to_num(&op2, op2_gmp, 1);

		mpz_mul(res_gmp, op1_gmp, op2_gmp);
		mul_num_64(res, op1, op2, NUM_LIMBS);

		if (!is_equal_num_gmp(res, res_gmp, NUM_LIMBS + 1)) {
			print_num_gmp(op1_gmp, NUM_LIMBS);
			print_num(op1, NUM_LIMBS);
			print_num_gmp(op2_gmp, NUM_LIMBS);
			printf("%0*" PRIx64 "\n", LIMB_SIZE_IN_HEX, op2);
			print_num_gmp(res_gmp, NUM_LIMBS + 1);
			print_num(res, NUM_LIMBS + 1);
			success = false;
		}

		clear_three_sorted_gmp(operands);
	}

	mpz_clear(op1_gmp);
	mpz_clear(op2_gmp);
	mpz_clear(res_gmp);
	mpz_clear(mod_gmp);
	gmp_randclear(gmp_random_state);

	return success;
}

bool test_mul(unsigned int number_of_tests, unsigned int seed) {
	gmp_randstate_t gmp_random_state;
	gmp_randinit_default(gmp_random_state);
	gmp_randseed_ui(gmp_random_state, seed);

	mpz_t op1_gmp;
	mpz_t op2_gmp;
	mpz_t res_gmp;
	mpz_t mod_gmp;
	mpz_init(op1_gmp);
	mpz_init(op2_gmp);
	mpz_init(res_gmp);
	mpz_init(mod_gmp);

	uint64_t op1[NUM_LIMBS];
	uint64_t op2[NUM_LIMBS];
	uint64_t res[2 * NUM_LIMBS];

	bool success = true;

	for (unsigned int i = 0; (i < number_of_tests) && success; i++) {
		three_sorted_gmp operands = get_three_sorted_gmp(PRIME_FIELD_BINARY_BIT_LENGTH, gmp_random_state);
		mpz_set(op1_gmp, operands.small);
		mpz_set(op2_gmp, operands.middle);
		mpz_set(mod_gmp, operands.big);

		clear_num(op1, NUM_LIMBS);
		clear_num(op2, NUM_LIMBS);
		clear_num(res, 2 * NUM_LIMBS);

		convert_gmp_to_num(op1, op1_gmp, NUM_LIMBS);
		convert_gmp_to_num(op2, op2_gmp, NUM_LIMBS);

		mpz_mul(res_gmp, op1_gmp, op2_gmp);
		mul(res, op1, op2, NUM_LIMBS);

		if (!is_equal_num_gmp(res, res_gmp, 2 * NUM_LIMBS)) {
			print_num_gmp(op1_gmp, NUM_LIMBS);
			print_num(op1, NUM_LIMBS);
			print_num_gmp(op2_gmp, NUM_LIMBS);
			print_num(op2, NUM_LIMBS);
			print_num_gmp(res_gmp, 2 * NUM_LIMBS);
			print_num(res, 2 * NUM_LIMBS);
			success = false;
		}

		clear_three_sorted_gmp(operands);
	}

	mpz_clear(op1_gmp);
	mpz_clear(op2_gmp);
	mpz_clear(res_gmp);
	mpz_clear(mod_gmp);
	gmp_randclear(gmp_random_state);

	return success;
}

bool test_cmp(unsigned int number_of_tests, unsigned int seed) {
	gmp_randstate_t gmp_random_state;
	gmp_randinit_default(gmp_random_state);
	gmp_randseed_ui(gmp_random_state, seed);

	mpz_t op1_gmp;
	mpz_t op2_gmp;
	mpz_t mod_gmp;
	mpz_init(op1_gmp);
	mpz_init(op2_gmp);
	mpz_init(mod_gmp);

	uint64_t op1[NUM_LIMBS];
	uint64_t op2[NUM_LIMBS];

	bool success = true;

	for (unsigned int i = 0; (i < number_of_tests) && success; i++) {
		generate_random_gmp_number(mod_gmp, PRIME_FIELD_BINARY_BIT_LENGTH, gmp_random_state);
		generate_random_gmp_less_than(op1_gmp, mod_gmp, gmp_random_state);
		generate_random_gmp_less_than(op2_gmp, mod_gmp, gmp_random_state);

		clear_num(op1, NUM_LIMBS);
		clear_num(op2, NUM_LIMBS);

		convert_gmp_to_num(op1, op1_gmp, NUM_LIMBS);
		convert_gmp_to_num(op2, op2_gmp, NUM_LIMBS);

		int res_gmp = mpz_cmp(op1_gmp, op2_gmp);
		int res = cmp(op1, op2, NUM_LIMBS);

		if (res_gmp != res) {
			print_num_gmp(op1_gmp, NUM_LIMBS);
			print_num(op1, NUM_LIMBS);
			print_num_gmp(op2_gmp, NUM_LIMBS);
			print_num(op2, NUM_LIMBS);
			printf("%d\n", res_gmp);
			printf("%d\n", res);

			success = false;
		}
	}

	mpz_clear(op1_gmp);
	mpz_clear(op2_gmp);
	mpz_clear(mod_gmp);
	gmp_randclear(gmp_random_state);

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
		three_sorted_gmp operands = get_three_sorted_gmp(PRIME_FIELD_BINARY_BIT_LENGTH, gmp_random_state);
		mpz_set(op1_gmp, operands.small);
		mpz_set(op2_gmp, operands.middle);
		mpz_set(mod_gmp, operands.big);

		clear_num(op1, NUM_LIMBS);
		clear_num(op2, NUM_LIMBS);
		clear_num(mod, NUM_LIMBS);
		clear_num(res, NUM_LIMBS);

		convert_gmp_to_num(op1, op1_gmp, NUM_LIMBS);
		convert_gmp_to_num(op2, op2_gmp, NUM_LIMBS);
		convert_gmp_to_num(mod, mod_gmp, NUM_LIMBS);

		// modular addition
		mpz_add(res_gmp, op1_gmp, op2_gmp);
		mpz_mod(res_gmp, res_gmp, mod_gmp);
		add_mod(res, op1, op2, mod, NUM_LIMBS);

		if (!is_equal_num_gmp(res, res_gmp, NUM_LIMBS)) {
			add_mod(res, op1, op2, mod, NUM_LIMBS);
			print_num_gmp(op1_gmp, NUM_LIMBS);
			print_num(op1, NUM_LIMBS);
			print_num_gmp(op2_gmp, NUM_LIMBS);
			print_num(op2, NUM_LIMBS);
			print_num_gmp(mod_gmp, NUM_LIMBS);
			print_num(mod, NUM_LIMBS);
			print_num_gmp(res_gmp, NUM_LIMBS);
			print_num(res, NUM_LIMBS);
			success = false;
		}

		clear_three_sorted_gmp(operands);
	}

	mpz_clear(op1_gmp);
	mpz_clear(op2_gmp);
	mpz_clear(mod_gmp);
	mpz_clear(res_gmp);
	gmp_randclear(gmp_random_state);

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
		three_sorted_gmp operands = get_three_sorted_gmp(PRIME_FIELD_BINARY_BIT_LENGTH, gmp_random_state);
		mpz_set(op1_gmp, operands.small);
		mpz_set(op2_gmp, operands.middle);
		mpz_set(mod_gmp, operands.big);

		clear_num(op1, NUM_LIMBS);
		clear_num(op2, NUM_LIMBS);
		clear_num(mod, NUM_LIMBS);
		clear_num(res, NUM_LIMBS);

		convert_gmp_to_num(op1, op1_gmp, NUM_LIMBS);
		convert_gmp_to_num(op2, op2_gmp, NUM_LIMBS);
		convert_gmp_to_num(mod, mod_gmp, NUM_LIMBS);

		// modular subtraction
		mpz_sub(res_gmp, op1_gmp, op2_gmp);
		mpz_mod(res_gmp, res_gmp, mod_gmp);
		sub_mod(res, op1, op2, mod, NUM_LIMBS);

		if (!is_equal_num_gmp(res, res_gmp, NUM_LIMBS)) {
			print_num_gmp(op1_gmp, NUM_LIMBS);
			print_num(op1, NUM_LIMBS);
			print_num_gmp(op2_gmp, NUM_LIMBS);
			print_num(op2, NUM_LIMBS);
			print_num_gmp(mod_gmp, NUM_LIMBS);
			print_num(mod, NUM_LIMBS);
			print_num_gmp(res_gmp, NUM_LIMBS);
			print_num(res, NUM_LIMBS);
			success = false;
		}

		clear_three_sorted_gmp(operands);
	}

	mpz_clear(op1_gmp);
	mpz_clear(op2_gmp);
	mpz_clear(mod_gmp);
	mpz_clear(res_gmp);
	gmp_randclear(gmp_random_state);

	return success;
}

bool test_mul_montgomery(unsigned int number_of_tests, unsigned int seed) {
	gmp_randstate_t gmp_random_state;
	gmp_randinit_default(gmp_random_state);
	gmp_randseed_ui(gmp_random_state, seed);

	mpz_t op1_gmp;
	mpz_t op2_gmp;
	mpz_t mod_gmp;
	mpz_t mod_prime_gmp;
	mpz_t res_gmp;
	mpz_t base_gmp;
	mpz_t R_gmp;
	mpz_t invR_gmp;
	mpz_init(op1_gmp);
	mpz_init(op2_gmp);
	mpz_init(mod_gmp);
	mpz_init(mod_prime_gmp);
	mpz_init(res_gmp);
	mpz_init(base_gmp);
	mpz_init(R_gmp);
	mpz_init(invR_gmp);

	mpz_ui_pow_ui(base_gmp, 2, LIMB_SIZE_IN_BITS);
	mpz_ui_pow_ui(R_gmp, 2, LIMB_SIZE_IN_BITS * NUM_LIMBS);

	uint64_t op1[NUM_LIMBS];
	uint64_t op2[NUM_LIMBS];
	uint64_t mod[NUM_LIMBS];
	uint64_t mod_prime;
	uint64_t res[NUM_LIMBS];

	bool success = true;

	for (unsigned int i = 0; (i < number_of_tests) && success; i++) {
		three_sorted_gmp operands;

		bool operands_ok;
		do {
			operands = get_three_sorted_gmp(PRIME_FIELD_BINARY_BIT_LENGTH, gmp_random_state);
			mpz_set(op1_gmp, operands.small);
			mpz_set(op2_gmp, operands.middle);
			mpz_set(mod_gmp, operands.big);

			operands_ok = true;

			int inverse_exists = mpz_invert(mod_prime_gmp, mod_gmp, base_gmp);

			if (!inverse_exists) {
				operands_ok = false;
				clear_three_sorted_gmp(operands);
			}
		} while (!operands_ok);

		mpz_neg(mod_prime_gmp, mod_prime_gmp);
		mpz_mod(mod_prime_gmp, mod_prime_gmp, base_gmp);
		mpz_invert(invR_gmp, R_gmp, mod_gmp);

		clear_num(op1, NUM_LIMBS);
		clear_num(op2, NUM_LIMBS);
		clear_num(mod, NUM_LIMBS);
		mod_prime = 0;
		clear_num(res, NUM_LIMBS);

		convert_gmp_to_num(op1, op1_gmp, NUM_LIMBS);
		convert_gmp_to_num(op2, op2_gmp, NUM_LIMBS);
		convert_gmp_to_num(mod, mod_gmp, NUM_LIMBS);
		convert_gmp_to_num(&mod_prime, mod_prime_gmp, 1);

		// montgomery multiplication
		mpz_mul(res_gmp, op1_gmp, op2_gmp);
		mpz_mul(res_gmp, res_gmp, invR_gmp);
		mpz_mod(res_gmp, res_gmp, mod_gmp);
		mul_montgomery(res, op1, op2, mod, mod_prime, NUM_LIMBS);

		if (!is_equal_num_gmp(res, res_gmp, NUM_LIMBS)) {
			print_num_gmp(op1_gmp, NUM_LIMBS);
			print_num(op1, NUM_LIMBS);
			print_num_gmp(op2_gmp, NUM_LIMBS);
			print_num(op2, NUM_LIMBS);
			print_num_gmp(mod_gmp, NUM_LIMBS);
			print_num(mod, NUM_LIMBS);
			print_num_gmp(res_gmp, NUM_LIMBS);
			print_num(res, NUM_LIMBS);
			success = false;
		}

		clear_three_sorted_gmp(operands);
	}

	mpz_clear(op1_gmp);
	mpz_clear(op2_gmp);
	mpz_clear(mod_gmp);
	mpz_clear(mod_prime_gmp);
	mpz_clear(res_gmp);
	mpz_clear(base_gmp);
	mpz_clear(R_gmp);
	mpz_clear(invR_gmp);
	gmp_randclear(gmp_random_state);

	return success;
}

void check_add() {
	printf("Add:\n");
	if (test_add(NUM_ITERATIONS, SEED)) {
		printf("Success\n");
	} else {
		printf("Failed\n");
	}
	printf("\n");
}

void check_add_num_64() {
	printf("add_num_64:\n");
	if (test_add_num_64(NUM_ITERATIONS, SEED)) {
		printf("Success\n");
	} else {
		printf("Failed\n");
	}
	printf("\n");
}

void check_sub() {
	printf("Sub:\n");
	if (test_sub(NUM_ITERATIONS, SEED)) {
		printf("Success\n");
	} else {
		printf("Failed\n");
	}
	printf("\n");
}

void check_mul64_to_128() {
	printf("mul64_to_128:\n");
	if (test_mul64_to_128(NUM_ITERATIONS, SEED)) {
		printf("Success\n");
	} else {
		printf("Failed\n");
	}
	printf("\n");
}

void check_mul_num_64() {
	printf("mul_num_64:\n");
	if (test_mul_num_64(NUM_ITERATIONS, SEED)) {
		printf("Success\n");
	} else {
		printf("Failed\n");
	}
	printf("\n");
}

void check_mul() {
	printf("Mul:\n");
	if (test_mul(NUM_ITERATIONS, SEED)) {
		printf("Success\n");
	} else {
		printf("Failed\n");
	}
	printf("\n");
}

void check_cmp() {
	printf("cmp:\n");
	if (test_cmp(NUM_ITERATIONS, SEED)) {
		printf("Success\n");
	} else {
		printf("Failed\n");
	}
	printf("\n");
}

void check_add_mod() {
	printf("Add Mod:\n");
	if (test_add_mod(NUM_ITERATIONS, SEED)) {
		printf("Success\n");
	} else {
		printf("Failed\n");
	}
	printf("\n");
}

void check_sub_mod() {
	printf("Sub Mod:\n");
	if (test_sub_mod(NUM_ITERATIONS, SEED)) {
		printf("Success\n");
	} else {
		printf("Failed\n");
	}
	printf("\n");
}

void check_mul_montgomery() {
	printf("Mul Montgomery:\n");
	if (test_mul_montgomery(NUM_ITERATIONS, SEED)) {
		printf("Success\n");
	} else {
		printf("Failed\n");
	}
	printf("\n");
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

bool test_add_vector(unsigned int number_of_tests, unsigned int seed) {
	gmp_randstate_t gmp_random_state;
	gmp_randinit_default(gmp_random_state);
	gmp_randseed_ui(gmp_random_state, seed);

	unsigned int const num_operands = 4;
	mpz_t op1_gmp[num_operands];
	mpz_t op2_gmp[num_operands];
	mpz_t res_gmp[num_operands];
	mpz_t mod_gmp[num_operands];
	for (unsigned int i = 0; i < num_operands; i++) {
		mpz_init(op1_gmp[i]);
		mpz_init(op2_gmp[i]);
		mpz_init(res_gmp[i]);
		mpz_init(mod_gmp[i]);
	}

	uint64_t op1[NUM_LIMBS];
	uint64_t op2[NUM_LIMBS];
	uint64_t res[NUM_LIMBS];

	bool success = true;

	for (unsigned int i = 0; (i < number_of_tests) && success; i++) {
		for (unsigned int j = 0; j < num_operands; j++) {

		}
		three_sorted_gmp operands = get_three_sorted_gmp(PRIME_FIELD_BINARY_BIT_LENGTH, gmp_random_state);
		mpz_set(op1_gmp, operands.small);
		mpz_set(op2_gmp, operands.middle);
		mpz_set(mod_gmp, operands.big);

		clear_num(op1, NUM_LIMBS);
		clear_num(op2, NUM_LIMBS);
		clear_num(res, NUM_LIMBS);

		convert_gmp_to_num(op1, op1_gmp, NUM_LIMBS);
		convert_gmp_to_num(op2, op2_gmp, NUM_LIMBS);

		mpz_add(res_gmp, op1_gmp, op2_gmp);
		add(res, op1, op2, NUM_LIMBS, 0);

		if (!is_equal_num_gmp(res, res_gmp, NUM_LIMBS)) {
			print_num_gmp(op1_gmp, NUM_LIMBS);
			print_num(op1, NUM_LIMBS);
			print_num_gmp(op2_gmp, NUM_LIMBS);
			print_num(op2, NUM_LIMBS);
			print_num_gmp(res_gmp, NUM_LIMBS);
			print_num(res, NUM_LIMBS);
			success = false;
		}

		clear_three_sorted_gmp(operands);
	}

	for (unsigned int i = 0; i < num_operands; i++) {
		mpz_clear(op1_gmp[i]);
		mpz_clear(op2_gmp[i]);
		mpz_clear(res_gmp[i]);
		mpz_clear(mod_gmp[i]);
	}
	gmp_randclear(gmp_random_state);

	return success;
}

void check_add_vector() {
	printf("Add Vector:\n");
	if (test_add_vector(NUM_ITERATIONS, SEED)) {
		printf("Success\n");
	} else {
		printf("Failed\n");
	}
	printf("\n");
}

int main(void) {
#ifdef VECTORIZED_CODE
	check_add_vector();
#else
	check_add();
	check_add_num_64();
	check_sub();
	check_mul64_to_128();
	check_mul_num_64();
	check_mul();
	check_cmp();
	check_add_mod();
	check_sub_mod();
	check_mul_montgomery();
#endif

	return EXIT_SUCCESS;
}

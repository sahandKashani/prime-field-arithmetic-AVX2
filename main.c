#include <assert.h>
#include <immintrin.h>
#include <inttypes.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <gmp.h>
#include "arithmetic.h"
#include "gmp_int.h"
#include "limb.h"
#include "utilities.h"
#include "constants.h"
#include "elliptic_curve.h"

#define NUM_ITERATIONS (1 << 10)
#define SEED (12345)

bool test_add_num_num(unsigned int number_of_tests, unsigned int seed) {
    gmp_randstate_t gmp_random_state;
    gmp_randinit_default(gmp_random_state);
    gmp_randseed_ui(gmp_random_state, seed);

    gmp_int_t op1_gmp;
    gmp_int_t op2_gmp;
    gmp_int_t res_gmp;
    gmp_int_t mod_gmp;
    gmp_int_init(op1_gmp);
    gmp_int_init(op2_gmp);
    gmp_int_init(res_gmp);
    gmp_int_init(mod_gmp);

    limb_t op1[NUM_LIMBS];
    limb_t op2[NUM_LIMBS];
    limb_t res[NUM_LIMBS];
    limb_t carry_in;

    bool success = true;

    for (unsigned int i = 0; (i < (number_of_tests / NUM_ENTRIES_IN_LIMB)) && success; i++) {
        three_sorted_gmp operands = get_three_sorted_gmp(PRIME_FIELD_BINARY_BIT_LENGTH, gmp_random_state);
        gmp_int_set(op1_gmp, operands.small);
        gmp_int_set(op2_gmp, operands.middle);
        gmp_int_set(mod_gmp, operands.big);

        zero_num(op1, NUM_LIMBS);
        zero_num(op2, NUM_LIMBS);
        zero_num(res, NUM_LIMBS);
        zero_num(&carry_in, 1);

        convert_gmp_to_num(op1, op1_gmp, NUM_LIMBS);
        convert_gmp_to_num(op2, op2_gmp, NUM_LIMBS);

        gmp_int_add(res_gmp, op1_gmp, op2_gmp);
        add_num_num(res, op1, op2, NUM_LIMBS, carry_in);

        if (!is_equal_num_gmp(res, res_gmp, NUM_LIMBS)) {
            print_num_gmp(op1_gmp, NUM_LIMBS);
            print_num(op1, NUM_LIMBS);
            print_num_gmp(op2_gmp, NUM_LIMBS);
            print_num(op2, NUM_LIMBS);
            print_num_gmp(res_gmp, NUM_LIMBS);
            print_num(res, NUM_LIMBS);
            success = false;

            add_num_num(res, op1, op2, NUM_LIMBS, carry_in);
        }

        clear_three_sorted_gmp(operands);
    }

    gmp_int_clear(op1_gmp);
    gmp_int_clear(op2_gmp);
    gmp_int_clear(res_gmp);
    gmp_int_clear(mod_gmp);
    gmp_randclear(gmp_random_state);

    return success;
}

bool test_add_num_limb(unsigned int number_of_tests, unsigned int seed) {
    gmp_randstate_t gmp_random_state;
    gmp_randinit_default(gmp_random_state);
    gmp_randseed_ui(gmp_random_state, seed);

    gmp_int_t op1_gmp;
    gmp_int_t op2_gmp;
    gmp_int_t res_gmp;
    gmp_int_t mod_gmp;
    gmp_int_init(op1_gmp);
    gmp_int_init(op2_gmp);
    gmp_int_init(res_gmp);
    gmp_int_init(mod_gmp);

    limb_t op1[NUM_LIMBS];
    limb_t op2;
    limb_t res[NUM_LIMBS];
    limb_t carry_in;

    bool success = true;

    for (unsigned int i = 0; (i < (number_of_tests / NUM_ENTRIES_IN_LIMB)) && success; i++) {
        three_sorted_gmp operands = get_three_sorted_gmp(PRIME_FIELD_BINARY_BIT_LENGTH, gmp_random_state);
        gmp_int_set(op1_gmp, operands.middle);
        gmp_int_set(mod_gmp, operands.big);

        generate_random_gmp_number(op2_gmp, BASE_EXPONENT, gmp_random_state);

        zero_num(op1, NUM_LIMBS);
        zero_num(&op2, 1);
        zero_num(res, NUM_LIMBS);
        zero_num(&carry_in, 1);

        convert_gmp_to_num(op1, op1_gmp, NUM_LIMBS);
        convert_gmp_to_num(&op2, op2_gmp, 1);

        gmp_int_add(res_gmp, op1_gmp, op2_gmp);
        add_num_limb(res, op1, op2, NUM_LIMBS, carry_in);

        if (!is_equal_num_gmp(res, res_gmp, NUM_LIMBS)) {
            print_num_gmp(op1_gmp, NUM_LIMBS);
            print_num(op1, NUM_LIMBS);
            print_num_gmp(op2_gmp, 1);
            print_num(&op2, 1);
            print_num_gmp(res_gmp, NUM_LIMBS);
            print_num(res, NUM_LIMBS);
            success = false;

            add_num_limb(res, op1, op2, NUM_LIMBS, carry_in);
        }

        clear_three_sorted_gmp(operands);
    }

    gmp_int_clear(op1_gmp);
    gmp_int_clear(op2_gmp);
    gmp_int_clear(res_gmp);
    gmp_int_clear(mod_gmp);
    gmp_randclear(gmp_random_state);

    return success;
}

bool test_sub_num_num(unsigned int number_of_tests, unsigned int seed) {
    gmp_randstate_t gmp_random_state;
    gmp_randinit_default(gmp_random_state);
    gmp_randseed_ui(gmp_random_state, seed);

    gmp_int_t op1_gmp;
    gmp_int_t op2_gmp;
    gmp_int_t res_gmp;
    gmp_int_t mod_gmp;
    gmp_int_init(op1_gmp);
    gmp_int_init(op2_gmp);
    gmp_int_init(res_gmp);
    gmp_int_init(mod_gmp);

    limb_t op1[NUM_LIMBS];
    limb_t op2[NUM_LIMBS];
    limb_t res[NUM_LIMBS];
    limb_t borrow_in;

    bool success = true;

    for (unsigned int i = 0; (i < (number_of_tests / NUM_ENTRIES_IN_LIMB)) && success; i++) {
        three_sorted_gmp operands = get_three_sorted_gmp(PRIME_FIELD_BINARY_BIT_LENGTH, gmp_random_state);
        /* op2 has to be smaller than op1 since this is normal subtraction (not modular) */
        gmp_int_set(op1_gmp, operands.middle);
        gmp_int_set(op2_gmp, operands.small);
        gmp_int_set(mod_gmp, operands.big);

        zero_num(op1, NUM_LIMBS);
        zero_num(op2, NUM_LIMBS);
        zero_num(res, NUM_LIMBS);
        zero_num(&borrow_in, 1);

        convert_gmp_to_num(op1, op1_gmp, NUM_LIMBS);
        convert_gmp_to_num(op2, op2_gmp, NUM_LIMBS);

        gmp_int_sub(res_gmp, op1_gmp, op2_gmp);
        sub_num_num(res, op1, op2, NUM_LIMBS, borrow_in);

        if (!is_equal_num_gmp(res, res_gmp, NUM_LIMBS)) {
            print_num_gmp(op1_gmp, NUM_LIMBS);
            print_num(op1, NUM_LIMBS);
            print_num_gmp(op2_gmp, NUM_LIMBS);
            print_num(op2, NUM_LIMBS);
            print_num_gmp(res_gmp, NUM_LIMBS);
            print_num(res, NUM_LIMBS);
            success = false;

            sub_num_num(res, op1, op2, NUM_LIMBS, borrow_in);
        }

        clear_three_sorted_gmp(operands);
    }

    gmp_int_clear(op1_gmp);
    gmp_int_clear(op2_gmp);
    gmp_int_clear(res_gmp);
    gmp_int_clear(mod_gmp);
    gmp_randclear(gmp_random_state);

    return success;
}

bool test_mul_limb_limb(unsigned int number_of_tests, unsigned int seed) {
    gmp_randstate_t gmp_random_state;
    gmp_randinit_default(gmp_random_state);
    gmp_randseed_ui(gmp_random_state, seed);

    gmp_int_t op1_gmp;
    gmp_int_t op2_gmp;
    gmp_int_t res_gmp;
    gmp_int_init(op1_gmp);
    gmp_int_init(op2_gmp);
    gmp_int_init(res_gmp);

    limb_t op1;
    limb_t op2;
    limb_t res[2];

    bool success = true;

    for (unsigned int i = 0; (i < (number_of_tests / NUM_ENTRIES_IN_LIMB)) && success; i++) {
        generate_random_gmp_number(op1_gmp, BASE_EXPONENT, gmp_random_state);
        generate_random_gmp_number(op2_gmp, BASE_EXPONENT, gmp_random_state);

        zero_num(&op1, 1);
        zero_num(&op2, 1);
        zero_num(res, 2);

        convert_gmp_to_num(&op1, op1_gmp, 1);
        convert_gmp_to_num(&op2, op2_gmp, 1);

        gmp_int_mul(res_gmp, op1_gmp, op2_gmp);
        struct d_limb_t tmp = mul_limb_limb(op1, op2);

        #if !FULL_LIMB_PRECISION

            tmp = reduce_to_base_d_limb_t(tmp);

        #endif

        res[1] = tmp.hi;
        res[0] = tmp.lo;

        if (!is_equal_num_gmp(res, res_gmp, 2)) {
            print_num_gmp(op1_gmp, 1);
            print_num(&op1, 1);
            print_num_gmp(op2_gmp, 1);
            print_num(&op2, 1);
            print_num_gmp(res_gmp, 2);
            print_num(res, 2);
            success = false;

            mul_limb_limb(op1, op2);
        }
    }

    gmp_int_clear(op1_gmp);
    gmp_int_clear(op2_gmp);
    gmp_int_clear(res_gmp);
    gmp_randclear(gmp_random_state);

    return success;
}

bool test_mul_num_limb(unsigned int number_of_tests, unsigned int seed) {
    gmp_randstate_t gmp_random_state;
    gmp_randinit_default(gmp_random_state);
    gmp_randseed_ui(gmp_random_state, seed);

    gmp_int_t op1_gmp;
    gmp_int_t op2_gmp;
    gmp_int_t res_gmp;
    gmp_int_t mod_gmp;
    gmp_int_init(op1_gmp);
    gmp_int_init(op2_gmp);
    gmp_int_init(res_gmp);
    gmp_int_init(mod_gmp);

    limb_t op1[NUM_LIMBS];
    limb_t op2;
    limb_t res[NUM_LIMBS + 1];

    bool success = true;

    for (unsigned int i = 0; (i < (number_of_tests / NUM_ENTRIES_IN_LIMB)) && success; i++) {
        three_sorted_gmp operands = get_three_sorted_gmp(PRIME_FIELD_BINARY_BIT_LENGTH, gmp_random_state);
        gmp_int_set(op1_gmp, operands.middle);
        gmp_int_set(mod_gmp, operands.big);

        generate_random_gmp_number(op2_gmp, BASE_EXPONENT, gmp_random_state);

        zero_num(op1, NUM_LIMBS);
        zero_num(&op2, 1);
        zero_num(res, NUM_LIMBS);

        convert_gmp_to_num(op1, op1_gmp, NUM_LIMBS);
        convert_gmp_to_num(&op2, op2_gmp, 1);

        gmp_int_mul(res_gmp, op1_gmp, op2_gmp);
        mul_num_limb(res, op1, op2, NUM_LIMBS);

        if (!is_equal_num_gmp(res, res_gmp, NUM_LIMBS + 1)) {
            print_num_gmp(op1_gmp, NUM_LIMBS);
            print_num(op1, NUM_LIMBS);
            print_num_gmp(op2_gmp, 1);
            print_num(&op2, 1);
            print_num_gmp(res_gmp, NUM_LIMBS + 1);
            print_num(res, NUM_LIMBS + 1);
            success = false;

            mul_num_limb(res, op1, op2, NUM_LIMBS);
        }

        clear_three_sorted_gmp(operands);
    }

    gmp_int_clear(op1_gmp);
    gmp_int_clear(op2_gmp);
    gmp_int_clear(res_gmp);
    gmp_int_clear(mod_gmp);
    gmp_randclear(gmp_random_state);

    return success;
}

bool test_mul_num_num(unsigned int number_of_tests, unsigned int seed) {
    gmp_randstate_t gmp_random_state;
    gmp_randinit_default(gmp_random_state);
    gmp_randseed_ui(gmp_random_state, seed);

    gmp_int_t op1_gmp;
    gmp_int_t op2_gmp;
    gmp_int_t res_gmp;
    gmp_int_t mod_gmp;
    gmp_int_init(op1_gmp);
    gmp_int_init(op2_gmp);
    gmp_int_init(res_gmp);
    gmp_int_init(mod_gmp);

    limb_t op1[NUM_LIMBS];
    limb_t op2[NUM_LIMBS];
    limb_t res[2 * NUM_LIMBS];

    bool success = true;

    for (unsigned int i = 0; (i < (number_of_tests / NUM_ENTRIES_IN_LIMB)) && success; i++) {
        three_sorted_gmp operands = get_three_sorted_gmp(PRIME_FIELD_BINARY_BIT_LENGTH, gmp_random_state);
        gmp_int_set(op1_gmp, operands.small);
        gmp_int_set(op2_gmp, operands.middle);
        gmp_int_set(mod_gmp, operands.big);

        zero_num(op1, NUM_LIMBS);
        zero_num(op2, NUM_LIMBS);
        zero_num(res, 2 * NUM_LIMBS);

        convert_gmp_to_num(op1, op1_gmp, NUM_LIMBS);
        convert_gmp_to_num(op2, op2_gmp, NUM_LIMBS);

        gmp_int_mul(res_gmp, op1_gmp, op2_gmp);
        mul_num_num(res, op1, op2, NUM_LIMBS);

        if (!is_equal_num_gmp(res, res_gmp, 2 * NUM_LIMBS)) {
            print_num_gmp(op1_gmp, NUM_LIMBS);
            print_num(op1, NUM_LIMBS);
            print_num_gmp(op2_gmp, NUM_LIMBS);
            print_num(op2, NUM_LIMBS);
            print_num_gmp(res_gmp, 2 * NUM_LIMBS);
            print_num(res, 2 * NUM_LIMBS);
            success = false;

            mul_num_num(res, op1, op2, NUM_LIMBS);
        }

        clear_three_sorted_gmp(operands);
    }

    gmp_int_clear(op1_gmp);
    gmp_int_clear(op2_gmp);
    gmp_int_clear(res_gmp);
    gmp_int_clear(mod_gmp);
    gmp_randclear(gmp_random_state);

    return success;
}

bool test_add_mod_num_num(unsigned int number_of_tests, unsigned int seed) {
    gmp_randstate_t gmp_random_state;
    gmp_randinit_default(gmp_random_state);
    gmp_randseed_ui(gmp_random_state, seed);

    gmp_int_t op1_gmp;
    gmp_int_t op2_gmp;
    gmp_int_t mod_gmp;
    gmp_int_t res_gmp;
    gmp_int_init(op1_gmp);
    gmp_int_init(op2_gmp);
    gmp_int_init(mod_gmp);
    gmp_int_init(res_gmp);

    limb_t op1[NUM_LIMBS];
    limb_t op2[NUM_LIMBS];
    limb_t mod[NUM_LIMBS];
    limb_t res[NUM_LIMBS];

    bool success = true;

    for (unsigned int i = 0; (i < (number_of_tests / NUM_ENTRIES_IN_LIMB)) && success; i++) {
        three_sorted_gmp operands = get_three_sorted_gmp(PRIME_FIELD_BINARY_BIT_LENGTH, gmp_random_state);
        gmp_int_set(op1_gmp, operands.small);
        gmp_int_set(op2_gmp, operands.middle);
        gmp_int_set(mod_gmp, operands.big);

        zero_num(op1, NUM_LIMBS);
        zero_num(op2, NUM_LIMBS);
        zero_num(mod, NUM_LIMBS);
        zero_num(res, NUM_LIMBS);

        convert_gmp_to_num(op1, op1_gmp, NUM_LIMBS);
        convert_gmp_to_num(op2, op2_gmp, NUM_LIMBS);
        convert_gmp_to_num(mod, mod_gmp, NUM_LIMBS);

        gmp_int_add_mod(res_gmp, op1_gmp, op2_gmp, mod_gmp);
        add_mod_num_num(res, op1, op2, mod, NUM_LIMBS);

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

            add_mod_num_num(res, op1, op2, mod, NUM_LIMBS);
        }

        clear_three_sorted_gmp(operands);
    }

    gmp_int_clear(op1_gmp);
    gmp_int_clear(op2_gmp);
    gmp_int_clear(mod_gmp);
    gmp_int_clear(res_gmp);
    gmp_randclear(gmp_random_state);

    return success;
}

bool test_sub_mod_num_num(unsigned int number_of_tests, unsigned int seed) {
    gmp_randstate_t gmp_random_state;
    gmp_randinit_default(gmp_random_state);
    gmp_randseed_ui(gmp_random_state, seed);

    gmp_int_t op1_gmp;
    gmp_int_t op2_gmp;
    gmp_int_t mod_gmp;
    gmp_int_t res_gmp;
    gmp_int_init(op1_gmp);
    gmp_int_init(op2_gmp);
    gmp_int_init(mod_gmp);
    gmp_int_init(res_gmp);

    limb_t op1[NUM_LIMBS];
    limb_t op2[NUM_LIMBS];
    limb_t mod[NUM_LIMBS];
    limb_t res[NUM_LIMBS];

    bool success = true;

    for (unsigned int i = 0; (i < (number_of_tests / NUM_ENTRIES_IN_LIMB)) && success; i++) {
        three_sorted_gmp operands = get_three_sorted_gmp(PRIME_FIELD_BINARY_BIT_LENGTH, gmp_random_state);
        gmp_int_set(op1_gmp, operands.small);
        gmp_int_set(op2_gmp, operands.middle);
        gmp_int_set(mod_gmp, operands.big);

        zero_num(op1, NUM_LIMBS);
        zero_num(op2, NUM_LIMBS);
        zero_num(mod, NUM_LIMBS);
        zero_num(res, NUM_LIMBS);

        convert_gmp_to_num(op1, op1_gmp, NUM_LIMBS);
        convert_gmp_to_num(op2, op2_gmp, NUM_LIMBS);
        convert_gmp_to_num(mod, mod_gmp, NUM_LIMBS);

        gmp_int_sub_mod(res_gmp, op1_gmp, op2_gmp, mod_gmp);
        sub_mod_num_num(res, op1, op2, mod, NUM_LIMBS);

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

            sub_mod_num_num(res, op1, op2, mod, NUM_LIMBS);
        }

        clear_three_sorted_gmp(operands);
    }

    gmp_int_clear(op1_gmp);
    gmp_int_clear(op2_gmp);
    gmp_int_clear(mod_gmp);
    gmp_int_clear(res_gmp);
    gmp_randclear(gmp_random_state);

    return success;
}

bool test_mul_montgomery_num_num(unsigned int number_of_tests, unsigned int seed) {
    gmp_randstate_t gmp_random_state;
    gmp_randinit_default(gmp_random_state);
    gmp_randseed_ui(gmp_random_state, seed);

    gmp_int_t op1_gmp;
    gmp_int_t op2_gmp;
    gmp_int_t mod_gmp;
    gmp_int_t mod_prime_gmp;
    gmp_int_t res_gmp;
    gmp_int_t base_gmp;
    gmp_int_t R_gmp;
    gmp_int_t invR_gmp;
    gmp_int_init(op1_gmp);
    gmp_int_init(op2_gmp);
    gmp_int_init(mod_gmp);
    gmp_int_init(mod_prime_gmp);
    gmp_int_init(res_gmp);
    gmp_int_init(base_gmp);
    gmp_int_init(R_gmp);
    gmp_int_init(invR_gmp);

    gmp_int_ui_pow_ui(base_gmp, 2, BASE_EXPONENT);
    gmp_int_ui_pow_ui(R_gmp, 2, BASE_EXPONENT * NUM_LIMBS);

    limb_t op1[NUM_LIMBS];
    limb_t op2[NUM_LIMBS];
    limb_t mod[NUM_LIMBS];
    limb_t mod_prime;
    limb_t res[NUM_LIMBS];

    bool success = true;

    for (unsigned int i = 0; (i < (number_of_tests / NUM_ENTRIES_IN_LIMB)) && success; i++) {
        three_sorted_gmp operands;

        bool operands_ok;
        do {
            operands = get_three_sorted_gmp(PRIME_FIELD_BINARY_BIT_LENGTH, gmp_random_state);
            gmp_int_set(op1_gmp, operands.small);
            gmp_int_set(op2_gmp, operands.middle);
            gmp_int_set(mod_gmp, operands.big);

            operands_ok = true;

            int inverse_exists[NUM_ENTRIES_IN_LIMB];
            gmp_int_invert(inverse_exists, mod_prime_gmp, mod_gmp, base_gmp);
            bool inverse_exists_common = true;

            for (unsigned int j = 0; j < NUM_ENTRIES_IN_LIMB; j++) {
                if (!inverse_exists[j]) {
                    inverse_exists_common = false;
                }
            }

            if (!inverse_exists_common) {
                operands_ok = false;
                clear_three_sorted_gmp(operands);
            }
        } while (!operands_ok);

        gmp_int_neg(mod_prime_gmp, mod_prime_gmp);
        gmp_int_mod(mod_prime_gmp, mod_prime_gmp, base_gmp);
        gmp_int_invert(NULL, invR_gmp, R_gmp, mod_gmp);

        zero_num(op1, NUM_LIMBS);
        zero_num(op2, NUM_LIMBS);
        zero_num(mod, NUM_LIMBS);
        zero_num(&mod_prime, 1);
        zero_num(res, NUM_LIMBS);

        convert_gmp_to_num(op1, op1_gmp, NUM_LIMBS);
        convert_gmp_to_num(op2, op2_gmp, NUM_LIMBS);
        convert_gmp_to_num(mod, mod_gmp, NUM_LIMBS);
        convert_gmp_to_num(&mod_prime, mod_prime_gmp, 1);

        gmp_int_mul(res_gmp, op1_gmp, op2_gmp);
        gmp_int_mul(res_gmp, res_gmp, invR_gmp);
        gmp_int_mod(res_gmp, res_gmp, mod_gmp);
        mul_montgomery_num_num(res, op1, op2, mod, mod_prime, NUM_LIMBS);

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

            mul_montgomery_num_num(res, op1, op2, mod, mod_prime, NUM_LIMBS);
        }

        clear_three_sorted_gmp(operands);
    }

    gmp_int_clear(op1_gmp);
    gmp_int_clear(op2_gmp);
    gmp_int_clear(mod_gmp);
    gmp_int_clear(mod_prime_gmp);
    gmp_int_clear(res_gmp);
    gmp_int_clear(base_gmp);
    gmp_int_clear(R_gmp);
    gmp_int_clear(invR_gmp);
    gmp_randclear(gmp_random_state);

    return success;
}

void check_add_num_num() {
    printf("Add:\n");
    if (test_add_num_num(NUM_ITERATIONS, SEED)) {
        printf("Success\n");
    } else {
        printf("Failed\n");
    }
    printf("\n");
}

void check_add_num_limb() {
    printf("add_num_limb:\n");
    if (test_add_num_limb(NUM_ITERATIONS, SEED)) {
        printf("Success\n");
    } else {
        printf("Failed\n");
    }
    printf("\n");
}

void check_sub_num_num() {
    printf("Sub:\n");
    if (test_sub_num_num(NUM_ITERATIONS, SEED)) {
        printf("Success\n");
    } else {
        printf("Failed\n");
    }
    printf("\n");
}

void check_mul_limb_limb() {
    printf("mul_limb_limb:\n");
    if (test_mul_limb_limb(NUM_ITERATIONS, SEED)) {
        printf("Success\n");
    } else {
        printf("Failed\n");
    }
    printf("\n");
}

void check_mul_num_limb() {
    printf("mul_num_limb:\n");
    if (test_mul_num_limb(NUM_ITERATIONS, SEED)) {
        printf("Success\n");
    } else {
        printf("Failed\n");
    }
    printf("\n");
}

void check_mul_num_num() {
    printf("Mul:\n");
    if (test_mul_num_num(NUM_ITERATIONS, SEED)) {
        printf("Success\n");
    } else {
        printf("Failed\n");
    }
    printf("\n");
}

void check_add_mod_num_num() {
    printf("Add Mod:\n");
    if (test_add_mod_num_num(NUM_ITERATIONS, SEED)) {
        printf("Success\n");
    } else {
        printf("Failed\n");
    }
    printf("\n");
}

void check_sub_mod_num_num() {
    printf("Sub Mod:\n");
    if (test_sub_mod_num_num(NUM_ITERATIONS, SEED)) {
        printf("Success\n");
    } else {
        printf("Failed\n");
    }
    printf("\n");
}

void check_mul_montgomery_num_num() {
    printf("Mul Montgomery:\n");
    if (test_mul_montgomery_num_num(NUM_ITERATIONS, SEED)) {
        printf("Success\n");
    } else {
        printf("Failed\n");
    }
    printf("\n");
}

int main(void) {
    #if TEST

        check_add_num_num();
        check_add_num_limb();
        check_sub_num_num();
        check_mul_limb_limb();
        check_mul_num_limb();
        check_mul_num_num();
        check_add_mod_num_num();
        check_sub_mod_num_num();
        check_mul_montgomery_num_num();

    #else /* TEST */

        #if PRIME_FIELD_BINARY_BIT_LENGTH == 131

            #if SIMD_PARALLEL_WALKS

            #else /* SIMD_PARALLEL_WALKS */

                #if LIMB_SIZE_IN_BITS == 32

                    /* from certicom document */
                    limb_t m[NUM_LIMBS] = {0x6b3abc0b, 0x194c4318, 0x93469e33, 0x8e1d43f2, 0x00000004};
                    limb_t m_prime;

                    gmp_int_t m_gmp;
                    gmp_int_t m_prime_gmp;
                    gmp_int_t base_gmp;

                    gmp_int_init(m_gmp);
                    gmp_int_init(m_prime_gmp);
                    gmp_int_init(base_gmp);

                    convert_num_to_gmp(m_gmp, m, NUM_LIMBS);

                    gmp_int_ui_pow_ui(base_gmp, 2, BASE_EXPONENT);
                    int inverse_exists;
                    gmp_int_invert(&inverse_exists, m_prime_gmp, m_gmp, base_gmp);
                    assert(inverse_exists);
                    gmp_int_neg(m_prime_gmp, m_prime_gmp);
                    gmp_int_mod(m_prime_gmp, m_prime_gmp, base_gmp);

                    convert_gmp_to_num(&m_prime, m_prime_gmp, 1);

                    struct curve_point p1 = {
                        .x = {0xee8140ee, 0xe0296c61, 0x2b9a812f, 0x9f6d21d3, 0x00000001},
                        .y = {0x96515a03, 0xf776b144, 0x32833a4e, 0xbe0e4b9e, 0x00000001}
                    };

                    struct curve_point p2 = {
                        .x = {0xf4b4bff2, 0x7e0b46a5, 0xb394666d, 0x96c93d34, 0x00000000},
                        .y = {0xa06b2e3b, 0x8bce38bf, 0x1653efa8, 0x93a86761, 0x00000000}
                    };

                    printf("original\n");
                    printf("p1.x = ");
                    print_num(p1.x, NUM_LIMBS);
                    printf("p1.y = ");
                    print_num(p1.y, NUM_LIMBS);
                    printf("p2.x = ");
                    print_num(p2.x, NUM_LIMBS);
                    printf("p2.y = ");
                    print_num(p2.y, NUM_LIMBS);

                    /* convert to montgomery representation */
                    limb_t one[NUM_LIMBS];
                    set_num(one, 1, NUM_LIMBS);
                    mul_montgomery_num_num(p1.x, p1.x, one, m, m_prime, NUM_LIMBS);
                    mul_montgomery_num_num(p1.y, p1.y, one, m, m_prime, NUM_LIMBS);
                    mul_montgomery_num_num(p2.x, p2.x, one, m, m_prime, NUM_LIMBS);
                    mul_montgomery_num_num(p2.y, p2.y, one, m, m_prime, NUM_LIMBS);

                    printf("\n");

                    printf("montgomery representation\n");
                    printf("p1.x = ");
                    print_num(p1.x, NUM_LIMBS);
                    printf("p1.y = ");
                    print_num(p1.y, NUM_LIMBS);
                    printf("p2.x = ");
                    print_num(p2.x, NUM_LIMBS);
                    printf("p2.y = ");
                    print_num(p2.y, NUM_LIMBS);

                    printf("\n");

                    struct curve_point p3 = add_point_point(p1, p2, m, m_prime);

                    print_num(p3.x, NUM_LIMBS);
                    print_num(p3.y, NUM_LIMBS);

                #elif LIMB_SIZE_IN_BITS == 64

                #endif /* LIMB_SIZE_IN_BITS */

            #endif /* SIMD_PARALLEL_WALKS */

        #endif /* PRIME_FIELD_BINARY_BIT_LENGTH */

    #endif /* TEST */

    return EXIT_SUCCESS;
}

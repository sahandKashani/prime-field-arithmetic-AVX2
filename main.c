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
#include "compile_time_checks.h"
#include "gmp_int.h"
#include "limb.h"
#include "utilities.h"
#include "constants.h"
#include "elliptic_curve.h"
#include "prime_field.h"

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
        generate_random_gmp_number(mod_gmp, PRIME_FIELD_BINARY_BIT_LENGTH, gmp_random_state);

        three_sorted_gmp operands = get_three_sorted_gmp_with_inverse(PRIME_FIELD_BINARY_BIT_LENGTH, gmp_random_state, mod_gmp);

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

bool test_point_addition() {
    bool success = true;

    for (unsigned int i = 0; (i < (NUM_POINTS / NUM_ENTRIES_IN_LIMB)) && success; i += 2) {
        struct curve_point p1;
        struct curve_point_gmp p1_gmp;
        curve_point_init_gmp(&p1_gmp);

        struct curve_point p2;
        struct curve_point_gmp p2_gmp;
        curve_point_init_gmp(&p2_gmp);

        struct curve_point p3;
        struct curve_point_gmp p3_gmp;
        curve_point_init_gmp(&p3_gmp);

        /* set p1 */
        gmp_int_set(p1_gmp.x, points_x_glo_gmp[i]);
        gmp_int_set(p1_gmp.y, points_y_glo_gmp[i]);
        copy_num(p1.x, points_x_glo[i], NUM_LIMBS);
        copy_num(p1.y, points_y_glo[i], NUM_LIMBS);

        /* set p2 */
        gmp_int_set(p2_gmp.x, points_x_glo_gmp[i+1]);
        gmp_int_set(p2_gmp.y, points_y_glo_gmp[i+1]);
        copy_num(p2.x, points_x_glo[i+1], NUM_LIMBS);
        copy_num(p2.y, points_y_glo[i+1], NUM_LIMBS);

        /* to montgomery representation */
        standard_to_montgomery_representation_point_gmp(&p1_gmp);
        standard_to_montgomery_representation_point_gmp(&p2_gmp);
        standard_to_montgomery_representation_point(&p1);
        standard_to_montgomery_representation_point(&p2);

        /* point addition */
        add_point_point_gmp(&p3_gmp, &p1_gmp, &p2_gmp);
        add_point_point(&p3, &p1, &p2, NUM_LIMBS);

        montgomery_to_standard_representation_point(&p1);
        montgomery_to_standard_representation_point_gmp(&p1_gmp);
        montgomery_to_standard_representation_point(&p2);
        montgomery_to_standard_representation_point_gmp(&p2_gmp);
        montgomery_to_standard_representation_point(&p3);
        montgomery_to_standard_representation_point_gmp(&p3_gmp);

        bool on_curve = is_on_curve_point(p3, NUM_LIMBS);
        bool on_curve_gmp = is_on_curve_point_gmp(p3_gmp);
        if (!(on_curve && on_curve_gmp)) {
            print_num(p1.x, NUM_LIMBS);
            print_num(p1.y, NUM_LIMBS);
            print_num(p2.x, NUM_LIMBS);
            print_num(p2.y, NUM_LIMBS);
            print_num(p3.x, NUM_LIMBS);
            print_num(p3.y, NUM_LIMBS);
            print_num_gmp(p1_gmp.x, NUM_LIMBS);
            print_num_gmp(p1_gmp.y, NUM_LIMBS);
            print_num_gmp(p2_gmp.x, NUM_LIMBS);
            print_num_gmp(p2_gmp.y, NUM_LIMBS);
            print_num_gmp(p3_gmp.x, NUM_LIMBS);
            print_num_gmp(p3_gmp.y, NUM_LIMBS);
            success = false;
        }

        curve_point_clear_gmp(&p1_gmp);
        curve_point_clear_gmp(&p2_gmp);
        curve_point_clear_gmp(&p3_gmp);
    }

    return success;
}

bool test_point_double() {
    bool success = true;

    for (unsigned int i = 0; (i < (NUM_POINTS / NUM_ENTRIES_IN_LIMB)) && success; i += 1) {
        struct curve_point p1;
        struct curve_point_gmp p1_gmp;
        curve_point_init_gmp(&p1_gmp);

        struct curve_point p2;
        struct curve_point_gmp p2_gmp;
        curve_point_init_gmp(&p2_gmp);

        /* set p1 */
        gmp_int_set(p1_gmp.x, points_x_glo_gmp[i]);
        gmp_int_set(p1_gmp.y, points_y_glo_gmp[i]);
        copy_num(p1.x, points_x_glo[i], NUM_LIMBS);
        copy_num(p1.y, points_y_glo[i], NUM_LIMBS);

        /* to montgomery representation */
        standard_to_montgomery_representation_point_gmp(&p1_gmp);
        standard_to_montgomery_representation_point(&p1);

        /* point double */
        double_point_gmp(&p2_gmp, &p1_gmp);
        double_point(&p2, &p1, NUM_LIMBS);

        montgomery_to_standard_representation_point(&p1);
        montgomery_to_standard_representation_point_gmp(&p1_gmp);
        montgomery_to_standard_representation_point(&p2);
        montgomery_to_standard_representation_point_gmp(&p2_gmp);

        bool on_curve = is_on_curve_point(p2, NUM_LIMBS);
        bool on_curve_gmp = is_on_curve_point_gmp(p2_gmp);
        if (!(on_curve && on_curve_gmp)) {
            printf("on_curve = %d\n", on_curve);
            printf("on_curve_gmp = %d\n", on_curve_gmp);
            print_num(p1.x, NUM_LIMBS);
            print_num(p1.y, NUM_LIMBS);
            print_num(p2.x, NUM_LIMBS);
            print_num(p2.y, NUM_LIMBS);
            print_num_gmp(p1_gmp.x, NUM_LIMBS);
            print_num_gmp(p1_gmp.y, NUM_LIMBS);
            print_num_gmp(p2_gmp.x, NUM_LIMBS);
            print_num_gmp(p2_gmp.y, NUM_LIMBS);
            success = false;
        }

        curve_point_clear_gmp(&p1_gmp);
        curve_point_clear_gmp(&p2_gmp);
    }

    return success;
}

bool test_point_neg() {
    bool success = true;

    for (unsigned int i = 0; (i < (NUM_POINTS / NUM_ENTRIES_IN_LIMB)) && success; i += 1) {
        struct curve_point p1;
        struct curve_point_gmp p1_gmp;
        curve_point_init_gmp(&p1_gmp);

        struct curve_point p2;
        struct curve_point_gmp p2_gmp;
        curve_point_init_gmp(&p2_gmp);

        /* set p1 */
        gmp_int_set(p1_gmp.x, points_x_glo_gmp[i]);
        gmp_int_set(p1_gmp.y, points_y_glo_gmp[i]);
        copy_num(p1.x, points_x_glo[i], NUM_LIMBS);
        copy_num(p1.y, points_y_glo[i], NUM_LIMBS);

        /* to montgomery representation */
        standard_to_montgomery_representation_point_gmp(&p1_gmp);
        standard_to_montgomery_representation_point(&p1);

        /* point neg */
        neg_point_gmp(&p2_gmp, &p1_gmp);
        neg_point(&p2, &p1, NUM_LIMBS);

        montgomery_to_standard_representation_point(&p1);
        montgomery_to_standard_representation_point_gmp(&p1_gmp);
        montgomery_to_standard_representation_point(&p2);
        montgomery_to_standard_representation_point_gmp(&p2_gmp);

        bool on_curve = is_on_curve_point(p2, NUM_LIMBS);
        bool on_curve_gmp = is_on_curve_point_gmp(p2_gmp);
        if (!(on_curve && on_curve_gmp)) {
            print_num(p1.x, NUM_LIMBS);
            print_num(p1.y, NUM_LIMBS);
            print_num(p2.x, NUM_LIMBS);
            print_num(p2.y, NUM_LIMBS);
            print_num_gmp(p1_gmp.x, NUM_LIMBS);
            print_num_gmp(p1_gmp.y, NUM_LIMBS);
            print_num_gmp(p2_gmp.x, NUM_LIMBS);
            print_num_gmp(p2_gmp.y, NUM_LIMBS);
            success = false;
        }

        curve_point_clear_gmp(&p1_gmp);
        curve_point_clear_gmp(&p2_gmp);
    }

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

void check_add_point_point() {
    printf("Point addition:\n");
    if (test_point_addition()) {
        printf("Success\n");
    } else {
        printf("Failed\n");
    }
    printf("\n");
}

void check_double_point() {
    printf("Point double:\n");
    if (test_point_double()) {
        printf("Success\n");
    } else {
        printf("Failed\n");
    }
    printf("\n");
}

void check_neg_point() {
    printf("Point neg:\n");
    if (test_point_neg()) {
        printf("Success\n");
    } else {
        printf("Failed\n");
    }
    printf("\n");
}

int main(void) {
    initialize_constants();

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
        check_add_point_point();
        check_double_point();
        check_neg_point();

    #else /* TEST */

        #if PRIME_FIELD_BINARY_BIT_LENGTH == 131



        #endif /* PRIME_FIELD_BINARY_BIT_LENGTH */

    #endif /* TEST */

    printf("end\n");

    free_constants();
    return EXIT_SUCCESS;
}

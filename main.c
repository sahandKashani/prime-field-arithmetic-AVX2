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

#define NUM_ITERATIONS (100000L)
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

    for (unsigned int i = 0; (i < number_of_tests) && success; i++) {
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
            add_num_num(res, op1, op2, NUM_LIMBS, carry_in);
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

    for (unsigned int i = 0; (i < number_of_tests) && success; i++) {
        three_sorted_gmp operands = get_three_sorted_gmp(PRIME_FIELD_BINARY_BIT_LENGTH, gmp_random_state);
        gmp_int_set(op1_gmp, operands.middle);
        gmp_int_set(mod_gmp, operands.big);

        generate_random_gmp_number(op2_gmp, BASE_EXPONENT, gmp_random_state);
        gmp_printf("%0*Zx\n", 1 * LIMB_SIZE_IN_HEX, op2_gmp);
        print_num_gmp(op2_gmp, 1);

        zero_num(op1, NUM_LIMBS);
        zero_num(&op2, 1);
        zero_num(res, NUM_LIMBS);
        zero_num(&carry_in, 1);

        convert_gmp_to_num(op1, op1_gmp, NUM_LIMBS);
        convert_gmp_to_num(&op2, op2_gmp, 1);

        gmp_int_add(res_gmp, op1_gmp, op2_gmp);
        add_num_limb(res, op1, op2, NUM_LIMBS, carry_in);

        if (!is_equal_num_gmp(res, res_gmp, NUM_LIMBS)) {
            add_num_limb(res, op1, op2, NUM_LIMBS, carry_in);
            print_num_gmp(op1_gmp, NUM_LIMBS);
            print_num(op1, NUM_LIMBS);
            print_num_gmp(op2_gmp, 1);
            print_num(&op2, 1);
            print_num_gmp(res_gmp, NUM_LIMBS);
            print_num(res, NUM_LIMBS);
            success = false;
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

//bool test_sub_num_num(unsigned int number_of_tests, unsigned int seed) {
//    gmp_randstate_t gmp_random_state;
//    gmp_randinit_default(gmp_random_state);
//    gmp_randseed_ui(gmp_random_state, seed);
//
//    mpz_t op1_gmp;
//    mpz_t op2_gmp;
//    mpz_t res_gmp;
//    mpz_t mod_gmp;
//    mpz_init(op1_gmp);
//    mpz_init(op2_gmp);
//    mpz_init(res_gmp);
//    mpz_init(mod_gmp);
//
//    limb_t op1[NUM_LIMBS];
//    limb_t op2[NUM_LIMBS];
//    limb_t res[NUM_LIMBS];
//    limb_t borrow_in;
//
//    bool success = true;
//
//    for (unsigned int i = 0; (i < number_of_tests) && success; i++) {
//        three_sorted_gmp operands = get_three_sorted_gmp(PRIME_FIELD_BINARY_BIT_LENGTH, gmp_random_state);
//        /* op2 has to be smaller than op1 since this is normal subtraction (not modular) */
//        mpz_set(op1_gmp, operands.middle);
//        mpz_set(op2_gmp, operands.small);
//        mpz_set(mod_gmp, operands.big);
//
//        clear_num(op1, NUM_LIMBS);
//        clear_num(op2, NUM_LIMBS);
//        clear_num(res, NUM_LIMBS);
//        clear_num(&borrow_in, 1);
//
//        convert_gmp_to_num(op1, op1_gmp, NUM_LIMBS);
//        convert_gmp_to_num(op2, op2_gmp, NUM_LIMBS);
//
//        mpz_sub(res_gmp, op1_gmp, op2_gmp);
//        sub_num_num(res, op1, op2, NUM_LIMBS, borrow_in);
//
//        if (!is_equal_num_gmp(res, res_gmp, NUM_LIMBS)) {
//            sub_num_num(res, op1, op2, NUM_LIMBS, borrow_in);
//            print_num_gmp(op1_gmp, NUM_LIMBS);
//            print_num(op1, NUM_LIMBS);
//            print_num_gmp(op2_gmp, NUM_LIMBS);
//            print_num(op2, NUM_LIMBS);
//            print_num_gmp(res_gmp, NUM_LIMBS);
//            print_num(res, NUM_LIMBS);
//            success = false;
//        }
//
//        clear_three_sorted_gmp(operands);
//    }
//
//    mpz_clear(op1_gmp);
//    mpz_clear(op2_gmp);
//    mpz_clear(res_gmp);
//    mpz_clear(mod_gmp);
//    gmp_randclear(gmp_random_state);
//
//    return success;
//}
//
//bool test_mul_limb_limb(unsigned int number_of_tests, unsigned int seed) {
//    gmp_randstate_t gmp_random_state;
//    gmp_randinit_default(gmp_random_state);
//    gmp_randseed_ui(gmp_random_state, seed);
//
//    mpz_t op1_gmp;
//    mpz_t op2_gmp;
//    mpz_t res_gmp;
//    mpz_init(op1_gmp);
//    mpz_init(op2_gmp);
//    mpz_init(res_gmp);
//
//    limb_t op1;
//    limb_t op2;
//    limb_t res[2];
//
//    bool success = true;
//
//    for (unsigned int i = 0; (i < number_of_tests) && success; i++) {
//        generate_random_gmp_number(op1_gmp, BASE_EXPONENT, gmp_random_state);
//        generate_random_gmp_number(op2_gmp, BASE_EXPONENT, gmp_random_state);
//
//        clear_num(&op1, 1);
//        clear_num(&op2, 1);
//        clear_num(res, 2);
//
//        convert_gmp_to_num(&op1, op1_gmp, 1);
//        convert_gmp_to_num(&op2, op2_gmp, 1);
//
//        mpz_mul(res_gmp, op1_gmp, op2_gmp);
//        struct d_limb_t tmp = mul_limb_limb(op1, op2);
//
//        #if !FULL_LIMB_PRECISION
//
//            tmp = reduce_to_base_d_limb_t(tmp);
//
//        #endif
//
//        res[1] = tmp.hi;
//        res[0] = tmp.lo;
//
//        if (!is_equal_num_gmp(res, res_gmp, 2)) {
//            mul_limb_limb(op1, op2);
//            print_num_gmp(op1_gmp, 1);
//            print_num(&op1, 1);
//            print_num_gmp(op2_gmp, 1);
//            print_num(&op2, 1);
//            print_num_gmp(res_gmp, 2);
//            print_num(res, 2);
//            success = false;
//        }
//    }
//
//    mpz_clear(op1_gmp);
//    mpz_clear(op2_gmp);
//    mpz_clear(res_gmp);
//    gmp_randclear(gmp_random_state);
//
//    return success;
//}
//
//bool test_mul_num_limb(unsigned int number_of_tests, unsigned int seed) {
//    gmp_randstate_t gmp_random_state;
//    gmp_randinit_default(gmp_random_state);
//    gmp_randseed_ui(gmp_random_state, seed);
//
//    mpz_t op1_gmp;
//    mpz_t op2_gmp;
//    mpz_t res_gmp;
//    mpz_t mod_gmp;
//    mpz_init(op1_gmp);
//    mpz_init(op2_gmp);
//    mpz_init(res_gmp);
//    mpz_init(mod_gmp);
//
//    limb_t op1[NUM_LIMBS];
//    limb_t op2;
//    limb_t res[NUM_LIMBS + 1];
//
//    bool success = true;
//
//    for (unsigned int i = 0; (i < number_of_tests) && success; i++) {
//        three_sorted_gmp operands = get_three_sorted_gmp(PRIME_FIELD_BINARY_BIT_LENGTH, gmp_random_state);
//        mpz_set(op1_gmp, operands.middle);
//        mpz_set(mod_gmp, operands.big);
//
//        generate_random_gmp_number(op2_gmp, BASE_EXPONENT, gmp_random_state);
//
//        clear_num(op1, NUM_LIMBS);
//        clear_num(&op2, 1);
//        clear_num(res, NUM_LIMBS);
//
//        convert_gmp_to_num(op1, op1_gmp, NUM_LIMBS);
//        convert_gmp_to_num(&op2, op2_gmp, 1);
//
//        mpz_mul(res_gmp, op1_gmp, op2_gmp);
//        mul_num_limb(res, op1, op2, NUM_LIMBS);
//
//        if (!is_equal_num_gmp(res, res_gmp, NUM_LIMBS + 1)) {
//            mul_num_limb(res, op1, op2, NUM_LIMBS);
//            print_num_gmp(op1_gmp, NUM_LIMBS);
//            print_num(op1, NUM_LIMBS);
//            print_num_gmp(op2_gmp, 1);
//            print_num(&op2, 1);
//            print_num_gmp(res_gmp, NUM_LIMBS + 1);
//            print_num(res, NUM_LIMBS + 1);
//            success = false;
//        }
//
//        clear_three_sorted_gmp(operands);
//    }
//
//    mpz_clear(op1_gmp);
//    mpz_clear(op2_gmp);
//    mpz_clear(res_gmp);
//    mpz_clear(mod_gmp);
//    gmp_randclear(gmp_random_state);
//
//    return success;
//}
//
//bool test_mul_num_num(unsigned int number_of_tests, unsigned int seed) {
//    gmp_randstate_t gmp_random_state;
//    gmp_randinit_default(gmp_random_state);
//    gmp_randseed_ui(gmp_random_state, seed);
//
//    mpz_t op1_gmp;
//    mpz_t op2_gmp;
//    mpz_t res_gmp;
//    mpz_t mod_gmp;
//    mpz_init(op1_gmp);
//    mpz_init(op2_gmp);
//    mpz_init(res_gmp);
//    mpz_init(mod_gmp);
//
//    limb_t op1[NUM_LIMBS];
//    limb_t op2[NUM_LIMBS];
//    limb_t res[2 * NUM_LIMBS];
//
//    bool success = true;
//
//    for (unsigned int i = 0; (i < number_of_tests) && success; i++) {
//        three_sorted_gmp operands = get_three_sorted_gmp(PRIME_FIELD_BINARY_BIT_LENGTH, gmp_random_state);
//        mpz_set(op1_gmp, operands.small);
//        mpz_set(op2_gmp, operands.middle);
//        mpz_set(mod_gmp, operands.big);
//
//        clear_num(op1, NUM_LIMBS);
//        clear_num(op2, NUM_LIMBS);
//        clear_num(res, 2 * NUM_LIMBS);
//
//        convert_gmp_to_num(op1, op1_gmp, NUM_LIMBS);
//        convert_gmp_to_num(op2, op2_gmp, NUM_LIMBS);
//
//        mpz_mul(res_gmp, op1_gmp, op2_gmp);
//        mul_num_num(res, op1, op2, NUM_LIMBS);
//
//        if (!is_equal_num_gmp(res, res_gmp, 2 * NUM_LIMBS)) {
//            mul_num_num(res, op1, op2, NUM_LIMBS);
//            print_num_gmp(op1_gmp, NUM_LIMBS);
//            print_num(op1, NUM_LIMBS);
//            print_num_gmp(op2_gmp, NUM_LIMBS);
//            print_num(op2, NUM_LIMBS);
//            print_num_gmp(res_gmp, 2 * NUM_LIMBS);
//            print_num(res, 2 * NUM_LIMBS);
//            success = false;
//        }
//
//        clear_three_sorted_gmp(operands);
//    }
//
//    mpz_clear(op1_gmp);
//    mpz_clear(op2_gmp);
//    mpz_clear(res_gmp);
//    mpz_clear(mod_gmp);
//    gmp_randclear(gmp_random_state);
//
//    return success;
//}
//
//bool test_cmp_num_num(unsigned int number_of_tests, unsigned int seed) {
//    gmp_randstate_t gmp_random_state;
//    gmp_randinit_default(gmp_random_state);
//    gmp_randseed_ui(gmp_random_state, seed);
//
//    mpz_t op1_gmp;
//    mpz_t op2_gmp;
//    mpz_t mod_gmp;
//    mpz_init(op1_gmp);
//    mpz_init(op2_gmp);
//    mpz_init(mod_gmp);
//
//    limb_t op1[NUM_LIMBS];
//    limb_t op2[NUM_LIMBS];
//
//    bool success = true;
//
//    for (unsigned int i = 0; (i < number_of_tests) && success; i++) {
//        generate_random_gmp_number(mod_gmp, PRIME_FIELD_BINARY_BIT_LENGTH, gmp_random_state);
//        generate_random_gmp_less_than(op1_gmp, mod_gmp, gmp_random_state);
//        generate_random_gmp_less_than(op2_gmp, mod_gmp, gmp_random_state);
//
//        clear_num(op1, NUM_LIMBS);
//        clear_num(op2, NUM_LIMBS);
//
//        convert_gmp_to_num(op1, op1_gmp, NUM_LIMBS);
//        convert_gmp_to_num(op2, op2_gmp, NUM_LIMBS);
//
//        int res_gmp = mpz_cmp(op1_gmp, op2_gmp);
//        int res = cmp_num_num(op1, op2, NUM_LIMBS);
//
//        if (res_gmp != res) {
//            cmp_num_num(op1, op2, NUM_LIMBS);
//            print_num_gmp(op1_gmp, NUM_LIMBS);
//            print_num(op1, NUM_LIMBS);
//            print_num_gmp(op2_gmp, NUM_LIMBS);
//            print_num(op2, NUM_LIMBS);
//            printf("%d\n", res_gmp);
//            printf("%d\n", res);
//
//            success = false;
//        }
//    }
//
//    mpz_clear(op1_gmp);
//    mpz_clear(op2_gmp);
//    mpz_clear(mod_gmp);
//    gmp_randclear(gmp_random_state);
//
//    return success;
//}
//
//bool test_add_mod_num_num(unsigned int number_of_tests, unsigned int seed) {
//    gmp_randstate_t gmp_random_state;
//    gmp_randinit_default(gmp_random_state);
//    gmp_randseed_ui(gmp_random_state, seed);
//
//    mpz_t op1_gmp;
//    mpz_t op2_gmp;
//    mpz_t mod_gmp;
//    mpz_t res_gmp;
//    mpz_init(op1_gmp);
//    mpz_init(op2_gmp);
//    mpz_init(mod_gmp);
//    mpz_init(res_gmp);
//
//    limb_t op1[NUM_LIMBS];
//    limb_t op2[NUM_LIMBS];
//    limb_t mod[NUM_LIMBS];
//    limb_t res[NUM_LIMBS];
//
//    bool success = true;
//
//    for (unsigned int i = 0; (i < number_of_tests) && success; i++) {
//        three_sorted_gmp operands = get_three_sorted_gmp(PRIME_FIELD_BINARY_BIT_LENGTH, gmp_random_state);
//        mpz_set(op1_gmp, operands.small);
//        mpz_set(op2_gmp, operands.middle);
//        mpz_set(mod_gmp, operands.big);
//
//        clear_num(op1, NUM_LIMBS);
//        clear_num(op2, NUM_LIMBS);
//        clear_num(mod, NUM_LIMBS);
//        clear_num(res, NUM_LIMBS);
//
//        convert_gmp_to_num(op1, op1_gmp, NUM_LIMBS);
//        convert_gmp_to_num(op2, op2_gmp, NUM_LIMBS);
//        convert_gmp_to_num(mod, mod_gmp, NUM_LIMBS);
//
//        /* modular addition */
//        mpz_add(res_gmp, op1_gmp, op2_gmp);
//        mpz_mod(res_gmp, res_gmp, mod_gmp);
//        add_mod_num_num(res, op1, op2, mod, NUM_LIMBS);
//
//        if (!is_equal_num_gmp(res, res_gmp, NUM_LIMBS)) {
//            add_mod_num_num(res, op1, op2, mod, NUM_LIMBS);
//            print_num_gmp(op1_gmp, NUM_LIMBS);
//            print_num(op1, NUM_LIMBS);
//            print_num_gmp(op2_gmp, NUM_LIMBS);
//            print_num(op2, NUM_LIMBS);
//            print_num_gmp(mod_gmp, NUM_LIMBS);
//            print_num(mod, NUM_LIMBS);
//            print_num_gmp(res_gmp, NUM_LIMBS);
//            print_num(res, NUM_LIMBS);
//            success = false;
//        }
//
//        clear_three_sorted_gmp(operands);
//    }
//
//    mpz_clear(op1_gmp);
//    mpz_clear(op2_gmp);
//    mpz_clear(mod_gmp);
//    mpz_clear(res_gmp);
//    gmp_randclear(gmp_random_state);
//
//    return success;
//}
//
//bool test_sub_mod_num_num(unsigned int number_of_tests, unsigned int seed) {
//    gmp_randstate_t gmp_random_state;
//    gmp_randinit_default(gmp_random_state);
//    gmp_randseed_ui(gmp_random_state, seed);
//
//    mpz_t op1_gmp;
//    mpz_t op2_gmp;
//    mpz_t mod_gmp;
//    mpz_t res_gmp;
//    mpz_init(op1_gmp);
//    mpz_init(op2_gmp);
//    mpz_init(mod_gmp);
//    mpz_init(res_gmp);
//
//    limb_t op1[NUM_LIMBS];
//    limb_t op2[NUM_LIMBS];
//    limb_t mod[NUM_LIMBS];
//    limb_t res[NUM_LIMBS];
//
//    bool success = true;
//
//    for (unsigned int i = 0; (i < number_of_tests) && success; i++) {
//        three_sorted_gmp operands = get_three_sorted_gmp(PRIME_FIELD_BINARY_BIT_LENGTH, gmp_random_state);
//        mpz_set(op1_gmp, operands.small);
//        mpz_set(op2_gmp, operands.middle);
//        mpz_set(mod_gmp, operands.big);
//
//        clear_num(op1, NUM_LIMBS);
//        clear_num(op2, NUM_LIMBS);
//        clear_num(mod, NUM_LIMBS);
//        clear_num(res, NUM_LIMBS);
//
//        convert_gmp_to_num(op1, op1_gmp, NUM_LIMBS);
//        convert_gmp_to_num(op2, op2_gmp, NUM_LIMBS);
//        convert_gmp_to_num(mod, mod_gmp, NUM_LIMBS);
//
//        /* modular subtraction */
//        mpz_sub(res_gmp, op1_gmp, op2_gmp);
//        mpz_mod(res_gmp, res_gmp, mod_gmp);
//        sub_mod_num_num(res, op1, op2, mod, NUM_LIMBS);
//
//        if (!is_equal_num_gmp(res, res_gmp, NUM_LIMBS)) {
//            sub_mod_num_num(res, op1, op2, mod, NUM_LIMBS);
//            print_num_gmp(op1_gmp, NUM_LIMBS);
//            print_num(op1, NUM_LIMBS);
//            print_num_gmp(op2_gmp, NUM_LIMBS);
//            print_num(op2, NUM_LIMBS);
//            print_num_gmp(mod_gmp, NUM_LIMBS);
//            print_num(mod, NUM_LIMBS);
//            print_num_gmp(res_gmp, NUM_LIMBS);
//            print_num(res, NUM_LIMBS);
//            success = false;
//        }
//
//        clear_three_sorted_gmp(operands);
//    }
//
//    mpz_clear(op1_gmp);
//    mpz_clear(op2_gmp);
//    mpz_clear(mod_gmp);
//    mpz_clear(res_gmp);
//    gmp_randclear(gmp_random_state);
//
//    return success;
//}
//
//bool test_mul_montgomery_num_num(unsigned int number_of_tests, unsigned int seed) {
//    gmp_randstate_t gmp_random_state;
//    gmp_randinit_default(gmp_random_state);
//    gmp_randseed_ui(gmp_random_state, seed);
//
//    mpz_t op1_gmp;
//    mpz_t op2_gmp;
//    mpz_t mod_gmp;
//    mpz_t mod_prime_gmp;
//    mpz_t res_gmp;
//    mpz_t base_gmp;
//    mpz_t R_gmp;
//    mpz_t invR_gmp;
//    mpz_init(op1_gmp);
//    mpz_init(op2_gmp);
//    mpz_init(mod_gmp);
//    mpz_init(mod_prime_gmp);
//    mpz_init(res_gmp);
//    mpz_init(base_gmp);
//    mpz_init(R_gmp);
//    mpz_init(invR_gmp);
//
//    mpz_ui_pow_ui(base_gmp, 2, BASE_EXPONENT);
//    mpz_ui_pow_ui(R_gmp, 2, BASE_EXPONENT * NUM_LIMBS);
//
//    limb_t op1[NUM_LIMBS];
//    limb_t op2[NUM_LIMBS];
//    limb_t mod[NUM_LIMBS];
//    limb_t mod_prime;
//    limb_t res[NUM_LIMBS];
//
//    bool success = true;
//
//    for (unsigned int i = 0; (i < number_of_tests) && success; i++) {
//        three_sorted_gmp operands;
//
//        bool operands_ok;
//        do {
//            operands = get_three_sorted_gmp(PRIME_FIELD_BINARY_BIT_LENGTH, gmp_random_state);
//            mpz_set(op1_gmp, operands.small);
//            mpz_set(op2_gmp, operands.middle);
//            mpz_set(mod_gmp, operands.big);
//
//            operands_ok = true;
//
//            int inverse_exists = mpz_invert(mod_prime_gmp, mod_gmp, base_gmp);
//
//            if (!inverse_exists) {
//                operands_ok = false;
//                clear_three_sorted_gmp(operands);
//            }
//        } while (!operands_ok);
//
//        mpz_neg(mod_prime_gmp, mod_prime_gmp);
//        mpz_mod(mod_prime_gmp, mod_prime_gmp, base_gmp);
//        mpz_invert(invR_gmp, R_gmp, mod_gmp);
//
//        clear_num(op1, NUM_LIMBS);
//        clear_num(op2, NUM_LIMBS);
//        clear_num(mod, NUM_LIMBS);
//        clear_num(&mod_prime, 1);
//        clear_num(res, NUM_LIMBS);
//
//        convert_gmp_to_num(op1, op1_gmp, NUM_LIMBS);
//        convert_gmp_to_num(op2, op2_gmp, NUM_LIMBS);
//        convert_gmp_to_num(mod, mod_gmp, NUM_LIMBS);
//        convert_gmp_to_num(&mod_prime, mod_prime_gmp, 1);
//
//        /* montgomery multiplication */
//        mpz_mul(res_gmp, op1_gmp, op2_gmp);
//        mpz_mul(res_gmp, res_gmp, invR_gmp);
//        mpz_mod(res_gmp, res_gmp, mod_gmp);
//        mul_montgomery_num_num(res, op1, op2, mod, mod_prime, NUM_LIMBS);
//
//        if (!is_equal_num_gmp(res, res_gmp, NUM_LIMBS)) {
//            mul_montgomery_num_num(res, op1, op2, mod, mod_prime, NUM_LIMBS);
//            print_num_gmp(op1_gmp, NUM_LIMBS);
//            print_num(op1, NUM_LIMBS);
//            print_num_gmp(op2_gmp, NUM_LIMBS);
//            print_num(op2, NUM_LIMBS);
//            print_num_gmp(mod_gmp, NUM_LIMBS);
//            print_num(mod, NUM_LIMBS);
//            print_num_gmp(res_gmp, NUM_LIMBS);
//            print_num(res, NUM_LIMBS);
//            success = false;
//        }
//
//        clear_three_sorted_gmp(operands);
//    }
//
//    mpz_clear(op1_gmp);
//    mpz_clear(op2_gmp);
//    mpz_clear(mod_gmp);
//    mpz_clear(mod_prime_gmp);
//    mpz_clear(res_gmp);
//    mpz_clear(base_gmp);
//    mpz_clear(R_gmp);
//    mpz_clear(invR_gmp);
//    gmp_randclear(gmp_random_state);
//
//    return success;
//}

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

//void check_sub_num_num() {
//    printf("Sub:\n");
//    if (test_sub_num_num(NUM_ITERATIONS, SEED)) {
//        printf("Success\n");
//    } else {
//        printf("Failed\n");
//    }
//    printf("\n");
//}
//
//void check_mul_limb_limb() {
//    printf("mul_limb_limb:\n");
//    if (test_mul_limb_limb(NUM_ITERATIONS, SEED)) {
//        printf("Success\n");
//    } else {
//        printf("Failed\n");
//    }
//    printf("\n");
//}
//
//void check_mul_num_limb() {
//    printf("mul_num_limb:\n");
//    if (test_mul_num_limb(NUM_ITERATIONS, SEED)) {
//        printf("Success\n");
//    } else {
//        printf("Failed\n");
//    }
//    printf("\n");
//}
//
//void check_mul_num_num() {
//    printf("Mul:\n");
//    if (test_mul_num_num(NUM_ITERATIONS, SEED)) {
//        printf("Success\n");
//    } else {
//        printf("Failed\n");
//    }
//    printf("\n");
//}
//
//void check_cmp_num_num() {
//    printf("cmp:\n");
//    if (test_cmp_num_num(NUM_ITERATIONS, SEED)) {
//        printf("Success\n");
//    } else {
//        printf("Failed\n");
//    }
//    printf("\n");
//}
//
//void check_add_mod_num_num() {
//    printf("Add Mod:\n");
//    if (test_add_mod_num_num(NUM_ITERATIONS, SEED)) {
//        printf("Success\n");
//    } else {
//        printf("Failed\n");
//    }
//    printf("\n");
//}
//
//void check_sub_mod_num_num() {
//    printf("Sub Mod:\n");
//    if (test_sub_mod_num_num(NUM_ITERATIONS, SEED)) {
//        printf("Success\n");
//    } else {
//        printf("Failed\n");
//    }
//    printf("\n");
//}
//
//void check_mul_montgomery_num_num() {
//    printf("Mul Montgomery:\n");
//    if (test_mul_montgomery_num_num(NUM_ITERATIONS, SEED)) {
//        printf("Success\n");
//    } else {
//        printf("Failed\n");
//    }
//    printf("\n");
//}

int main(void) {
    #if !SIMD_PARALLEL_WALKS

        check_add_num_num();
        check_add_num_limb();
        check_sub_num_num();
        check_mul_limb_limb();
        check_mul_num_limb();
        check_mul_num_num();
        check_cmp_num_num();
        check_add_mod_num_num();
        check_sub_mod_num_num();
        check_mul_montgomery_num_num();

    #elif SIMD_PARALLEL_WALKS

//        check_add_num_num();
        check_add_num_limb();

//        gmp_randstate_t gmp_random_state;
//        gmp_randinit_default(gmp_random_state);
//        gmp_randseed_ui(gmp_random_state, SEED);
//
//        limb_t a_num[NUM_LIMBS];
//        limb_t b_num = set_limb(1);
//        gmp_int_t a_gmp;
//
//        gmp_int_init(a_gmp);
//        generate_random_gmp_number(a_gmp, PRIME_FIELD_BINARY_BIT_LENGTH, gmp_random_state);
//
//        convert_gmp_to_num(a_num, a_gmp, NUM_LIMBS);
//        print_num_gmp(a_gmp, NUM_LIMBS);
//        print_num(a_num, NUM_LIMBS);
//        printf("equal_num_num = %d\n", is_equal_num_num(a_num, a_num, NUM_LIMBS));
//        printf("equal_num_gmp = %d\n", is_equal_num_gmp(a_num, a_gmp, NUM_LIMBS));
//        add_num_limb(a_num, a_num, b_num, NUM_LIMBS, zero());
//        printf("equal_num_gmp = %d\n", is_equal_num_gmp(a_num, a_gmp, NUM_LIMBS));
//
//        gmp_int_clear(a_gmp);
//        gmp_randclear(gmp_random_state);

    #endif

    return EXIT_SUCCESS;
}

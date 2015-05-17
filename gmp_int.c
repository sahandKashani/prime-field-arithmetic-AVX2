#include <gmp.h>
#include "gmp_int.h"
#include "limb.h"

void gmp_int_init(gmp_int_t x) {
    for (unsigned int i = 0; i < NUM_ENTRIES_IN_LIMB; i++) {
        mpz_init(x[i]);
    }
}

void gmp_int_set(gmp_int_t rop, gmp_int_t op) {
    for (unsigned int i = 0; i < NUM_ENTRIES_IN_LIMB; i++) {
        mpz_set(rop[i], op[i]);
    }
}

void gmp_int_add(gmp_int_t rop, gmp_int_t op1, gmp_int_t op2) {
    for (unsigned int i = 0; i < NUM_ENTRIES_IN_LIMB; i++) {
        mpz_add(rop[i], op1[i], op2[i]);
    }
}

void gmp_int_sub(gmp_int_t rop, gmp_int_t op1, gmp_int_t op2) {
    for (unsigned int i = 0; i < NUM_ENTRIES_IN_LIMB; i++) {
        mpz_sub(rop[i], op1[i], op2[i]);
    }
}

void gmp_int_mul(gmp_int_t rop, gmp_int_t op1, gmp_int_t op2) {
    for (unsigned int i = 0; i < NUM_ENTRIES_IN_LIMB; i++) {
        mpz_mul(rop[i], op1[i], op2[i]);
    }
}

void gmp_int_add_mod(gmp_int_t rop, gmp_int_t op1, gmp_int_t op2, gmp_int_t mod) {
    for (unsigned int i = 0; i < NUM_ENTRIES_IN_LIMB; i++) {
        mpz_add(rop[i], op1[i], op2[i]);
        mpz_mod(rop[i], rop[i], mod[i]);
    }
}

void gmp_int_sub_mod(gmp_int_t rop, gmp_int_t op1, gmp_int_t op2, gmp_int_t mod) {
    for (unsigned int i = 0; i < NUM_ENTRIES_IN_LIMB; i++) {
        mpz_sub(rop[i], op1[i], op2[i]);
        mpz_mod(rop[i], rop[i], mod[i]);
    }
}

void gmp_int_mul_montgomery(gmp_int_t rop, gmp_int_t op1, gmp_int_t op2, gmp_int_t invR, gmp_int_t mod) {
    for (unsigned int i = 0; i < NUM_ENTRIES_IN_LIMB; i++) {
        mpz_mul(rop[i], op1[i], op2[i]);
        mpz_mul(rop[i], rop[i], invR[i]);
        mpz_mod(rop[i], rop[i], mod[i]);
    }
}

#include <gmp.h>
#include "constants.h"
#include "gmp_int.h"
#include "limb.h"

void gmp_int_init(gmp_int_t x) {
    for (unsigned int i = 0; i < NUM_ENTRIES_IN_LIMB; i++) {
        mpz_init(x[i]);
    }
}

void gmp_int_clear(gmp_int_t x) {
    for (unsigned int i = 0; i < NUM_ENTRIES_IN_LIMB; i++) {
        mpz_clear(x[i]);
    }
}

void gmp_int_set(gmp_int_t rop, gmp_int_t op) {
    for (unsigned int i = 0; i < NUM_ENTRIES_IN_LIMB; i++) {
        mpz_set(rop[i], op[i]);
    }
}

void gmp_int_cmp(int *rop, gmp_int_t op1, gmp_int_t op2) {
    for (unsigned int i = 0; i < NUM_ENTRIES_IN_LIMB; i++) {
        rop[i] = mpz_cmp(op1[i], op2[i]);
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

void gmp_int_urandomm(gmp_int_t rop, gmp_randstate_t state, gmp_int_t n) {
    for (unsigned int i = 0; i < NUM_ENTRIES_IN_LIMB; i++) {
        mpz_urandomm(rop[i], state, n[i]);
    }
}

void gmp_int_rrandomb(gmp_int_t rop, gmp_randstate_t state, mp_bitcnt_t n) {
    for (unsigned int i = 0; i < NUM_ENTRIES_IN_LIMB; i++) {
        mpz_rrandomb(rop[i], state, n);
    }
}

void gmp_int_urandomb(gmp_int_t rop, gmp_randstate_t state, mp_bitcnt_t n) {
    for (unsigned int i = 0; i < NUM_ENTRIES_IN_LIMB; i++) {
        mpz_urandomb(rop[i], state, n);
    }
}

void gmp_int_import(gmp_int_t rop, size_t count, int order, size_t size, int endian, size_t nails, const void *op) {
    for (unsigned int i = 0; i < NUM_ENTRIES_IN_LIMB; i++) {
        mpz_import(rop[i], count, order, size, endian, nails, ((limb_building_block_t *) op) + (i * count));
    }
}

void gmp_int_export(void *rop, size_t *countp, int order, size_t size, int endian, size_t nails, gmp_int_t op, unsigned int num_limbs) {
    for (unsigned int i = 0; i < NUM_ENTRIES_IN_LIMB; i++) {
        mpz_export(((limb_building_block_t *) rop) + (i * num_limbs), countp, order, size, endian, nails, op[i]);
    }
}

void gmp_int_ui_pow_ui(gmp_int_t rop, unsigned long int base, unsigned long int exp) {
    for (unsigned int i = 0; i < NUM_ENTRIES_IN_LIMB; i++) {
        mpz_ui_pow_ui(rop[i], base, exp);
    }
}

void gmp_int_neg(gmp_int_t rop, gmp_int_t op) {
    for (unsigned int i = 0; i < NUM_ENTRIES_IN_LIMB; i++) {
        mpz_neg(rop[i], op[i]);
    }
}

void gmp_int_mod(gmp_int_t r, gmp_int_t n, gmp_int_t d) {
    for (unsigned int i = 0; i < NUM_ENTRIES_IN_LIMB; i++) {
        mpz_mod(r[i], n[i], d[i]);
    }
}

void gmp_int_invert(int *inverse_exists, gmp_int_t rop, gmp_int_t op1, gmp_int_t op2) {
    for (unsigned int i = 0; i < NUM_ENTRIES_IN_LIMB; i++) {
        int inv_exists = mpz_invert(rop[i], op1[i], op2[i]);
        if (inverse_exists != NULL) {
            inverse_exists[i] = inv_exists;
        }
    }
}

int gmp_int_set_str(gmp_int_t rop, const char *str, int base) {
    int ret = 0;
    for (unsigned int i = 0; i < NUM_ENTRIES_IN_LIMB; i++) {
        ret = mpz_set_str(rop[i], str, base);
    }
    return ret;
}

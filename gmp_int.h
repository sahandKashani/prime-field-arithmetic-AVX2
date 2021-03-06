#ifndef GMP_INT_H_
#define GMP_INT_H_

    #include "limb.h"
    #include <gmp.h>

    typedef mpz_t gmp_int_t[NUM_ENTRIES_IN_LIMB];

    void gmp_int_init(gmp_int_t x);
    void gmp_int_clear(gmp_int_t x);
    void gmp_int_set(gmp_int_t rop, gmp_int_t op);
    void gmp_int_cmp(int *rop, gmp_int_t op1, gmp_int_t op2);
    void gmp_int_add(gmp_int_t rop, gmp_int_t op1, gmp_int_t op2);
    void gmp_int_sub(gmp_int_t rop, gmp_int_t op1, gmp_int_t op2);
    void gmp_int_mul(gmp_int_t rop, gmp_int_t op1, gmp_int_t op2);
    void gmp_int_add_mod(gmp_int_t rop, gmp_int_t op1, gmp_int_t op2, gmp_int_t mod);
    void gmp_int_sub_mod(gmp_int_t rop, gmp_int_t op1, gmp_int_t op2, gmp_int_t mod);
    void gmp_int_mul_montgomery(gmp_int_t rop, gmp_int_t op1, gmp_int_t op2, gmp_int_t invR, gmp_int_t mod);
    void gmp_int_urandomm(gmp_int_t rop, gmp_randstate_t state, gmp_int_t n);
    void gmp_int_rrandomb(gmp_int_t rop, gmp_randstate_t state, mp_bitcnt_t n);
    void gmp_int_urandomm_with_inverse(gmp_int_t rop, gmp_randstate_t state, gmp_int_t n);
    void gmp_int_rrandomb_with_inverse(gmp_int_t rop, gmp_randstate_t state, mp_bitcnt_t n, gmp_int_t mod);
    void gmp_int_urandomb(gmp_int_t rop, gmp_randstate_t state, mp_bitcnt_t n);
    void gmp_int_import(gmp_int_t rop, size_t count, int order, size_t size, int endian, size_t nails, const void *op);
    void gmp_int_export(void *rop, size_t *countp, int order, size_t size, int endian, size_t nails, gmp_int_t op, unsigned int num_limbs);
    void gmp_int_ui_pow_ui (gmp_int_t rop, unsigned long int base, unsigned long int exp);
    void gmp_int_neg (gmp_int_t rop, gmp_int_t op);
    void gmp_int_mod (gmp_int_t r, gmp_int_t n, gmp_int_t d);
    void gmp_int_invert(int *inverse_exists, gmp_int_t rop, gmp_int_t op1, gmp_int_t op2);
    void gmp_int_montgomery_inverse(gmp_int_t res, gmp_int_t op, gmp_int_t mod);
    int gmp_int_set_str(gmp_int_t rop, const char *str, int base);
    int gmp_int_set_strings(gmp_int_t rop, char **str, int base);

#endif /* GMP_INT_H_ */

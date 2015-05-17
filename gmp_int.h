#ifndef GMP_INT_H_
#define GMP_INT_H_

    #include "limb.h"
    #include <gmp.h>

    typedef mpz_t gmp_int_t[NUM_ENTRIES_IN_LIMB];

    void gmp_int_init(gmp_int_t x);
    void gmp_int_set(gmp_int_t rop, gmp_int_t op);
    void gmp_int_add(gmp_int_t rop, gmp_int_t op1, gmp_int_t op2);
    void gmp_int_sub(gmp_int_t rop, gmp_int_t op1, gmp_int_t op2);
    void gmp_int_mul(gmp_int_t rop, gmp_int_t op1, gmp_int_t op2);
    void gmp_int_add_mod(gmp_int_t rop, gmp_int_t op1, gmp_int_t op2, gmp_int_t mod);
    void gmp_int_sub_mod(gmp_int_t rop, gmp_int_t op1, gmp_int_t op2, gmp_int_t mod);
    void gmp_int_mul_montgomery(gmp_int_t rop, gmp_int_t op1, gmp_int_t op2, gmp_int_t invR, gmp_int_t mod);
    void gmp_int_urandomm(gmp_int_t rop, gmp_randstate_t state, gmp_int_t n);
    void gmp_int_rrandomb(gmp_int_t rop, gmp_randstate_t state, mp_bitcnt_t n);
    void gmp_int_urandomb(gmp_int_t rop, gmp_randstate_t state, mp_bitcnt_t n);

#endif /* GMP_INT_H_ */

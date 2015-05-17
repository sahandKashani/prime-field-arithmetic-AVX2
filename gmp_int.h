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

#endif /* GMP_INT_H_ */

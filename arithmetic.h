#ifndef ARITHMETIC_H_
#define ARITHMETIC_H_

    #include <stdbool.h>
    #include "limb.h"

    limb_t add_num_num(limb_t *c, limb_t *a, limb_t *b, unsigned int num_limbs, limb_t carry_in);
    limb_t add_num_limb(limb_t *c, limb_t *a, limb_t b, unsigned int num_limbs, limb_t carry_in);
    limb_t sub_num_num(limb_t *c, limb_t *a, limb_t *b, unsigned int num_limbs, limb_t borrow_in);
    void mul_num_limb(limb_t *c, limb_t *a, limb_t b, unsigned int num_limbs);
    void mul_num_num(limb_t *c, limb_t *a, limb_t *b, unsigned int num_limbs);
    bool equals_zero(limb_t *num, unsigned int num_limbs);
    int cmp_num_num(limb_t *a, limb_t *b, unsigned int num_limbs);
    void and_num_num(limb_t *c, limb_t *a, limb_t *b, unsigned int num_limbs);
    void add_mod_num_num(limb_t *c, limb_t *a, limb_t *b, limb_t *m, unsigned int num_limbs);
    void sub_mod_num_num(limb_t *c, limb_t *a, limb_t *b, limb_t *m, unsigned int num_limbs);
    void mul_montgomery_num_num(limb_t *z, limb_t *x, limb_t *y, limb_t *m, limb_t m_prime, unsigned int num_limbs);

#endif /* ARITHMETIC_H_ */

#include <stdio.h>
#include "arithmetic.h"
#include "elliptic_curve.h"
#include "utilities.h"

/**
 * Supposes data is in Montgomery form prior to being called
 */
struct curve_point add_point_point(struct curve_point a, struct curve_point b, limb_t *m, limb_t m_prime) {
    struct curve_point c;

    limb_t numer[NUM_LIMBS];
    limb_t denom[NUM_LIMBS];
    limb_t lambda[NUM_LIMBS];

    /* lambda = (y2 - y1) / (x2 - x1) */
    sub_mod_num_num(numer, b.y, a.y, m, NUM_LIMBS);
    print_num(numer, NUM_LIMBS);

    sub_mod_num_num(denom, b.x, a.x, m, NUM_LIMBS);
    print_num(denom, NUM_LIMBS);

    invert_num(denom, denom, m, NUM_LIMBS);
    print_num(denom, NUM_LIMBS);

    mul_montgomery_num_num(lambda, numer, denom, m, m_prime, NUM_LIMBS);
    print_num(lambda, NUM_LIMBS);

    /* x */
    mul_montgomery_num_num(c.x, lambda, lambda, m, m_prime, NUM_LIMBS);
    sub_mod_num_num(c.x, c.x, a.x, m, NUM_LIMBS);
    sub_mod_num_num(c.x, c.x, b.x, m, NUM_LIMBS);

    /* y */
    sub_mod_num_num(c.y, a.x, c.x, m, NUM_LIMBS);
    mul_montgomery_num_num(c.y, lambda, c.y, m, m_prime, NUM_LIMBS);
    sub_mod_num_num(c.y, c.y, a.y, m, NUM_LIMBS);

    return c;
}

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

bool is_on_curve_gmp(gmp_int_t x_gmp, gmp_int_t y_gmp) {
    gmp_int_t a_gmp;
    gmp_int_t b_gmp;
    gmp_int_t m_gmp;
    gmp_int_t lhs_gmp; /* (y^2) mod m */
    gmp_int_t rhs_gmp; /* (x^3 + a*x + b) mod m */
    gmp_int_t ax_plus_b_gmp;

    gmp_int_init(a_gmp);
    gmp_int_init(b_gmp);
    gmp_int_init(m_gmp);
    gmp_int_init(lhs_gmp);
    gmp_int_init(rhs_gmp);
    gmp_int_init(ax_plus_b_gmp);

    gmp_int_set_str(a_gmp, a_hex, 16);
    gmp_int_set_str(b_gmp, b_hex, 16);
    gmp_int_set_str(m_gmp, m_hex, 16);

    /* lhs */
    gmp_int_mul(lhs_gmp, y_gmp, y_gmp);
    gmp_int_mod(lhs_gmp, lhs_gmp, m_gmp);

    /* rhs */
    gmp_int_mul(ax_plus_b_gmp, a_gmp, x_gmp);
    gmp_int_add(ax_plus_b_gmp, ax_plus_b_gmp, b_gmp);
    gmp_int_mul(rhs_gmp, x_gmp, x_gmp);
    gmp_int_mul(rhs_gmp, rhs_gmp, x_gmp);
    gmp_int_add(rhs_gmp, rhs_gmp, ax_plus_b_gmp);
    gmp_int_mod(rhs_gmp, rhs_gmp, m_gmp);

    int on_curve[NUM_ENTRIES_IN_LIMB];
    gmp_int_cmp(on_curve, lhs_gmp, rhs_gmp);

    gmp_int_clear(a_gmp);
    gmp_int_clear(b_gmp);
    gmp_int_clear(m_gmp);
    gmp_int_clear(lhs_gmp);
    gmp_int_clear(rhs_gmp);
    gmp_int_clear(ax_plus_b_gmp);

    bool on_curve_
    for (unsigned int i = 0; i < NUM_ENTRIES_IN_LIMB; i++) {

    }

    return on_curve;
}

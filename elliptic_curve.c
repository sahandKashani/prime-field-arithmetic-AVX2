#include <assert.h>
#include <stdio.h>
#include "arithmetic.h"
#include "elliptic_curve.h"
#include "utilities.h"

/**
 * Supposes data is in Montgomery form prior to being called
 */
struct curve_point add_point_point(struct curve_point p1, struct curve_point p2) {
    struct curve_point p3;

    limb_t numer[NUM_LIMBS];
    limb_t denom[NUM_LIMBS];
    limb_t lambda[NUM_LIMBS];

    /* lambda = (y2 - y1) / (x2 - x1) */
    sub_mod_num_num(numer, p2.y, p1.y, m_glo, NUM_LIMBS);
    sub_mod_num_num(denom, p2.x, p1.x, m_glo, NUM_LIMBS);
    invert_num(denom, denom, m_glo, NUM_LIMBS);
    mul_montgomery_num_num(lambda, numer, denom, m_glo, m_prime_glo, NUM_LIMBS);

    /* x */
    mul_montgomery_num_num(p3.x, lambda, lambda, m_glo, m_prime_glo, NUM_LIMBS);
    sub_mod_num_num(p3.x, p3.x, p1.x, m_glo, NUM_LIMBS);
    sub_mod_num_num(p3.x, p3.x, p2.x, m_glo, NUM_LIMBS);

    /* y */
    sub_mod_num_num(p3.y, p1.x, p3.x, m_glo, NUM_LIMBS);
    mul_montgomery_num_num(p3.y, lambda, p3.y, m_glo, m_prime_glo, NUM_LIMBS);
    sub_mod_num_num(p3.y, p3.y, p1.y, m_glo, NUM_LIMBS);

    return p3;
}

/**
 * Supposes data is in Montgomery form prior to being called
 */
struct curve_point_gmp add_point_point_gmp(struct curve_point_gmp p1, struct curve_point_gmp p2) {
    struct curve_point_gmp p3;
    gmp_int_init(p3.x);
    gmp_int_init(p3.y);

    gmp_int_t numer_gmp;
    gmp_int_t denom_gmp;
    gmp_int_t lambda_gmp;
    gmp_int_init(numer_gmp);
    gmp_int_init(denom_gmp);
    gmp_int_init(lambda_gmp);

    /* lambda = (y2 - y1) / (x2 - x1) */
    gmp_int_sub_mod(numer_gmp, p2.y, p1.y, m_glo_gmp);
    gmp_int_sub_mod(denom_gmp, p2.x, p1.x, m_glo_gmp);
    gmp_int_invert(NULL, denom_gmp, denom_gmp, m_glo_gmp);
    gmp_int_mul_montgomery(lambda_gmp, numer_gmp, denom_gmp, inv_R_glo_gmp, m_glo_gmp);

    /* x */
    gmp_int_mul_montgomery(p3.x, lambda_gmp, lambda_gmp, inv_R_glo_gmp, m_glo_gmp);
    gmp_int_sub_mod(p3.x, p3.x, p1.x, m_glo_gmp);
    gmp_int_sub_mod(p3.x, p3.x, p2.x, m_glo_gmp);

    /* y */
    gmp_int_sub_mod(p3.y, p1.x, p3.x, m_glo_gmp);
    gmp_int_mul_montgomery(p3.y, lambda_gmp, p3.y, inv_R_glo_gmp, m_glo_gmp);
    gmp_int_sub_mod(p3.y, p3.y, p1.y, m_glo_gmp);

    return p3;
}

/* assumes input is in standard representation */
bool is_on_curve(limb_t *x_num, limb_t *y_num) {
    gmp_int_t x_gmp;
    gmp_int_t y_gmp;
    gmp_int_init(x_gmp);
    gmp_int_init(y_gmp);

    convert_num_to_gmp(x_gmp, x_num, NUM_LIMBS);
    convert_num_to_gmp(y_gmp, y_num, NUM_LIMBS);

    bool is_on_curve = is_on_curve_gmp(x_gmp, y_gmp);

    gmp_int_clear(x_gmp);
    gmp_int_clear(y_gmp);

    return is_on_curve;
}

/* assumes input is in standard representation */
bool is_on_curve_point(struct curve_point p) {
    return is_on_curve(p.x, p.y);
}

/* assumes input is in standard representation */
bool is_on_curve_gmp(gmp_int_t x_gmp, gmp_int_t y_gmp) {
    /* (y^2) mod m == (x^3 + a*x + b) mod m */
    gmp_int_t lhs_gmp; /* (y^2) mod m */
    gmp_int_t rhs_gmp; /* (x^3 + a*x + b) mod m */
    gmp_int_t ax_plus_b_gmp;

    gmp_int_init(lhs_gmp);
    gmp_int_init(rhs_gmp);
    gmp_int_init(ax_plus_b_gmp);

    /* lhs */
    gmp_int_mul(lhs_gmp, y_gmp, y_gmp);
    gmp_int_mod(lhs_gmp, lhs_gmp, m_glo_gmp);

    /* rhs */
    gmp_int_mul(ax_plus_b_gmp, a_glo_gmp, x_gmp);
    gmp_int_add(ax_plus_b_gmp, ax_plus_b_gmp, b_glo_gmp);
    gmp_int_mul(rhs_gmp, x_gmp, x_gmp);
    gmp_int_mul(rhs_gmp, rhs_gmp, x_gmp);
    gmp_int_add(rhs_gmp, rhs_gmp, ax_plus_b_gmp);
    gmp_int_mod(rhs_gmp, rhs_gmp, m_glo_gmp);

    int on_curve[NUM_ENTRIES_IN_LIMB];
    gmp_int_cmp(on_curve, lhs_gmp, rhs_gmp);

    gmp_int_clear(lhs_gmp);
    gmp_int_clear(rhs_gmp);
    gmp_int_clear(ax_plus_b_gmp);

    bool on_curve_final = true;
    for (unsigned int i = 0; i < NUM_ENTRIES_IN_LIMB; i++) {
        if (on_curve[i] != 0) {
            on_curve_final = false;
        }
    }

    return on_curve_final;
}

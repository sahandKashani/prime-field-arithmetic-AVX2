#include <assert.h>
#include <stdio.h>
#include "prime_field.h"
#include "elliptic_curve.h"
#include "utilities.h"

void curve_point_init_gmp(struct curve_point_gmp *p) {
    gmp_int_init(p->x);
    gmp_int_init(p->y);
}

void curve_point_clear_gmp(struct curve_point_gmp *p) {
    gmp_int_clear(p->x);
    gmp_int_clear(p->y);
}

/**
 * Supposes data is in Montgomery form prior to being called
 */
void neg_point(struct curve_point *p2, struct curve_point *p1, unsigned int num_limbs) {
    struct curve_point p_out;

    limb_t zero[NUM_LIMBS];
    zero_num(zero, num_limbs);
    copy_num(p_out.x, p1->x, num_limbs);
    sub_mod_num_num(p_out.y, zero, p1->y, m_glo, num_limbs);

    copy_num(p2->x, p_out.x, num_limbs);
    copy_num(p2->y, p_out.y, num_limbs);
}

/**
 * Supposes data is in Montgomery form prior to being called
 */
void neg_point_gmp(struct curve_point_gmp *p2, struct curve_point_gmp *p1) {
    gmp_int_t zero_gmp;
    gmp_int_init(zero_gmp);
    gmp_int_set_str(zero_gmp, "0", 10);
    gmp_int_set(p2->x, p1->x);
    gmp_int_sub_mod(p2->y, zero_gmp, p1->y, m_glo_gmp);
    gmp_int_clear(zero_gmp);
}

/**
 * Supposes data is in Montgomery form prior to being called
 */
void add_point_point(struct curve_point *p3, struct curve_point *p1, struct curve_point *p2, unsigned int num_limbs) {
    struct curve_point p_out;

    limb_t numer[num_limbs];
    limb_t denom[num_limbs];
    limb_t lambda[num_limbs];

    /* lambda = (y2 - y1) / (x2 - x1) */
    sub_mod_num_num(numer, p2->y, p1->y, m_glo, num_limbs);
    sub_mod_num_num(denom, p2->x, p1->x, m_glo, num_limbs);
    montgomery_inverse_num(denom, denom, m_glo, num_limbs);
    mul_montgomery_num_num(lambda, numer, denom, m_glo, m_prime_glo, num_limbs);

    /* x */
    mul_montgomery_num_num(p_out.x, lambda, lambda, m_glo, m_prime_glo, num_limbs);
    sub_mod_num_num(p_out.x, p_out.x, p1->x, m_glo, num_limbs);
    sub_mod_num_num(p_out.x, p_out.x, p2->x, m_glo, num_limbs);

    /* y */
    sub_mod_num_num(p_out.y, p1->x, p_out.x, m_glo, num_limbs);
    mul_montgomery_num_num(p_out.y, lambda, p_out.y, m_glo, m_prime_glo, num_limbs);
    sub_mod_num_num(p_out.y, p_out.y, p1->y, m_glo, num_limbs);

    copy_num(p3->x, p_out.x, num_limbs);
    copy_num(p3->y, p_out.y, num_limbs);
}

/**
 * Supposes data is in Montgomery form prior to being called
 */
void add_point_point_gmp(struct curve_point_gmp *p3, struct curve_point_gmp *p1, struct curve_point_gmp *p2) {
    gmp_int_t numer_gmp;
    gmp_int_t denom_gmp;
    gmp_int_t lambda_gmp;
    gmp_int_init(numer_gmp);
    gmp_int_init(denom_gmp);
    gmp_int_init(lambda_gmp);

    /* lambda = (y2 - y1) / (x2 - x1) */
    gmp_int_sub_mod(numer_gmp, p2->y, p1->y, m_glo_gmp);
    gmp_int_sub_mod(denom_gmp, p2->x, p1->x, m_glo_gmp);
    gmp_int_montgomery_inverse(denom_gmp, denom_gmp, m_glo_gmp);
    gmp_int_mul_montgomery(lambda_gmp, numer_gmp, denom_gmp, inv_R_glo_gmp, m_glo_gmp);

    /* x */
    gmp_int_mul_montgomery(p3->x, lambda_gmp, lambda_gmp, inv_R_glo_gmp, m_glo_gmp);
    gmp_int_sub_mod(p3->x, p3->x, p1->x, m_glo_gmp);
    gmp_int_sub_mod(p3->x, p3->x, p2->x, m_glo_gmp);

    /* y */
    gmp_int_sub_mod(p3->y, p1->x, p3->x, m_glo_gmp);
    gmp_int_mul_montgomery(p3->y, lambda_gmp, p3->y, inv_R_glo_gmp, m_glo_gmp);
    gmp_int_sub_mod(p3->y, p3->y, p1->y, m_glo_gmp);

    gmp_int_clear(numer_gmp);
    gmp_int_clear(denom_gmp);
    gmp_int_clear(lambda_gmp);
}

/**
 * Supposes data is in Montgomery form prior to being called
 */
void double_point(struct curve_point *p2, struct curve_point *p1, unsigned int num_limbs) {
    struct curve_point p_out;

    limb_t x1_squared[num_limbs];
    limb_t numer[num_limbs];
    limb_t denom[num_limbs];
    limb_t lambda[num_limbs];

    /* lambda = (3 * (x1^2) + a) / (2 * y1) */
    mul_montgomery_num_num(x1_squared, p1->x, p1->x, m_glo, m_prime_glo, num_limbs);
    add_mod_num_num(numer, x1_squared, x1_squared, m_glo, num_limbs);
    add_mod_num_num(numer, numer, x1_squared, m_glo, num_limbs);
    add_mod_num_num(numer, numer, a_glo, m_glo, num_limbs);
    add_mod_num_num(denom, p1->y, p1->y, m_glo, num_limbs);
    montgomery_inverse_num(denom, denom, m_glo, num_limbs);
    mul_montgomery_num_num(lambda, numer, denom, m_glo, m_prime_glo, num_limbs);

    /* x */
    mul_montgomery_num_num(p_out.x, lambda, lambda, m_glo, m_prime_glo, num_limbs);
    sub_mod_num_num(p_out.x, p_out.x, p1->x, m_glo, num_limbs);
    sub_mod_num_num(p_out.x, p_out.x, p1->x, m_glo, num_limbs);

    /* y */
    sub_mod_num_num(p_out.y, p1->x, p_out.x, m_glo, num_limbs);
    mul_montgomery_num_num(p_out.y, lambda, p_out.y, m_glo, m_prime_glo, num_limbs);
    sub_mod_num_num(p_out.y, p_out.y, p1->y, m_glo, num_limbs);

    copy_num(p2->x, p_out.x, num_limbs);
    copy_num(p2->y, p_out.y, num_limbs);
}

/**
 * Supposes data is in Montgomery form prior to being called
 */
void double_point_gmp(struct curve_point_gmp *p2, struct curve_point_gmp *p1) {
    gmp_int_t x1_squared_gmp;
    gmp_int_t numer_gmp;
    gmp_int_t denom_gmp;
    gmp_int_t lambda_gmp;
    gmp_int_init(x1_squared_gmp);
    gmp_int_init(numer_gmp);
    gmp_int_init(denom_gmp);
    gmp_int_init(lambda_gmp);

    /* lambda = (3 * (x1^2) + a) / (2 * y1) */
    gmp_int_mul_montgomery(x1_squared_gmp, p1->x, p1->x, inv_R_glo_gmp, m_glo_gmp);
    gmp_int_add_mod(numer_gmp, x1_squared_gmp, x1_squared_gmp, m_glo_gmp);
    gmp_int_add_mod(numer_gmp, numer_gmp, x1_squared_gmp, m_glo_gmp);
    gmp_int_add_mod(numer_gmp, numer_gmp, a_glo_gmp, m_glo_gmp);
    gmp_int_add_mod(denom_gmp, p1->y, p1->y, m_glo_gmp);
    gmp_int_montgomery_inverse(denom_gmp, denom_gmp, m_glo_gmp);
    gmp_int_mul_montgomery(lambda_gmp, numer_gmp, denom_gmp, inv_R_glo_gmp, m_glo_gmp);

    /* x */
    gmp_int_mul_montgomery(p2->x, lambda_gmp, lambda_gmp, inv_R_glo_gmp, m_glo_gmp);
    gmp_int_sub_mod(p2->x, p2->x, p1->x, m_glo_gmp);
    gmp_int_sub_mod(p2->x, p2->x, p1->x, m_glo_gmp);

    /* y */
    gmp_int_sub_mod(p2->y, p1->x, p2->x, m_glo_gmp);
    gmp_int_mul_montgomery(p2->y, lambda_gmp, p2->y, inv_R_glo_gmp, m_glo_gmp);
    gmp_int_sub_mod(p2->y, p2->y, p1->y, m_glo_gmp);

    gmp_int_clear(x1_squared_gmp);
    gmp_int_clear(numer_gmp);
    gmp_int_clear(denom_gmp);
    gmp_int_clear(lambda_gmp);
}

/* assumes input is in standard representation */
bool is_on_curve(limb_t *x_num, limb_t *y_num, unsigned int num_limbs) {
    gmp_int_t x_gmp;
    gmp_int_t y_gmp;
    gmp_int_init(x_gmp);
    gmp_int_init(y_gmp);

    convert_num_to_gmp(x_gmp, x_num, num_limbs);
    convert_num_to_gmp(y_gmp, y_num, num_limbs);

    bool is_on_curve = is_on_curve_gmp(x_gmp, y_gmp);

    gmp_int_clear(x_gmp);
    gmp_int_clear(y_gmp);

    return is_on_curve;
}

/* assumes input is in standard representation */
bool is_on_curve_point(struct curve_point p, unsigned int num_limbs) {
    return is_on_curve(p.x, p.y, num_limbs);
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

bool is_on_curve_point_gmp(struct curve_point_gmp p) {
    return is_on_curve_gmp(p.x, p.y);
}

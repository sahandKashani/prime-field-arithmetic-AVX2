#include <immintrin.h>
#include <stdbool.h>
#include <stdlib.h>
#include "arithmetic.h"
#include "constants.h"
#include "limb.h"
#include "utilities.h"
#include "settings.h"

limb_t add_num_num(limb_t *c, limb_t *a, limb_t *b, unsigned int num_limbs, limb_t carry_in) {
    limb_t carry_out = carry_in;

    for (unsigned int i = 0; i < num_limbs; i++) {
        // we need to temporarily store the output of each operation, because it
        // is possible that c is the same array as a or b.
        limb_t c_tmp = set_limb(0);

        #if FULL_LIMB_PRECISION

            // c_tmp = a[i] + carry_out;
            // carry_out = (c_tmp < a[i]);
            // c_tmp += b[i];
            // carry_out |= (c_tmp < b[i]);
            c_tmp = add_limb_limb(load_limb(a, i), carry_out);
            carry_out = cmpgt_limb_limb(load_limb(a, i), c_tmp);
            c_tmp = add_limb_limb(c_tmp, load_limb(b, i));
            carry_out = or_limb_limb(carry_out, cmpgt_limb_limb(load_limb(b, i), c_tmp));

        #else

            // c_tmp = a[i] + b[i] + carry_out;
            // carry_out = carry(c_tmp);
            // c_tmp = reduce_to_base(c_tmp);
            c_tmp = add_limb_limb(add_limb_limb(load_limb(a, i), load_limb(b, i)), carry_out);
            carry_out = carry(c_tmp);
            c_tmp = reduce_to_base(c_tmp);

        #endif

        // c[i] = c_tmp;
        store_limb(c, i, c_tmp);
    }

    return carry_out;
}

limb_t add_num_limb(limb_t *c, limb_t *a, limb_t b, unsigned int num_limbs, limb_t carry_in) {
    // we need to temporarily store the output of each operation, because it is
    // possible that c is the same array as a.
    limb_t c_tmp = set_limb(0);
    limb_t carry_out = set_limb(0);

    #if FULL_LIMB_PRECISION

        // c_tmp = a[0] + carry_in;
        // carry_out = (c_tmp < a[0]);
        // c_tmp += b;
        // carry_out |= (c_tmp < b);
        c_tmp = add_limb_limb(load_limb(a, 0), carry_in);
        carry_out = cmpgt_limb_limb(load_limb(a, 0), c_tmp);
        c_tmp = add_limb_limb(c_tmp, b);
        carry_out = or_limb_limb(carry_out, cmpgt_limb_limb(b, c_tmp));

    #else

        // c_tmp = a[0] + b + carry_in;
        // carry_out = carry(c_tmp);
        // c_tmp = reduce_to_base(c_tmp);
        c_tmp = add_limb_limb(add_limb_limb(load_limb(a, 0), b), carry_in);
        carry_out = carry(c_tmp);
        c_tmp = reduce_to_base(c_tmp);

    #endif

    // c[0] = c_tmp;
    store_limb(c, 0, c_tmp);

    for (unsigned int i = 1; i < num_limbs; i++) {
        // c_tmp = a[i] + carry_out;
        c_tmp = add_limb_limb(load_limb(a, i), carry_out);

        #if FULL_LIMB_PRECISION

            // carry_out = (c_tmp < a[i]);
            carry_out = cmpgt_limb_limb(load_limb(a, i), c_tmp);

        #else

            // carry_out = carry(c_tmp);
            // c_tmp = reduce_to_base(c_tmp);
            carry_out = carry(c_tmp);
            c_tmp = reduce_to_base(c_tmp);

        #endif

        // c[i] = c_tmp;
        store_limb(c, i, c_tmp);
    }

    return carry_out;
}

limb_t sub_num_num(limb_t *c, limb_t *a, limb_t *b, unsigned int num_limbs, limb_t borrow_in) {
    limb_t borrow_out = borrow_in;

    for (unsigned int i = 0; i < num_limbs; i++) {
        // we need to temporarily store the output of each operation, because it
        // is possible that c is the same array as a or b.
        limb_t c_tmp = set_limb(0);

        #if FULL_LIMB_PRECISION

            // limb_t c_tmp_old = 0;
            // c_tmp = a[i] - borrow_out;
            // c_tmp_old = c_tmp;
            // borrow_out = (c_tmp > a[i]);
            // c_tmp -= b[i];
            // borrow_out |= (c_tmp > c_tmp_old);
            limb_t c_tmp_old = set_limb(0);
            c_tmp = sub_limb_limb(load_limb(a, i), borrow_out);
            c_tmp_old = c_tmp;
            borrow_out = cmpgt_limb_limb(c_tmp, load_limb(a, i));
            c_tmp = sub_limb_limb(c_tmp, load_limb(b, i));
            borrow_out = or_limb_limb(borrow_out, cmpgt_limb_limb(c_tmp, c_tmp_old));

        #else

            // c_tmp = a[i] - b[i] - borrow_out;
            // borrow_out = carry(c_tmp);
            // c_tmp = reduce_to_base(c_tmp);
            c_tmp = sub_limb_limb(sub_limb_limb(load_limb(a, i), load_limb(b, i)), borrow_out);
            borrow_out = carry(c_tmp);
            c_tmp = reduce_to_base(c_tmp);

        #endif

        // c[i] = c_tmp;
        store_limb(c, i, c_tmp);
    }

    return borrow_out;
}

void mul_num_limb(limb_t * const c, limb_t const * const a, limb_t const b, unsigned int const num_limbs) {
//    limb_t res[num_limbs + 1];
//    clear_num(res, num_limbs + 1);
//
//    limb_t carry_out = 0;
//    for (unsigned int i = 0; i < num_limbs; i++) {
//        limb_t inner_product[2] = {0, 0};
//        mul_limb_limb(&inner_product[1], &inner_product[0], a[i], b);
//        carry_out = add(res + i, res + i, inner_product, 2, carry_out);
//    }
//
//    copy_num(c, res, num_limbs + 1);
}

void mul_num_num(limb_t * const c, limb_t const * const a, limb_t const * const b, unsigned int const num_limbs) {
//    limb_t res[2 * num_limbs];
//    clear_num(res, 2 * num_limbs);
//
//    for (unsigned int i = 0; i < num_limbs; i++) {
//        limb_t tmp[num_limbs + 1];
//        mul_num_limb(tmp, a, b[i], num_limbs);
//        add(res + i, res + i, tmp, num_limbs + 1, 0);
//    }
//
//    copy_num(c, res, 2 * num_limbs);
}

bool equals_zero(limb_t const * const num, unsigned int const num_limbs) {
//    for (unsigned int i = 0; i < num_limbs; i++) {
//        if (num[i] != 0) {
//            return false;
//        }
//    }
//    return true;
}

// returns -1 if a < b
// returns  0 if a == b
// returns +1 if a > b
int cmp_num_num(limb_t const * const a, limb_t const * const b, unsigned int const num_limbs) {
//    limb_t tmp[num_limbs];
//    limb_t borrow_out = sub(tmp, a, b, num_limbs, 0);
//
//    if (borrow_out) {
//        return -1;
//    } else if (equals_zero(tmp, num_limbs)) {
//        return 0;
//    } else {
//        return 1;
//    }
}

void and_num_num(limb_t * const c, limb_t const * const a, limb_t const * const b, unsigned int const num_limbs) {
//    for (unsigned int i = 0; i < num_limbs; i++) {
//        c[i] = a[i] & b[i];
//    }
}

void add_mod_num_num(limb_t * const c, limb_t const * const a, limb_t const * const b, limb_t const * const m, unsigned int const num_limbs) {
//    #if BRANCHLESS_MODULAR_ADDITION
//
//    limb_t mask[num_limbs];
//    clear_num(mask, num_limbs);
//
//    add(c, a, b, num_limbs, 0);
//    limb_t borrow_out = sub(c, c, m, num_limbs, 0);
//    sub(mask, mask, mask, num_limbs, borrow_out);
//    and(mask, m, mask, num_limbs);
//    add(c, c, mask, num_limbs, 0);
//
//    #else
//
//    add(c, a, b, num_limbs, 0);
//    if (cmp(c, m, num_limbs) >= 0) {
//        sub(c, c, m, num_limbs, 0);
//    }
//
//    #endif
}

void sub_mod_num_num(limb_t * const c, limb_t const * const a, limb_t const * const b, limb_t const * const m, unsigned int const num_limbs) {
//    #if BRANCHLESS_MODULAR_SUBTRACTION
//
//    limb_t mask[num_limbs];
//    clear_num(mask, num_limbs);
//
//    limb_t borrow_out = sub(c, a, b, num_limbs, 0);
//    sub(mask, mask, mask, num_limbs, borrow_out);
//    and(mask, m, mask, num_limbs);
//    add(c, c, mask, num_limbs, 0);
//
//    #else
//
//    unsigned int borrow_out = sub(c, a, b, num_limbs, 0);
//    if (borrow_out) {
//        add(c, c, m, num_limbs, 0);
//    }
//
//    #endif
}

void mul_montgomery_num_num(limb_t * const z, limb_t const * const x, limb_t const * const y, limb_t const * const m, limb_t m_prime, unsigned int const num_limbs) {
//    limb_t A[num_limbs + 1];
//    clear_num(A, num_limbs + 1);
//
//    for (unsigned int i = 0; i < num_limbs; i++) {
//        // u_i = (a_0 + (x_i * y_0)) * m' mod b
//        limb_t A0_Xi_Y0_Mprime = (A[0] + x[i] * y[0]) * m_prime;
//
//        #if FULL_LIMB_PRECISION
//
//        limb_t ui = A0_Xi_Y0_Mprime;
//
//        #else
//
//        limb_t ui = reduce_to_base(A0_Xi_Y0_Mprime);
//
//        #endif
//
//        // A = (A + (x_i * y) + (u_i * m)) / b
//
//        // x_i * y
//        limb_t xi_y[num_limbs + 1];
//        mul_num_limb(xi_y, y, x[i], num_limbs);
//
//        // u_i * m
//        limb_t ui_m[num_limbs + 1];
//        mul_num_limb(ui_m, m, ui, num_limbs);
//
//        // A = A + (x_i * y)
//        add(A, A, xi_y, num_limbs + 1, 0);
//
//        // A = A + (x_i * y) + (u_i * m)
//        add(A, A, ui_m, num_limbs + 1, 0);
//
//        // A = (A + (x_i * y) + (u_i * m)) / b
//        for (unsigned int j = 0; j < num_limbs; j++) {
//            A[j] = A[j + 1];
//        }
//        A[num_limbs] = 0;
//    }
//
//    #if BRANCHLESS_MONTGOMERY_MULTIPLICATION
//
//    sub_mod(A, A, m, m, num_limbs);
//
//    #else
//
//    // A[num_limbs] = 0, so it is like if A and m have the same number of limbs.
//    if (cmp(A, m, num_limbs) >= 0) {
//        sub(A, A, m, num_limbs, 0);
//    }
//
//    #endif
//
//    copy_num(z, A, num_limbs);
}

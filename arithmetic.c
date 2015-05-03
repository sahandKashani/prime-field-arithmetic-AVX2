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
        /* we need to temporarily store the output of each operation, because it
         * is possible that c is the same array as a or b.
         */
        limb_t c_tmp = set_limb(0);

        #if FULL_LIMB_PRECISION

            c_tmp = add_limb_limb(load_limb(a, i), carry_out);
            carry_out = cmpgt_limb_limb(load_limb(a, i), c_tmp);
            c_tmp = add_limb_limb(c_tmp, load_limb(b, i));
            carry_out = or_limb_limb(carry_out, cmpgt_limb_limb(load_limb(b, i), c_tmp));

        #else

            c_tmp = add_limb_limb(add_limb_limb(load_limb(a, i), load_limb(b, i)), carry_out);
            carry_out = carry(c_tmp);
            c_tmp = reduce_to_base_limb_t(c_tmp);

        #endif

        store_limb(c, i, c_tmp);
    }

    return carry_out;
}

limb_t add_num_limb(limb_t *c, limb_t *a, limb_t b, unsigned int num_limbs, limb_t carry_in) {
    /* we need to temporarily store the output of each operation, because it is
     * possible that c is the same array as a or b.
     */
    limb_t c_tmp = set_limb(0);
    limb_t carry_out = set_limb(0);

    #if FULL_LIMB_PRECISION

        c_tmp = add_limb_limb(load_limb(a, 0), carry_in);
        carry_out = cmpgt_limb_limb(load_limb(a, 0), c_tmp);
        c_tmp = add_limb_limb(c_tmp, b);
        carry_out = or_limb_limb(carry_out, cmpgt_limb_limb(b, c_tmp));

    #else

        c_tmp = add_limb_limb(add_limb_limb(load_limb(a, 0), b), carry_in);
        carry_out = carry(c_tmp);
        c_tmp = reduce_to_base_limb_t(c_tmp);

    #endif

    store_limb(c, 0, c_tmp);

    for (unsigned int i = 1; i < num_limbs; i++) {
        c_tmp = add_limb_limb(load_limb(a, i), carry_out);

        #if FULL_LIMB_PRECISION

            carry_out = cmpgt_limb_limb(load_limb(a, i), c_tmp);

        #else

            carry_out = carry(c_tmp);
            c_tmp = reduce_to_base_limb_t(c_tmp);

        #endif

        store_limb(c, i, c_tmp);
    }

    return carry_out;
}

limb_t sub_num_num(limb_t *c, limb_t *a, limb_t *b, unsigned int num_limbs, limb_t borrow_in) {
    limb_t borrow_out = borrow_in;

    for (unsigned int i = 0; i < num_limbs; i++) {
        /* we need to temporarily store the output of each operation, because it
         * is possible that c is the same array as a or b.
         */
        limb_t c_tmp = set_limb(0);

        #if FULL_LIMB_PRECISION

            limb_t c_tmp_old = set_limb(0);
            c_tmp = sub_limb_limb(load_limb(a, i), borrow_out);
            c_tmp_old = c_tmp;
            borrow_out = cmpgt_limb_limb(c_tmp, load_limb(a, i));
            c_tmp = sub_limb_limb(c_tmp, load_limb(b, i));
            borrow_out = or_limb_limb(borrow_out, cmpgt_limb_limb(c_tmp, c_tmp_old));

        #else

            c_tmp = sub_limb_limb(sub_limb_limb(load_limb(a, i), load_limb(b, i)), borrow_out);
            borrow_out = carry(c_tmp);
            c_tmp = reduce_to_base_limb_t(c_tmp);

        #endif

        store_limb(c, i, c_tmp);
    }

    return borrow_out;
}

void mul_num_limb(limb_t *c, limb_t *a, limb_t b, unsigned int num_limbs) {
    limb_t res[num_limbs + 1];
    clear_num(res, num_limbs + 1);

    limb_t carry_out = set_limb(0);
    for (unsigned int i = 0; i < num_limbs; i++) {
        struct d_limb_t tmp = mul_limb_limb(a[i], b);

        #if !FULL_LIMB_PRECISION

            tmp = reduce_to_base_d_limb_t(tmp);

        #endif

        limb_t inner_product[2] = {tmp.lo, tmp.hi};
        carry_out = add_num_num(res + i, res + i, inner_product, 2, carry_out);
    }

    copy_num(c, res, num_limbs + 1);
}

void mul_num_num(limb_t *c, limb_t *a, limb_t *b, unsigned int num_limbs) {
    limb_t res[2 * num_limbs];
    clear_num(res, 2 * num_limbs);

    for (unsigned int i = 0; i < num_limbs; i++) {
        limb_t tmp[num_limbs + 1];
        mul_num_limb(tmp, a, b[i], num_limbs);
        add_num_num(res + i, res + i, tmp, num_limbs + 1, set_limb(0));
    }

    copy_num(c, res, 2 * num_limbs);
}

bool equals_zero(limb_t *num, unsigned int num_limbs) {
    for (unsigned int i = 0; i < num_limbs; i++) {
        if (num[i] != 0) {
            return false;
        }
    }
    return true;
}

/* returns -1 if a < b
 * returns  0 if a == b
 * returns +1 if a > b
 */
int cmp_num_num(limb_t *a, limb_t *b, unsigned int num_limbs) {
    limb_t tmp[num_limbs];
    limb_t borrow_out = sub_num_num(tmp, a, b, num_limbs, set_limb(0));

    if (borrow_out) {
        return -1;
    } else if (equals_zero(tmp, num_limbs)) {
        return 0;
    } else {
        return 1;
    }
}

void and_num_num(limb_t *c, limb_t *a, limb_t *b, unsigned int num_limbs) {
    for (unsigned int i = 0; i < num_limbs; i++) {
        c[i] = and_limb_limb(load_limb(a, i), load_limb(b, i));
    }
}

void add_mod_num_num(limb_t *c, limb_t *a, limb_t *b, limb_t *m, unsigned int num_limbs) {
    limb_t mask[num_limbs];
    clear_num(mask, num_limbs);

    limb_t zero = set_limb(0);
    add_num_num(c, a, b, num_limbs, zero);
    limb_t borrow_out = sub_num_num(c, c, m, num_limbs, zero);
    sub_num_num(mask, mask, mask, num_limbs, borrow_out);
    and_num_num(mask, m, mask, num_limbs);
    add_num_num(c, c, mask, num_limbs, zero);
}

void sub_mod_num_num(limb_t *c, limb_t *a, limb_t *b, limb_t *m, unsigned int num_limbs) {
    limb_t mask[num_limbs];
    clear_num(mask, num_limbs);

    limb_t borrow_out = sub_num_num(c, a, b, num_limbs, 0);
    sub_num_num(mask, mask, mask, num_limbs, borrow_out);
    and_num_num(mask, m, mask, num_limbs);
    add_num_num(c, c, mask, num_limbs, 0);
}

void mul_montgomery_num_num(limb_t *z, limb_t *x, limb_t *y, limb_t *m, limb_t m_prime, unsigned int num_limbs) {
    limb_t A[num_limbs + 1];
    clear_num(A, num_limbs + 1);

    for (unsigned int i = 0; i < num_limbs; i++) {
        /* u_i = ((a_0 + (x_i * y_0)) * m') % b; */
         limb_t ui = (A[0] + x[i] * y[0]) * m_prime;

        #if !FULL_LIMB_PRECISION

            ui = reduce_to_base_limb_t(ui);

        #endif

        /* A = (A + (x_i * y) + (u_i * m)) / b; */

        /* x_i * y */
        limb_t xi_y[num_limbs + 1];
        mul_num_limb(xi_y, y, x[i], num_limbs);

        /* u_i * m */
        limb_t ui_m[num_limbs + 1];
        mul_num_limb(ui_m, m, ui, num_limbs);

        /* A = A + (x_i * y); */
        add_num_num(A, A, xi_y, num_limbs + 1, 0);

        /* A = A + (x_i * y) + (u_i * m); */
        add_num_num(A, A, ui_m, num_limbs + 1, 0);

        /* A = (A + (x_i * y) + (u_i * m)) / b; */
        for (unsigned int j = 0; j < num_limbs; j++) {
            A[j] = A[j + 1];
        }
        A[num_limbs] = 0;
    }

    sub_mod_num_num(A, A, m, m, num_limbs);
    copy_num(z, A, num_limbs);
}

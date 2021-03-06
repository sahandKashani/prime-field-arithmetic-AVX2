#include <immintrin.h>
#include <stdbool.h>
#include <stdlib.h>
#include "constants.h"
#include "limb.h"
#include "prime_field.h"
#include "utilities.h"
#include "settings.h"

void zero_num(limb_t *num, unsigned int num_limbs) {
    for (unsigned int i = 0; i < num_limbs; i++) {
        store_limb(num, i, zero());
    }
}

limb_t add_num_num(limb_t *c, limb_t *a, limb_t *b, unsigned int num_limbs, limb_t carry_in) {
    limb_t carry_out = carry_in;

    for (unsigned int i = 0; i < num_limbs; i++) {
        /* we need to temporarily store the output of each operation, because it
         * is possible that c is the same array as a or b.
         */
        limb_t c_tmp = zero();

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
    limb_t c_tmp = zero();
    limb_t carry_out = zero();

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
        limb_t c_tmp = zero();

        #if FULL_LIMB_PRECISION

            limb_t c_tmp_old = zero();
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
    zero_num(res, num_limbs + 1);

    limb_t carry_out = zero();
    for (unsigned int i = 0; i < num_limbs; i++) {
        struct d_limb_t tmp = mul_limb_limb(load_limb(a, i) , b);

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
    zero_num(res, 2 * num_limbs);

    for (unsigned int i = 0; i < num_limbs; i++) {
        limb_t tmp[num_limbs + 1];
        mul_num_limb(tmp, a, load_limb(b, i), num_limbs);
        add_num_num(res + i, res + i, tmp, num_limbs + 1, zero());
    }

    copy_num(c, res, 2 * num_limbs);
}

void and_num_num(limb_t *c, limb_t *a, limb_t *b, unsigned int num_limbs) {
    for (unsigned int i = 0; i < num_limbs; i++) {
        store_limb(c, i, and_limb_limb(load_limb(a, i), load_limb(b, i)));
    }
}

void add_mod_num_num(limb_t *c, limb_t *a, limb_t *b, limb_t *m, unsigned int num_limbs) {
    limb_t mask[num_limbs];
    zero_num(mask, num_limbs);

    add_num_num(c, a, b, num_limbs, zero());
    limb_t borrow_out = sub_num_num(c, c, m, num_limbs, zero());
    sub_num_num(mask, mask, mask, num_limbs, borrow_out);
    and_num_num(mask, m, mask, num_limbs);
    add_num_num(c, c, mask, num_limbs, zero());
}

void sub_mod_num_num(limb_t *c, limb_t *a, limb_t *b, limb_t *m, unsigned int num_limbs) {
    limb_t mask[num_limbs];
    zero_num(mask, num_limbs);

    limb_t borrow_out = sub_num_num(c, a, b, num_limbs, zero());
    sub_num_num(mask, mask, mask, num_limbs, borrow_out);
    and_num_num(mask, m, mask, num_limbs);
    add_num_num(c, c, mask, num_limbs, zero());
}

void mul_montgomery_num_num(limb_t *z, limb_t *x, limb_t *y, limb_t *m, limb_t m_prime, unsigned int num_limbs) {
    limb_t A[num_limbs + 1];
    zero_num(A, num_limbs + 1);

    for (unsigned int i = 0; i < num_limbs; i++) {
        /* u_i = ((a_0 + (x_i * y_0)) * m') % b; */
        struct d_limb_t tmp = mul_limb_limb(load_limb(x, i), load_limb(y, 0));
        limb_t ui = tmp.lo;
        ui = add_limb_limb(ui, load_limb(A, 0));
        tmp = mul_limb_limb(ui, m_prime);
        ui = tmp.lo;

        #if !FULL_LIMB_PRECISION

            ui = reduce_to_base_limb_t(ui);

        #endif

        /* A = (A + (x_i * y) + (u_i * m)) / b; */
        /* x_i * y */
        limb_t xi_y[num_limbs + 1];
        mul_num_limb(xi_y, y, load_limb(x, i), num_limbs);

        /* u_i * m */
        limb_t ui_m[num_limbs + 1];
        mul_num_limb(ui_m, m, ui, num_limbs);

        /* A = A + (x_i * y); */
        add_num_num(A, A, xi_y, num_limbs + 1, zero());

        /* A = A + (x_i * y) + (u_i * m); */
        add_num_num(A, A, ui_m, num_limbs + 1, zero());

        /* A = (A + (x_i * y) + (u_i * m)) / b; */
        for (unsigned int j = 0; j < num_limbs; j++) {
            store_limb(A, j, load_limb(A, j + 1));
        }
        store_limb(A, num_limbs, zero());
    }

    sub_mod_num_num(A, A, m, m, num_limbs);
    copy_num(z, A, num_limbs);
}

void montgomery_inverse_num(limb_t *b, limb_t *a, limb_t *m, unsigned int num_limbs) {
    gmp_int_t a_gmp;
    gmp_int_t m_gmp;

    gmp_int_init(a_gmp);
    gmp_int_init(m_gmp);

    convert_num_to_gmp(a_gmp, a, num_limbs);
    convert_num_to_gmp(m_gmp, m, num_limbs);

    gmp_int_montgomery_inverse(a_gmp, a_gmp, m_gmp);

    convert_gmp_to_num(b, a_gmp, num_limbs);

    gmp_int_clear(a_gmp);
    gmp_int_clear(m_gmp);
}

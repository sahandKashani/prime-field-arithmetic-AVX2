#include <immintrin.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include "constants.h"
#include "utilities.h"
#include "prime_field_arithmetic.h"

unsigned int add(uint64_t * const c, uint64_t const * const a, uint64_t const * const b, unsigned int const num_limbs, unsigned int const carry_in) {
    unsigned int carry_out = carry_in;

    for (unsigned int i = 0; i < num_limbs; i++) {
        // we need to temporarily store the output of each operation, because it is
        // possible that c is the same array as a or b.
        uint64_t c_tmp = 0;

#if FULL_LIMB_PRECISION
        c_tmp = a[i] + carry_out;
        carry_out = (c_tmp < a[i]);
        c_tmp += b[i];
        carry_out |= (c_tmp < b[i]);
        c[i] = c_tmp;
#else
        c_tmp = a[i] + b[i] + carry_out;
        carry_out = carry(c_tmp);
        c_tmp = reduce_to_base(c_tmp);
        c[i] = c_tmp;
#endif
    }

    return carry_out;
}

unsigned int add_num_limb(uint64_t * const c, uint64_t const * const a, uint64_t const b, unsigned int const num_limbs, unsigned int const carry_in) {
    // we need to temporarily store the output of each operation, because it is
    // possible that c is the same array as a.
    uint64_t c_tmp = 0;
    unsigned int carry_out = 0;

#if FULL_LIMB_PRECISION
    c_tmp = a[0] + carry_in;
    carry_out = (c_tmp < a[0]);
    c_tmp += b;
    carry_out |= (c_tmp < b);
    c[0] = c_tmp;
#else
    c_tmp = a[0] + b + carry_in;
    carry_out = carry(c_tmp);
    c_tmp = reduce_to_base(c_tmp);
    c[0] = c_tmp;
#endif

    for (unsigned int i = 1; i < num_limbs; i++) {
#if FULL_LIMB_PRECISION
        c_tmp = a[i] + carry_out;
        carry_out = (c_tmp < a[i]);
        c[i] = c_tmp;
#else
        c_tmp = a[i] + carry_out;
        carry_out = carry(c_tmp);
        c_tmp = reduce_to_base(c_tmp);
        c[i] = c_tmp;
#endif
    }

    return carry_out;
}

unsigned int sub(uint64_t * const c, uint64_t const * const a, uint64_t const * const b, unsigned int const num_limbs, unsigned int const borrow_in) {
    // we need to temporarily store the output of each operation, because it is
    // possible that c is the same array as a or b.
    uint64_t c_tmp = 0;
    unsigned int borrow_out = borrow_in;

    for (unsigned int i = 0; i < num_limbs; i++) {
#if FULL_LIMB_PRECISION
        uint64_t c_tmp_old = 0;

        c_tmp = a[i] - borrow_out;
        c_tmp_old = c_tmp;
        borrow_out = (c_tmp > a[i]);
        c_tmp -= b[i];
        borrow_out |= (c_tmp > c_tmp_old);
        c[i] = c_tmp;
#else
        c_tmp = a[i] - b[i] - borrow_out;
        borrow_out = carry(c_tmp);
        c_tmp = reduce_to_base(c_tmp);
        c[i] = c_tmp;
#endif
    }

    return borrow_out;
}

void mul_limb_limb(uint64_t * const c_hi, uint64_t * const c_lo, uint64_t const a, uint64_t const b) {
#if MULX
    unsigned long long x = a;
    unsigned long long y = b;
    unsigned long long hi;
    unsigned long long lo;
    lo = _mulx_u64(x, y, &hi);
    *c_hi = hi;
    *c_lo = lo;
#else
    uint32_t a_32[2] = {a & 0xffffffff, (uint32_t) (a >> 32)};
    uint32_t b_32[2] = {b & 0xffffffff, (uint32_t) (b >> 32)};
    uint32_t c_32[4] = {0, 0, 0, 0};

    uint64_t inner_product = 0;
    uint32_t inner_product_lo = 0;
    uint32_t inner_product_hi = 0;

    for (unsigned int i = 0; i < 2; i++) {
        inner_product_hi = 0;
        for (unsigned int j = 0; j < 2; j++) {
            inner_product = c_32[i + j] + (((uint64_t) a_32[i]) * b_32[j]) + inner_product_hi;
            inner_product_lo = inner_product & (0xffffffff);
            inner_product_hi = (uint32_t) (inner_product >> 32);
            c_32[i + j] = inner_product_lo;
        }
        c_32[i + 2] = inner_product_hi;
    }

    *c_lo = (((uint64_t) c_32[1]) << 32) + c_32[0];
    *c_hi = (((uint64_t) c_32[3]) << 32) + c_32[2];
#endif

#if !FULL_LIMB_PRECISION
    *c_hi <<= (LIMB_SIZE_IN_BITS - BASE_EXPONENT);
    *c_hi |= (*c_lo >> BASE_EXPONENT);
    *c_lo = reduce_to_base(*c_lo);
#endif
}

void mul_num_limb(uint64_t * const c, uint64_t const * const a, uint64_t const b, unsigned int const num_limbs) {
    uint64_t res[num_limbs + 1];
    clear_num(res, num_limbs + 1);

    uint64_t inner_product[2] = {0, 0};
    unsigned int carry_out = 0;
    for (unsigned int i = 0; i < num_limbs; i++) {
        mul_limb_limb(&inner_product[1], &inner_product[0], a[i], b);
        carry_out = add(res + i, res + i, inner_product, 2, carry_out);
    }

    copy_num(c, res, num_limbs + 1);
}

void mul(uint64_t * const c, uint64_t const * const a, uint64_t const * const b, unsigned int const num_limbs) {
    uint64_t res[2 * num_limbs];
    clear_num(res, 2 * num_limbs);

    for (unsigned int i = 0; i < num_limbs; i++) {
        uint64_t tmp[num_limbs + 1];
        mul_num_limb(tmp, a, b[i], num_limbs);
        add(res + i, res + i, tmp, num_limbs + 1, 0);
    }

    copy_num(c, res, 2 * num_limbs);
}

bool equals_zero(uint64_t const * const num, unsigned int const num_limbs) {
    for (unsigned int i = 0; i < num_limbs; i++) {
        if (num[i] != 0) {
            return false;
        }
    }
    return true;
}

// returns -1 if a < b
// returns  0 if a == b
// returns +1 if a > b
int cmp(uint64_t const * const a, uint64_t const * const b, unsigned int const num_limbs) {
    uint64_t tmp[num_limbs];
    unsigned int borrow_out = sub(tmp, a, b, num_limbs, 0);

    if (borrow_out) {
        return -1;
    } else if (equals_zero(tmp, num_limbs)) {
        return 0;
    } else {
        return 1;
    }
}

void and(uint64_t * const c, uint64_t const * const a, uint64_t const * const b, unsigned int const num_limbs) {
    for (unsigned int i = 0; i < num_limbs; i++) {
        c[i] = a[i] & b[i];
    }
}

void add_mod(uint64_t * const c, uint64_t const * const a, uint64_t const * const b, uint64_t const * const m, unsigned int const num_limbs) {
#if BRANCHLESS_MODULAR_ADDITION
    uint64_t mask[num_limbs];
    clear_num(mask, num_limbs);

    add(c, a, b, num_limbs, 0);
    unsigned int borrow_out = sub(c, c, m, num_limbs, 0);
    sub(mask, mask, mask, num_limbs, borrow_out);
    and(mask, m, mask, num_limbs);
    add(c, c, mask, num_limbs, 0);
#else
    add(c, a, b, num_limbs, 0);
    if (cmp(c, m, num_limbs) >= 0) {
        sub(c, c, m, num_limbs, 0);
    }
#endif
}

void sub_mod(uint64_t * const c, uint64_t const * const a, uint64_t const * const b, uint64_t const * const m, unsigned int const num_limbs) {
#if BRANCHLESS_MODULAR_SUBTRACTION
    uint64_t mask[num_limbs];
    clear_num(mask, num_limbs);

    unsigned int borrow_out = sub(c, a, b, num_limbs, 0);
    sub(mask, mask, mask, num_limbs, borrow_out);
    and(mask, m, mask, num_limbs);
    add(c, c, mask, num_limbs, 0);
#else
    unsigned int borrow_out = sub(c, a, b, num_limbs, 0);
    if (borrow_out) {
        add(c, c, m, num_limbs, 0);
    }
#endif
}

void mul_montgomery(uint64_t * const z, uint64_t const * const x, uint64_t const * const y, uint64_t const * const m, uint64_t m_prime, unsigned int const num_limbs) {
    uint64_t A[num_limbs + 1];
    clear_num(A, num_limbs + 1);

    for (unsigned int i = 0; i < num_limbs; i++) {
        // u_i = (a_0 + (x_i * y_0)) * m' mod b
#if FULL_LIMB_PRECISION
        uint64_t ui = (A[0] + x[i] * y[0]) * m_prime;
#else
        uint64_t ui = reduce_to_base((A[0] + x[i] * y[0]) * m_prime);
#endif

        // A = (A + (x_i * y) + (u_i * m)) / b

        // x_i * y
        uint64_t xi_y[num_limbs + 1];
        mul_num_limb(xi_y, y, x[i], num_limbs);

        // u_i * m
        uint64_t ui_m[num_limbs + 1];
        mul_num_limb(ui_m, m, ui, num_limbs);

        // A = A + (x_i * y)
        add(A, A, xi_y, num_limbs + 1, 0);

        // A = A + (x_i * y) + (u_i * m)
        add(A, A, ui_m, num_limbs + 1, 0);

        // A = (A + (x_i * y) + (u_i * m)) / b
        for (unsigned int j = 0; j < num_limbs; j++) {
            A[j] = A[j + 1];
        }
        A[num_limbs] = 0;
    }

#if BRANCHLESS_MONTGOMERY_MULTIPLICATION
    sub_mod(A, A, m, m, num_limbs);
#else
    // A[num_limbs] = 0, so it is like if A and m have the same number of limbs.
    if (cmp(A, m, num_limbs) >= 0) {
        sub(A, A, m, num_limbs, 0);
    }
#endif

    copy_num(z, A, num_limbs);
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

//void add_vector(uint64_t (*c)[4], uint64_t const * const a, uint64_t const * const b, uint64_t * const carry, unsigned int const num_limbs) {
//  __m256i x = _mm256_lddqu_si256((__m256i *) a);
//  __m256i y = _mm256_lddqu_si256((__m256i *) b);
//  __m256i z = _mm256_lddqu_si256((__m256i *) a);
//
//  unsigned int carry_out = carry_in;
//
//    for (unsigned int i = 0; i < num_limbs; i++) {
//      // we need to temporarily store the output of each operation, because it is
//      // possible that c is the same array as a or b.
//      uint64_t c_tmp = 0;
//
//        c_tmp = a[i] + carry_out;
//        carry_out = (c_tmp < a[i]);
//        c_tmp += b[i];
//        carry_out |= (c_tmp < b[i]);
//        c[i] = c_tmp;
//    }
//
//    return carry_out;
//}

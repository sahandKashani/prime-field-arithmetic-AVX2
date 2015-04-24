#include <immintrin.h>
#include "constants.h"
#include "arithmetic_vector.h"
#include "limb.h"
#include "settings.h"
#include "utilities.h"

#if !FULL_LIMB_PRECISION

limb_vec_t carry_vector(limb_vec_t limb) {
    limb_vec_t mask = set_vector(0x1);
    limb_vec_t tmp = srli_vector(limb, BASE_EXPONENT);
    return and_vector(tmp, mask);
}

limb_vec_t reduce_to_base_vector(limb_vec_t limb) {
    limb_vec_t mask = set_vector((limb_t) -1);
    mask = srli_vector(mask, NUM_EXCESS_BASE_BITS);
    return and_vector(limb, mask);
}

limb_vec_t excess_base_bits_vector(limb_vec_t limb) {
    limb_vec_t mask = set_vector((limb_t) -1);
    mask = srli_vector(mask, NUM_EXCESS_BASE_BITS);
    limb = srli_vector(limb, BASE_EXPONENT);
    return and_vector(limb, mask);
}

#endif

limb_vec_t srli_vector(limb_vec_t a, int amount) {
    #if LIMB_SIZE_IN_BITS == 32

    return _mm256_srli_epi32(a, amount);

    #elif LIMB_SIZE_IN_BITS == 64

    return _mm256_srli_epi64(a, amount);

    #endif
}

limb_vec_t set_vector(limb_t a) {
    #if LIMB_SIZE_IN_BITS == 32

    return _mm256_set1_epi32((int) a);

    #elif LIMB_SIZE_IN_BITS == 64

    return _mm256_set1_epi64x((long long int) a);

    #endif
}

limb_vec_t add_vector(limb_vec_t a, limb_vec_t b) {
    #if LIMB_SIZE_IN_BITS == 32

    return _mm256_add_epi32(a, b);

    #elif LIMB_SIZE_IN_BITS == 64

    return _mm256_add_epi64(a, b);

    #endif
}

limb_vec_t sub_vector(limb_vec_t a, limb_vec_t b) {
    #if LIMB_SIZE_IN_BITS == 32

    return _mm256_sub_epi32(a, b);

    #elif LIMB_SIZE_IN_BITS == 64

    return _mm256_sub_epi64(a, b);

    #endif
}

limb_vec_t cmpgt_vector(limb_vec_t a, limb_vec_t b) {
    limb_vec_t tmp;
    limb_vec_t mask = set_vector(0x1);

    #if LIMB_SIZE_IN_BITS == 32

    tmp = _mm256_cmpgt_epi32(a, b);

    #elif LIMB_SIZE_IN_BITS == 64

    tmp = _mm256_cmpgt_epi64(a, b);

    #endif

    // we apply a mask because _mm256_cmpgt_epixx returns 0xff..ff or 0x00..00,
    // but we want to have only 0x1 or 0x0 as a result.
    return and_vector(tmp, mask);
}

limb_vec_t load_vector(limb_vec_t const *addr) {
    return _mm256_load_si256(addr);
}

limb_vec_t zero_vector() {
    return _mm256_setzero_si256();
}

limb_vec_t or_vector(limb_vec_t a, limb_vec_t b) {
    return _mm256_or_si256(a, b);
}

limb_vec_t and_vector(limb_vec_t a, limb_vec_t b) {
    return _mm256_and_si256(a, b);
}

void store_vector(limb_vec_t * const addr, limb_vec_t data) {
    _mm256_storeu_si256(addr, data);
}

limb_vec_t add_simd(limb_vec_t * const c, limb_vec_t const * const a, limb_vec_t const * const b, unsigned int const num_limbs, limb_vec_t const carry_in) {
    limb_vec_t carry_out = carry_in;

    for (unsigned int i = 0; i < num_limbs; i++) {
        // we need to temporarily store the output of each operation, because it
        // is possible that c is the same array as a or b.
        limb_vec_t c_tmp = zero_vector();

        limb_vec_t a_i = load_vector(a + i);
        limb_vec_t b_i = load_vector(b + i);

        #if FULL_LIMB_PRECISION

        c_tmp = add_vector(a_i, carry_out);
        carry_out = cmpgt_vector(a_i, c_tmp);
        c_tmp = add_vector(c_tmp, b_i);
        carry_out = or_vector(carry_out, cmpgt_vector(b_i, c_tmp));

        #else

        c_tmp = add_vector(a_i, add_vector(b_i, carry_out));
        carry_out = carry_vector(c_tmp);
        c_tmp = reduce_to_base_vector(c_tmp);

        #endif

        store_vector(c + i, c_tmp);
    }

    return carry_out;
}

limb_vec_t add_num_limb_simd(limb_vec_t * const c, limb_vec_t const * const a, limb_vec_t const b, unsigned int const num_limbs, limb_vec_t const carry_in) {
    // we need to temporarily store the output of each operation, because it is
    // possible that c is the same array as a.
    limb_vec_t c_tmp = zero_vector();
    limb_vec_t carry_out = zero_vector();

    limb_vec_t a_0 = load_vector(a);

    #if FULL_LIMB_PRECISION

    c_tmp = add_vector(a_0, carry_in);
    carry_out = cmpgt_vector(a_0, c_tmp);
    c_tmp = add_vector(c_tmp, b);
    carry_out = or_vector(carry_out, cmpgt_vector(b, c_tmp));

    #else

    c_tmp = add_vector(a_0, add_vector(b, carry_in));
    carry_out = carry_vector(c_tmp);
    c_tmp = reduce_to_base_vector(c_tmp);

    #endif

    store_vector(c, c_tmp);

    for (unsigned int i = 1; i < num_limbs; i++) {
        limb_vec_t a_i = load_vector(a + i);

        c_tmp = add_vector(a_i, carry_out);

        #if FULL_LIMB_PRECISION

        carry_out = cmpgt_vector(a_i, c_tmp);

        #else

        carry_out = carry_vector(c_tmp);
        c_tmp = reduce_to_base_vector(c_tmp);

        #endif

        store_vector(c + i, c_tmp);
    }

    return carry_out;
}

limb_vec_t sub_simd(limb_vec_t * const c, limb_vec_t const * const a, limb_vec_t const * const b, unsigned int const num_limbs, limb_vec_t const borrow_in) {
    limb_vec_t borrow_out = borrow_in;

    for (unsigned int i = 0; i < num_limbs; i++) {
        // we need to temporarily store the output of each operation, because it
        // is possible that c is the same array as a or b.
        limb_vec_t c_tmp = zero_vector();

        limb_vec_t a_i = load_vector(a + i);
        limb_vec_t b_i = load_vector(b + i);

        #if FULL_LIMB_PRECISION

        limb_vec_t c_tmp_old = zero_vector();
        c_tmp = sub_vector(a_i, borrow_out);
        c_tmp_old = c_tmp;
        borrow_out = cmpgt_vector(c_tmp, a_i);
        c_tmp = sub_vector(c_tmp, b_i);
        borrow_out = or_vector(borrow_out, cmpgt_vector(c_tmp, c_tmp_old));

        #else

        c_tmp = sub_vector(a_i, sub_vector(b_i, borrow_out));
        borrow_out = carry_vector(c_tmp);
        c_tmp = reduce_to_base_vector(c_tmp);

        #endif

        store_vector(c + i, c_tmp);
    }

    return borrow_out;
}

void mul_limb_limb_simd(limb_vec_t * const c_hi, limb_vec_t * const c_lo, limb_vec_t const a, limb_vec_t const b) {
    #if LIMB_SIZE_IN_BITS == 32

    uint64_t res = (uint64_t) a * b;
    *c_lo = res & ((uint32_t) -1);
    *c_hi = (uint32_t) (res >> 32);

    #elif LIMB_SIZE_IN_BITS == 64

    // -1 = 0xff..ff
    uint32_t a_32[2] = {a & ((uint32_t) -1), (uint32_t) (a >> 32)};
    uint32_t b_32[2] = {b & ((uint32_t) -1), (uint32_t) (b >> 32)};
    uint32_t c_32[4] = {0, 0, 0, 0};

    uint64_t inner_product = 0;
    uint32_t inner_product_lo = 0;
    uint32_t inner_product_hi = 0;

    for (unsigned int i = 0; i < 2; i++) {
        inner_product_hi = 0;
        for (unsigned int j = 0; j < 2; j++) {
            inner_product = c_32[i + j] + (((uint64_t) a_32[i]) * b_32[j]) + inner_product_hi;
            inner_product_lo = inner_product & ((uint32_t) -1);
            inner_product_hi = (uint32_t) (inner_product >> 32);
            c_32[i + j] = inner_product_lo;
        }
        c_32[i + 2] = inner_product_hi;
    }

    *c_lo = (((uint64_t) c_32[1]) << 32) + c_32[0];
    *c_hi = (((uint64_t) c_32[3]) << 32) + c_32[2];

    #endif // LIMB_SIZE_IN_BITS

    #if !FULL_LIMB_PRECISION

    *c_hi <<= NUM_EXCESS_BASE_BITS;
    *c_hi |= excess_base_bits(*c_lo);
    *c_lo = reduce_to_base(*c_lo);

    #endif
}

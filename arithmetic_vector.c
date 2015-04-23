#include <immintrin.h>
#include "constants.h"
#include "arithmetic_vector.h"
#include "limb.h"
#include "settings.h"
#include "utilities.h"

#if !FULL_LIMB_PRECISION

limb_vec_t carry_vector(limb_vec_t limb) {
    // return (unsigned int) (limb >> BASE_EXPONENT) & 0x1;
    limb_vec_t mask = set_vector(0x1);
    limb_vec_t tmp = srli_vector(limb, BASE_EXPONENT);
    return and_vector(tmp, mask);
}

limb_vec_t reduce_to_base_vector(limb_vec_t limb) {
    // return limb & (((limb_t) -1) >> (LIMB_SIZE_IN_BITS - BASE_EXPONENT));
    limb_vec_t mask = set_vector((limb_t) -1);
    mask = srli_vector(mask, LIMB_SIZE_IN_BITS - BASE_EXPONENT);
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

limb_vec_t cmpgt_vector(limb_vec_t a, limb_vec_t b) {
    limb_vec_t tmp;
    limb_vec_t mask = set_vector(0x1);

    #if LIMB_SIZE_IN_BITS == 32

    tmp = _mm256_cmpgt_epi32(a, b);

    #elif LIMB_SIZE_IN_BITS == 64

    tmp = _mm256_cmpgt_epi64(a, b);

    #endif

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
        // limb_t c_tmp = 0;
        limb_vec_t c_tmp = zero_vector();

        limb_vec_t a_i = load_vector(a + i);
        limb_vec_t b_i = load_vector(b + i);

        #if FULL_LIMB_PRECISION

        // c_tmp = a[i] + carry_out;
        c_tmp = add_vector(a_i, carry_out);

        // carry_out = (c_tmp < a[i]);
        carry_out = cmpgt_vector(a_i, c_tmp);

        // c_tmp += b[i];
        c_tmp = add_vector(c_tmp, b_i);

        // carry_out |= (c_tmp < b[i]);
        carry_out = or_vector(carry_out, cmpgt_vector(b_i, c_tmp));

        #else

        // c_tmp = a[i] + b[i] + carry_out;
        c_tmp = add_vector(a_i, add_vector(b_i, carry_out));

        // carry_out = carry(c_tmp);
        carry_out = carry_vector(c_tmp);

        // c_tmp = reduce_to_base(c_tmp);
        c_tmp = reduce_to_base_vector(c_tmp);

        #endif

        store_vector(c + i, c_tmp);
    }

    return carry_out;
}

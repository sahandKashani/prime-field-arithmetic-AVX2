#include <immintrin.h>
#include "constants.h"
#include "settings.h"
#include "limb.h"
#include "arithmetic_vector.h"

//unsigned int add(limb_t * const c, limb_t const * const a, limb_t const * const b, unsigned int const num_limbs, unsigned int const carry_in) {
//    unsigned int carry_out = carry_in;
//
//    for (unsigned int i = 0; i < num_limbs; i++) {
//        // we need to temporarily store the output of each operation, because it
//        // is possible that c is the same array as a or b.
//        limb_t c_tmp = 0;
//
//        #if FULL_LIMB_PRECISION
//
//        c_tmp = a[i] + carry_out;
//        carry_out = (c_tmp < a[i]);
//        c_tmp += b[i];
//        carry_out |= (c_tmp < b[i]);
//
//        #else
//
//        c_tmp = a[i] + b[i] + carry_out;
//        carry_out = carry(c_tmp);
//        c_tmp = reduce_to_base(c_tmp);
//
//        #endif
//
//        c[i] = c_tmp;
//    }
//
//    return carry_out;
//}

unsigned int add_simd(limb_vec_t * const c, limb_vec_t const * const a, limb_vec_t const * const b, unsigned int const num_limbs, limb_vec_t const carry_in) {
    __m256i carry_out = carry_in;

    for (unsigned int i = 0; i < num_limbs; i++) {
        // we need to temporarily store the output of each operation, because it
        // is possible that c is the same array as a or b.
        limb_vec_t c_tmp = _mm256_setzero_si256();

        limb_vec_t a_i = _mm256_load_si256(a + i);
        limb_vec_t b_i = _mm256_load_si256(b + i);

        #if FULL_LIMB_PRECISION

        c_tmp = _mm256_add_epi32(a_i, carry_out);
        carry_out = _mm256_cmpgt_epi32(a_i, c_tmp);
        c_tmp = _mm256_add_epi32(c_tmp, b_i);
//        carry_out = _mm256_or_si256();

        #else


        #endif

    }

}

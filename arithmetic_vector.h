#ifndef ARITHMETIC_VECTOR_H_
#define ARITHMETIC_VECTOR_H_

#include "limb.h"

#if !FULL_LIMB_PRECISION

limb_vec_t carry_vector(limb_vec_t limb);
limb_vec_t reduce_to_base_vector(limb_vec_t limb);
limb_vec_t excess_base_bits_vector(limb_vec_t limb);

#endif

limb_vec_t srli_vector(limb_vec_t a, int amount);
limb_vec_t set_vector(limb_t a);
limb_vec_t add_vector(limb_vec_t a, limb_vec_t b);
limb_vec_t cmpgt_vector(limb_vec_t a, limb_vec_t b);
limb_vec_t load_vector(limb_vec_t const *addr);
limb_vec_t zero_vector();
limb_vec_t or_vector(limb_vec_t a, limb_vec_t b);
limb_vec_t and_vector(limb_vec_t a, limb_vec_t b);
void store_vector(limb_vec_t * const addr, limb_vec_t data);

limb_vec_t add_simd(limb_vec_t * const c, limb_vec_t const * const a, limb_vec_t const * const b, unsigned int const num_limbs, limb_vec_t const carry_in);
limb_vec_t add_num_limb_simd(limb_vec_t * const c, limb_vec_t const * const a, limb_vec_t const b, unsigned int const num_limbs, limb_vec_t const carry_in);

#endif

#ifndef ARITHMETIC_H_
#define ARITHMETIC_H_

#include <stdbool.h>
#include "limb.h"

#if !FULL_LIMB_PRECISION

limb_t carry(limb_t limb);
limb_t reduce_to_base(limb_t limb);
limb_t excess_base_bits(limb_t limb);

#endif

limb_t add(limb_t * const c, limb_t const * const a, limb_t const * const b, unsigned int const num_limbs, limb_t const carry_in);
limb_t add_num_limb(limb_t * const c, limb_t const * const a, limb_t const b, unsigned int const num_limbs, limb_t const carry_in);
limb_t sub(limb_t * const c, limb_t const * const a, limb_t const * const b, unsigned int const num_limbs, limb_t const borrow_in);
void mul_limb_limb(limb_t * const c_hi, limb_t * const c_lo, limb_t const a, limb_t const b);
void mul_num_limb(limb_t * const c, limb_t const * const a, limb_t const b, unsigned int const num_limbs);
void mul(limb_t * const c, limb_t const * const a, limb_t const * const b, unsigned int const num_limbs);
bool equals_zero(limb_t const * const num, unsigned int const num_limbs);
int cmp(limb_t const * const a, limb_t const * const b, unsigned int const num_limbs);
void and(limb_t * const c, limb_t const * const a, limb_t const * const b, unsigned int const num_limbs);
void add_mod(limb_t * const c, limb_t const * const a, limb_t const * const b, limb_t const * const m, unsigned int const num_limbs);
void sub_mod(limb_t * const c, limb_t const * const a, limb_t const * const b, limb_t const * const m, unsigned int const num_limbs);
void mul_montgomery(limb_t * const z, limb_t const * const x, limb_t const * const y, limb_t const * const m, limb_t m_prime, unsigned int const num_limbs);

#endif

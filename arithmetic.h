#ifndef ARITHMETIC_H_
#define ARITHMETIC_H_

#include <stdbool.h>
#include "limb.h"

#if !FULL_LIMB_PRECISION

unsigned int carry(limb_t limb);
limb_t reduce_to_base(limb_t limb);

#endif

unsigned int add(limb_t * const c, limb_t const * const a, limb_t const * const b, unsigned int const num_limbs, unsigned int const carry_in);
unsigned int add_num_limb(limb_t * const c, limb_t const * const a, limb_t const b, unsigned int const num_limbs, unsigned int const carry_in);
unsigned int sub(limb_t * const c, limb_t const * const a, limb_t const * const b, unsigned int const num_limbs, unsigned int const borrow_in);
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

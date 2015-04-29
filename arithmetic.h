#ifndef ARITHMETIC_H_
#define ARITHMETIC_H_

#include <stdbool.h>
#include "limb.h"

limb_t add_num_num(limb_t *c, limb_t *a, limb_t *b, unsigned int num_limbs, limb_t carry_in);
limb_t add_num_limb(limb_t *c, limb_t *a, limb_t b, unsigned int num_limbs, limb_t carry_in);
limb_t sub_num_num(limb_t *c, limb_t *a, limb_t *b, unsigned int num_limbs, limb_t borrow_in);
void mul_num_limb(limb_t * const c, limb_t const * const a, limb_t const b, unsigned int const num_limbs);
void mul_num_num(limb_t * const c, limb_t const * const a, limb_t const * const b, unsigned int const num_limbs);
bool equals_zero(limb_t const * const num, unsigned int const num_limbs);
int cmp_num_num(limb_t const * const a, limb_t const * const b, unsigned int const num_limbs);
void and_num_num(limb_t * const c, limb_t const * const a, limb_t const * const b, unsigned int const num_limbs);
void add_mod_num_num(limb_t * const c, limb_t const * const a, limb_t const * const b, limb_t const * const m, unsigned int const num_limbs);
void sub_mod_num_num(limb_t * const c, limb_t const * const a, limb_t const * const b, limb_t const * const m, unsigned int const num_limbs);
void mul_montgomery_num_num(limb_t * const z, limb_t const * const x, limb_t const * const y, limb_t const * const m, limb_t m_prime, unsigned int const num_limbs);

#endif

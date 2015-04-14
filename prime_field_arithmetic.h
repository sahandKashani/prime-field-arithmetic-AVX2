#ifndef PRIME_FIELD_ARITHMETIC_H_
#define PRIME_FIELD_ARITHMETIC_H_

#include <stdint.h>
#include <stdbool.h>

unsigned int add(uint64_t * const c, uint64_t const * const a, uint64_t const * const b, unsigned int const num_limbs, unsigned int const carry_in);
unsigned int add_num_limb(uint64_t * const c, uint64_t const * const a, uint64_t const b, unsigned int const num_limbs, unsigned int const carry_in);
unsigned int sub(uint64_t * const c, uint64_t const * const a, uint64_t const * const b, unsigned int const num_limbs, unsigned int const borrow_in);
void mul64_to_128(uint64_t * const c_hi, uint64_t * const c_lo, uint64_t const a, uint64_t const b);
void mul_num_64(uint64_t * const c, uint64_t const * const a, uint64_t const b, unsigned int const num_limbs);
void mul(uint64_t * const c, uint64_t const * const a, uint64_t const * const b, unsigned int const num_limbs);
bool equals_zero(uint64_t const * const num, unsigned int const num_limbs);
int cmp(uint64_t const * const a, uint64_t const * const b, unsigned int const num_limbs);
void and(uint64_t * const c, uint64_t const * const a, uint64_t const * const b, unsigned int const num_limbs);
void add_mod(uint64_t * const c, uint64_t const * const a, uint64_t const * const b, uint64_t const * const m, unsigned int const num_limbs);
void sub_mod(uint64_t * const c, uint64_t const * const a, uint64_t const * const b, uint64_t const * const m, unsigned int const num_limbs);
void mul_montgomery(uint64_t * const z, uint64_t const * const x, uint64_t const * const y, uint64_t const * const m, uint64_t m_prime, unsigned int const num_limbs);

#endif

#ifndef PRIME_FIELD_ARITHMETIC_H_
#define PRIME_FIELD_ARITHMETIC_H_

#include <stdint.h>
#include <stdbool.h>

unsigned int add(uint64_t const c[NUM_LIMBS], uint64_t const a[NUM_LIMBS], uint64_t const b[NUM_LIMBS], unsigned int const carry_in);
unsigned int sub(uint64_t const c[NUM_LIMBS], uint64_t const a[NUM_LIMBS], uint64_t const b[NUM_LIMBS], unsigned int const borrow_in);
bool equals_zero(uint64_t const num[NUM_LIMBS]);
int cmp(uint64_t const a[NUM_LIMBS], uint64_t const b[NUM_LIMBS]);
void add_mod(uint64_t c[NUM_LIMBS], uint64_t const a[NUM_LIMBS], uint64_t const b[NUM_LIMBS], uint64_t const m[NUM_LIMBS]);
void sub_mod(uint64_t c[NUM_LIMBS], uint64_t const a[NUM_LIMBS], uint64_t const b[NUM_LIMBS], uint64_t const m[NUM_LIMBS]);

#endif

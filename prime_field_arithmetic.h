#ifndef PRIME_FIELD_ARITHMETIC_H_
#define PRIME_FIELD_ARITHMETIC_H_

#include <stdint.h>
#include <stdbool.h>

unsigned int add(uint64_t * const c, uint64_t const * const a, uint64_t const * const b, unsigned int const carry_in);
unsigned int sub(uint64_t * const c, uint64_t const * const a, uint64_t const * const b, unsigned int const borrow_in);
bool equals_zero(uint64_t const * const num);
int cmp(uint64_t const * const a, uint64_t const * const b);
void add_mod(uint64_t * const c, uint64_t * const a, uint64_t * const b, uint64_t * const m);
void sub_mod(uint64_t * const c, uint64_t * const a, uint64_t * const b, uint64_t * const m);

#endif

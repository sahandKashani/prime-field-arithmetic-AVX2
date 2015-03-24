#ifndef PRIME_FIELD_ARITHMETIC_H_
#define PRIME_FIELD_ARITHMETIC_H_

#include <stdint.h>
#include <stdbool.h>

unsigned int add(uint64_t *c, uint64_t const *a, uint64_t const *b, unsigned int const num_limbs, unsigned int const carry_in);
unsigned int sub(uint64_t *c, uint64_t const *a, uint64_t const *b, unsigned int const num_limbs, unsigned int const borrow_in);
void mul(uint64_t *c, uint64_t const *a, uint64_t const *b, unsigned int const num_limbs);
bool equals_zero(uint64_t const *num, unsigned int const num_limbs);
int cmp(uint64_t const *a, uint64_t const *b, unsigned int const num_limbs);
void add_mod(uint64_t *c, uint64_t const *a, uint64_t const *b, uint64_t const *m, unsigned int const num_limbs);
void sub_mod(uint64_t *c, uint64_t const *a, uint64_t const *b, uint64_t const *m, unsigned int const num_limbs);

#endif

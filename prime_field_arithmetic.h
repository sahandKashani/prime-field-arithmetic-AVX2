#ifndef PRIME_FIELD_ARITHMETIC_H_
#define PRIME_FIELD_ARITHMETIC_H_

#include <stdint.h>

void add(uint64_t *c, uint64_t *a, uint64_t *b, unsigned int carry_in);
void sub(uint64_t *c, uint64_t *a, uint64_t *b, unsigned int borrow_in);
void add_mod(uint64_t *c, uint64_t *a, uint64_t *b, uint64_t *m);

#endif

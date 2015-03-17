#ifndef PRIME_FIELD_ARITHMETIC_H_
#define PRIME_FIELD_ARITHMETIC_H_

#include <stdint.h>

void add(uint64_t *a, uint64_t *b, uint64_t *c, unsigned int carry_in, unsigned int *carry_out);
void sub(uint64_t *a, uint64_t *b, uint64_t *c, unsigned int borrow_in, unsigned int *borrow_out);

#endif

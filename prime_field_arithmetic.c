#include <stdint.h>
#include "constants.h"

void add(uint64_t *a, uint64_t *b, uint64_t *c, unsigned int carry_in, unsigned int *carry_out) {
    c[0] = a[0] + b[0] + carry_in;
    carry_in = (c[0] < a[0]);

    for (unsigned int i = 1; i < NUM_LIMBS; i++) {
        c[i] = a[i] + b[i] + carry_in;
        carry_in = (c[i] < a[i]);
    }

    *carry_out = (c[NUM_LIMBS-1] < a[NUM_LIMBS-1]);
}

void sub(uint64_t *a, uint64_t *b, uint64_t *c, unsigned int borrow_in, unsigned int *borrow_out) {
    c[0] = a[0] - b[0] - borrow_in;
    borrow_in = (c[0] > a[0]);

    for (unsigned int i = 1; i < NUM_LIMBS; i++) {
        c[i] = a[i] - b[i] - borrow_in;
        borrow_in = (c[i] > a[i]);
    }

    *borrow_out = (c[NUM_LIMBS-1] > a[NUM_LIMBS-1]);
}

#include <stdint.h>
#include "constants.h"

unsigned int add(uint64_t *c, uint64_t *a, uint64_t *b, unsigned int carry_in, unsigned int num_limbs) {
    c[0] = a[0] + b[0] + carry_in;
    carry_in = (c[0] < a[0]);

    for (unsigned int i = 1; i < num_limbs; i++) {
        c[i] = a[i] + b[i] + carry_in;
        carry_in = (c[i] < a[i]);
    }

    unsigned int carry_out = (c[num_limbs-1] < a[num_limbs-1]);
    return carry_out;
}

unsigned int sub(uint64_t *c, uint64_t *a, uint64_t *b, unsigned int borrow_in, unsigned int num_limbs) {
    c[0] = a[0] - b[0] - borrow_in;
    borrow_in = (c[0] > a[0]);

    for (unsigned int i = 1; i < num_limbs; i++) {
        c[i] = a[i] - b[i] - borrow_in;
        borrow_in = (c[i] > a[i]);
    }

    unsigned int borrow_out = (c[num_limbs-1] > a[num_limbs-1]);
    return borrow_out;
}

void add_mod(uint64_t *c, uint64_t *a, uint64_t *b, uint64_t *m) {
	add(c, a, b, 0, NUM_LIMBS);

	uint64_t tmp[NUM_LIMBS];
	clear_num(tmp);
	unsigned int borrow_out = sub(tmp, c, m, 0, NUM_LIMBS);

	if (borrow_out) {
		sub(c, c, m, 0, NUM_LIMBS);
	}
}

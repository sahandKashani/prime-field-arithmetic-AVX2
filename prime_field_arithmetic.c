#include <stdint.h>
#include "constants.h"
#include "utilities.h"

unsigned int add(uint64_t *c, uint64_t *a, uint64_t *b, unsigned int carry_in) {
	unsigned int carry_out;

    c[0] = a[0] + b[0] + carry_in;
    carry_out = (c[0] < a[0]);

    for (unsigned int i = 1; i < NUM_LIMBS; i++) {
        c[i] = a[i] + b[i] + carry_out;
        carry_out = (c[i] < a[i]);
    }

    return carry_out;
}

unsigned int sub(uint64_t *c, uint64_t *a, uint64_t *b, unsigned int borrow_in) {
	unsigned int borrow_out;

    c[0] = a[0] - b[0] - borrow_in;
    borrow_out = (c[0] > a[0]);

    for (unsigned int i = 1; i < NUM_LIMBS; i++) {
        c[i] = a[i] - b[i] - borrow_out;
        borrow_out = (c[i] > a[i]);
    }

    return borrow_out;
}

//// returns -1 if a < b
//// returns  0 if a == b
//// returns +1 if a > b
//unsigned int cmp(uint64_t *a, uint64_t *b) {
//	uint64_t tmp[NUM_LIMBS];
//	clear_num(tmp);
//	unsigned int borrow_out = sub(tmp, a, b, 0, NUM_LIMBS);
//	if (borrow_out) {
//		return -1;
//	}
//}

void add_mod(uint64_t *c, uint64_t *a, uint64_t *b, uint64_t *m) {
	uint64_t tmp[NUM_LIMBS];
	clear_num(tmp);

	unsigned int carry_out = add(c, a, b, 0);
	unsigned int borrow_out = sub(tmp, m, c, 0);

	// result is bigger than our number's max precision due to word space, or is
	// bigger than the modulus
	if (carry_out || borrow_out) {
		sub(c, c, m, 0);
	}
}

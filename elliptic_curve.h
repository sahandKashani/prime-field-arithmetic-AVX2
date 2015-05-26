#ifndef ELLIPTIC_CURVE_H_
#define ELLIPTIC_CURVE_H_

    #include "constants.h"
    #include "limb.h"

    struct curve_point {
        limb_t x[NUM_LIMBS];
        limb_t y[NUM_LIMBS];
    };

    struct curve_point add_point_point(struct curve_point a, struct curve_point b, limb_t *m, limb_t m_prime);

#endif /* ELLIPTIC_CURVE_H_ */

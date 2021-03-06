#ifndef ELLIPTIC_CURVE_H_
#define ELLIPTIC_CURVE_H_

    #include "constants.h"
    #include "limb.h"
    #include "gmp_int.h"

    struct curve_point {
        limb_t x[NUM_LIMBS];
        limb_t y[NUM_LIMBS];
    };

    struct curve_point_gmp {
        gmp_int_t x;
        gmp_int_t y;
    };

    void curve_point_init_gmp(struct curve_point_gmp *p);
    void curve_point_clear_gmp(struct curve_point_gmp *p);
    void neg_point(struct curve_point *p2, struct curve_point *p1, unsigned int num_limbs);
    void neg_point_gmp(struct curve_point_gmp *p2, struct curve_point_gmp *p1);
    void add_point_point(struct curve_point *p3, struct curve_point *p1, struct curve_point *p2, unsigned int num_limbs);
    void add_point_point_gmp(struct curve_point_gmp *p3, struct curve_point_gmp *p1, struct curve_point_gmp *p2);
    void double_point(struct curve_point *p2, struct curve_point *p1, unsigned int num_limbs);
    void double_point_gmp(struct curve_point_gmp *p2, struct curve_point_gmp *p1);
    bool is_on_curve(limb_t *x_num, limb_t *y_num, unsigned int num_limbs);
    bool is_on_curve_point(struct curve_point p, unsigned int num_limbs);
    bool is_on_curve_gmp(gmp_int_t x_gmp, gmp_int_t y_gmp);
    bool is_on_curve_point_gmp(struct curve_point_gmp p);

#endif /* ELLIPTIC_CURVE_H_ */

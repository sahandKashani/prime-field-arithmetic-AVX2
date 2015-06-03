#ifndef CHECK_ARITHMETIC_H_
#define CHECK_ARITHMETIC_H_

#include <stdbool.h>

bool test_add_num_num(unsigned int number_of_tests, unsigned int seed);
bool test_add_num_limb(unsigned int number_of_tests, unsigned int seed);
bool test_sub_num_num(unsigned int number_of_tests, unsigned int seed);
bool test_mul_limb_limb(unsigned int number_of_tests, unsigned int seed);
bool test_mul_num_limb(unsigned int number_of_tests, unsigned int seed);
bool test_mul_num_num(unsigned int number_of_tests, unsigned int seed);
bool test_add_mod_num_num(unsigned int number_of_tests, unsigned int seed);
bool test_sub_mod_num_num(unsigned int number_of_tests, unsigned int seed);
bool test_mul_montgomery_num_num(unsigned int number_of_tests, unsigned int seed);
bool test_point_addition();
bool test_point_double();
bool test_point_neg();
void check_add_num_num(unsigned int num_iterations, unsigned int seed);
void check_add_num_limb(unsigned int num_iterations, unsigned int seed);
void check_sub_num_num(unsigned int num_iterations, unsigned int seed);
void check_mul_limb_limb(unsigned int num_iterations, unsigned int seed);
void check_mul_num_limb(unsigned int num_iterations, unsigned int seed);
void check_mul_num_num(unsigned int num_iterations, unsigned int seed);
void check_add_mod_num_num(unsigned int num_iterations, unsigned int seed);
void check_sub_mod_num_num(unsigned int num_iterations, unsigned int seed);
void check_mul_montgomery_num_num(unsigned int num_iterations, unsigned int seed);
void check_add_point_point();
void check_double_point();
void check_neg_point();

#endif /* CHECK_ARITHMETIC_H_ */

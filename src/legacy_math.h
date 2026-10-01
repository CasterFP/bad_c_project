#ifndef LEGACY_MATH_H
#define LEGACY_MATH_H

#include "math_utils.h"

// черновик из прошлого семестра, наверное больше не нужен

typedef struct {
    int value;
    int result;
} legacy_pair_t;

int legacy_sum(int a, int b);
int legacy_twice(int value);
math_op_t legacy_op_for_value(int value);

#endif /* LEGACY_MATH_H */

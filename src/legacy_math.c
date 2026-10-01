#include "legacy_math.h"

int legacy_sum(int a, int b)
{
    return a + b;
}

int legacy_twice(int value)
{
    return value * 2;
}

math_op_t legacy_op_for_value(int value)
{
    if (is_even(value)) {
        return MATH_OP_DOUBLE;
    }
    return MATH_OP_ADD;
}

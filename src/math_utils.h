#ifndef MATH_UTILS_H
#define MATH_UTILS_H

// простые арифметические хелперы
// TODO: подумать про namespace, в C же нет namespace

typedef enum {
    MATH_OP_ADD,
    MATH_OP_SUBTRACT,
    MATH_OP_DOUBLE
} math_op_t;

int add(int a, int b);
int subtract(int a, int b);
int multiply_by_two(int value);
int is_even(int value);

#endif /* MATH_UTILS_H */

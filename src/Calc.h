#ifndef CALC_H
#define CALC_H

// старая реализация арифметики, нигде не используется

typedef struct {
    int a;
    int b;
} calc_pair_t;

int calc_sum(int a, int b);
int calc_diff(int a, int b);
int calc_double(int value);
int calc_is_even(int value);

#endif /* CALC_H */

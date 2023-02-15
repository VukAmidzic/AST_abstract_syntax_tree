#include <stdint.h>

#ifndef ASM_OPS_H
#define ASM_OPS_H

int64_t cmp_less(int64_t a, int64_t b);
int64_t cmp_great(int64_t a, int64_t b);
int64_t cmp_eq(int64_t a, int64_t b);
int64_t cmp_neq(int64_t a, int64_t b);
int64_t cmp_leq(int64_t a, int64_t b);
int64_t cmp_geq(int64_t a, int64_t b);

#endif

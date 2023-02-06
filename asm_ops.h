#include <stdint.h>

#ifndef ASM_OPS_H
#define ASM_OPS_H

uint64_t cmp_less(uint64_t a, uint64_t b);
uint64_t cmp_great(uint64_t a, uint64_t b);
uint64_t cmp_eq(uint64_t a, uint64_t b);
uint64_t cmp_neq(uint64_t a, uint64_t b);
uint64_t cmp_leq(uint64_t a, uint64_t b);
uint64_t cmp_geq(uint64_t a, uint64_t b);

#endif

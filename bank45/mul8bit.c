//
// Created by D. Rimron-Soutter on 21/04/2022.
//
#include <stdio.h>

#include "inc/mul8bit.h"
#include "../inc/trammath.h"

void mul8bit(uint8_t factor) {
    printf("BANK 45, mul(factor=%d)\n", factor);
    total = total * factor;
}
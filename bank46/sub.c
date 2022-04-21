//
// Created by D. Rimron-Soutter on 21/04/2022.
//
#include <stdio.h>

#include "inc/sub.h"
#include "../inc/trammath.h"

void sub(uint16_t loss) {
    printf("BANK 46, sub(loss=%d)\n", loss);
    total = total - loss;
}
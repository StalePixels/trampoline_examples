//
// Created by D. Rimron-Soutter on 21/04/2022.
//
#include <stdio.h>

#include "inc/div_two.h"

void div_two(uint16_t *sum) {
    printf("BANK 44, div_two(sum=%d)\n", *sum);
    *sum = *sum / 2;
}
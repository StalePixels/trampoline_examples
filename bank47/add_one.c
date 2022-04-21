//
// Created by D. Rimron-Soutter on 21/04/2022.
//

#include <stdio.h>

#include "inc/add_one.h"
#include "../inc/trammath.h"

void add_one(uint8_t *sum) {
    printf("BANK 47, add_one(sum=%d)\n", *sum);
    total = total + *sum;
}
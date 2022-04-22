//
// Created by D. Rimron-Soutter on 22/04/2022.
//
#include <stdio.h>
#include <stdint.h>

#include "inc/log.h"

void log(char *label, uint16_t val) {
    printf("b43.%s:%d\n\n", label, val);
}
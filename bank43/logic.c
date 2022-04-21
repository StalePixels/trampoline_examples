//
// Created by D. Rimron-Soutter on 21/04/2022.
//
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "inc/logic.h"
#include "../inc/execfar.h"
#include "../inc/trammath.h"
#include "../bank47/inc/add_one.h"
#include "../bank46/inc/sub.h"
#include "../bank45/inc/mul8bit.h"
#include "../bank44/inc/div_two.h"

// This is in BANK43
void logic() {
    uint16_t *param = malloc(sizeof uint16_t);
    // a good developer would confirm the malloc worked here
    //                                              I'm not a good developer...

    *param = 12;
    printf("b43.total:%d\n\n", total);

    /*
     * Execute function add_one(param), in bank 47
     *
     * param is malloced out of the heap in main (0x8000<->0xBFE0) memory,
     * it could be a pointer to anything we wanted, but the pointer itself
     * is a 16bit unsigned integer, the memory address of the malloc. This
     * is standard C stuff, not at all Next/z88dk specific.
     *
     */
    execfarWithUint16(add_one, param, 47<<1);
    printf("b43.total:%d\n\n", total);

    /*
     * Execute function mul8bit(7), in bank45
     *
     * Called with a parameter value as a 8bit int.  This could also,
     * of course, be accomplished with a pointer to the value, but this is
     * an example of a "direct" parameter, not a pointer to "main" memory.
     *
     */
    execfarWithUint8(mul8bit, 100, 45<<1);
    printf("b43.total:%d\n\n", total);

    /*
     * Execute function sub(9), in bank46
     *
     * Called with a parameter value as a 16bit int.  Same idea as mul8bit
     * but this time rather than the parameter being used as a pointer we use
     * it directly.
     *
     */
    execfarWithUint16(sub, 1104, 46<<1);
    printf("b43.total:%d\n\n", total);

    /*
     * Execute function div_two(param), in bank46
     *
     * Called with a parameter value as a 16bit pointer.  Same idea as add_one
     * but this time we also store our return in the source pointer location.
     *
     */
    // copy total into the param malloc
    *param = total;
    execfarWithUint16(div_two, param, 44<<1);
    // copy total back out of param malloc
    total = *param;

    // Don't leak memory!
    free(param);
    printf("Logic done, exiting bank 43\n");
}
//
// Created by D. Rimron-Soutter on 21/04/2022.
//

#include <stdio.h>

#include "inc/trammath.h"
#include "inc/execfar.h"

#include "bank43/inc/logic.h"

uint16_t total = 0;

int main(void) {
    printf("Trampoline Total: %d\n", total);

    /*
     * Execute function execfar(), in bank 43 - there are no passed parameters
     */
    execfar(logic, 43<<1);

    printf("Final Total: %d\n", total);
#ifdef dotn
    printf("QUITTING!\n");
    return 0;
#else
    printf("RESET NEXT TO QUIT!");
    while(1);
#endif
}

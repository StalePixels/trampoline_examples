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
     * Execute function logic(), in bank 43 - there are no passed parameters.
     * There is nothing special about this function, it's exported from the
     * local file exactly as per normal C methods, you can call into any number
     * of functions in a bank - there's no special "entry point", or magic
     * decoration - just be sure that the bank in question is mapped by the
     * MMU first.
     *
     * By default you can change the base address that compiled banks use, and
     * not use MMU 6+7, but that's beyond the scope of this simple introduction.
     *
     * There's also no actual, special, specific need to use an execfar
     * trampoline here - it could have just as easily done a manual MMU mapping
     * before calling "logic()" as normal - but if you're doing that from a dot
     * command you must remember to save the original banks, and restore before
     * quitting - by leveraging the execfar it does that for me.
     *
     */
    execfar(logic, 43<<1);

    printf("Final Total: %d\n", total);
#ifdef dotn
    printf("QUITTING!");
    return 0;
#else
    printf("RESET NEXT TO QUIT!");
    while(1);
#endif
}

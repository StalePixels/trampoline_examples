//
// Created by D. Rimron-Soutter on 21/04/2022.
//

/*
 * dotn is defined externally at compile with the -Ddotn flag passed to zcc
 */

#include <z80.h>
#include <arch/zxn.h>
#include <intrinsic.h>
#include <arch/zxn/esxdos.h>
#include <stdio.h>

#include "inc/execfar.h"

#ifdef dotn
extern unsigned char _z_page_table[];
#endif

/*
 *******************************************************************************
 * Noisy Trampolines
 *******************************************************************************
 *
 * To use these in realworld circumstances you should (hopefully obviously)
 * remove the printfs - they're only there to make it clear what is going on.
 *
 *
 * Some notes about the input:
 *    fn:       The address of the function we're going to call
 *
 *    i8/i16:   The 8 or 16bit parameter to pass into the function fn. Optional
 *              depending which execfar trampoline you use, and how those values
 *              are used by the destination function is your choice.  There's
 *              several working examples on how these can be used in this repo.
 *
 *    destBank: The 8k page number which relates to the 16k bank that is mapped.
 *              This is why you'll see, throughout this example, banks requested
 *              as 47<<1 ( the left shifted number is the same as x2 - this is
 *              expanded by the compiler so incurs no computation at runtime) and
 *              helps visualise the association between the BANK in the code and
 *              the following line in the makefile:
 *            --codesegBANK_47 --constsegBANK_47 --datasegBANK_47 --bsssegBANK_47
 *
 *
 * Some notes about the output:
 *    addr:     The address of the remote function you're calling.  Routines
 *              in MMU6+7 should always be between 0xC000 and 0xFFFF, inclusive.
 *              If the address isn't in that range it means you've either
 *              remapped a BANK with a #pragma for z88dk or "cheating" with the
 *              trampoline (e.g., calling a function elsewhere but using the
 *              trampoline to map in some dependency functions or data into
 *              the top MMU slots).
 *
 *    *16 & *8: The parameters (if the exist) to be passed to the far function.
 *
 *    Zp:       The **PHYSICAL**, actual, hardware page number - after it's been
 *              looked up in the **VIRTUAL** mapping table.  This is only used
 *              for dotn style applications which dynamically request pages from
 *              NextZXOS and cannot be assured to get the exact page-number you
 *              specified in the Makefile.  Therefore the _z_page_table[] array
 *              is a lookup of physical to virtual pages - i.e. _z_page_table[94]
 *              (see the notes about destBank, above, on why bank47 becomes 94)
 *              will contain an uint8 value of the physical RAM page which was
 *              allocated.  On a 2MB Next these will often be up in the 200s.
 *
 *    pg:       The **PHYSICAL**, actual, hardware page number - no virtual MMU
 *              mapping table is used for these, this is how "non cooperative"
 *              applications will mostly use RAM, bypassing NextZXOS's allocation
 *              tables and routines, and overwriting any existing code directly.
 *
 */
void execfar(void (*fn)(void), uint8_t destBank) {
    printf("addr:%X", fn);
    uint8_t BottomPage = ZXN_READ_REG(REG_MMU0 + 6);
    uint8_t TopPage = ZXN_READ_REG(REG_MMU0 + 7);

#ifdef dotn
    printf(" Zp: %d\n", _z_page_table[destBank]);
    ZXN_WRITE_MMU6(_z_page_table[destBank]);
    ZXN_WRITE_MMU7(_z_page_table[destBank+1]);
#else // NEX, et al
    printf(" pg: %d\n", destBank);
    ZXN_WRITE_MMU6(destBank);
    ZXN_WRITE_MMU7(destBank+1);
#endif

    fn();

    ZXN_WRITE_MMU6(BottomPage);
    ZXN_WRITE_MMU7(TopPage);
}

void execfarWithUint8(void (*fn)(uint8_t), uint8_t i8, uint8_t destBank) {
    printf("addr:%X *8:%X", fn, i8);
    uint8_t BottomPage = ZXN_READ_REG(REG_MMU0 + 6);
    uint8_t TopPage = ZXN_READ_REG(REG_MMU0 + 7);

#ifdef dotn
    printf(" Zp: %d\n", _z_page_table[destBank]);
    ZXN_WRITE_MMU6(_z_page_table[destBank]);
    ZXN_WRITE_MMU7(_z_page_table[destBank+1]);
#else // NEX, et al
    printf(" pg: %d\n", destBank);
    ZXN_WRITE_MMU6(destBank);
    ZXN_WRITE_MMU7(destBank+1);
#endif

    fn(i8);

    ZXN_WRITE_MMU6(BottomPage);
    ZXN_WRITE_MMU7(TopPage);
}

void execfarWithUint16(void (*fn)(uint16_t), uint16_t i16, uint8_t destBank) {
    printf("addr:%X *16:%X", fn, i16);
    uint8_t BottomPage = ZXN_READ_REG(REG_MMU0 + 6);
    uint8_t TopPage = ZXN_READ_REG(REG_MMU0 + 7);

#ifdef dotn
    printf(" Zp:%d\n", _z_page_table[destBank]);
    ZXN_WRITE_MMU6(_z_page_table[destBank]);
    ZXN_WRITE_MMU7(_z_page_table[destBank+1]);
#else // NEX, et al
    printf(" pg:%d\n", destBank);
    ZXN_WRITE_MMU6(destBank);
    ZXN_WRITE_MMU7(destBank+1);
#endif

    fn(i16);

    ZXN_WRITE_MMU6(BottomPage);
    ZXN_WRITE_MMU7(TopPage);
}
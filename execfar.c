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

/*******************************************************************************
 * Dispatchers
 ******************************************************************************/
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
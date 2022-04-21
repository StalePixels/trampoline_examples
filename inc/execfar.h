//
// Created by D. Rimron-Soutter on 21/04/2022.
//

#ifndef TRAMPOLINE_EXAMPLES_EXECFAR_H
#define TRAMPOLINE_EXAMPLES_EXECFAR_H

void execfar(void (*fn)(void), uint8_t destBank);
void execfarWithUint8(void (*fn)(uint8_t), uint8_t i8, uint8_t destBank);
void execfarWithUint16(void (*fn)(uint16_t), uint16_t i16, uint8_t destBank);

#endif //TRAMPOLINE_EXAMPLES_EXECFAR_H

/*
 * Perif_Setup.c
 *
 *  Created on: 6 de jul de 2021
 *      Author: paulo
 */

#include "Perif_Setup.h"

void Setup_GPIO_Red(void) {// void Setup_GPIO(void)
    EALLOW;


    //GPI034 - LED RED
    GpioCtrlRegs.GPBGMUX1.bit.GPIO34 = 0;
    GpioCtrlRegs.GPBMUX1.bit.GPIO34 = 0;
    GpioCtrlRegs.GPBPUD.bit.GPIO34 = 1;
    GpioCtrlRegs.GPBDIR.bit.GPIO34 = 1; //valido apenas para GPIO
    GpioCtrlRegs.GPBCSEL1.bit.GPIO34 = GPIO_MUX_CPU1;
//Código para piscar os dois led em uma só funcao
//    //GPI031 - LED Blue
//    GpioCtrlRegs.GPAGMUX2.bit.GPIO31 = 0;
//    GpioCtrlRegs.GPAMUX2.bit.GPIO31 = 0;
//    GpioCtrlRegs.GPAPUD.bit.GPIO31 = 1;
//    GpioCtrlRegs.GPADIR.bit.GPIO31 = 1; //valido apenas para GPIO
//    GpioCtrlRegs.GPACSEL4.bit.GPIO31 = GPIO_MUX_CPU1;



    EDIS;
}


void Setup_GPIO_Blue(void) {
    EALLOW;
    //GPI031 - LED Blue
    GpioCtrlRegs.GPAGMUX2.bit.GPIO31 = 0;
    GpioCtrlRegs.GPAMUX2.bit.GPIO31 = 0;
    GpioCtrlRegs.GPAPUD.bit.GPIO31 = 1;
    GpioCtrlRegs.GPADIR.bit.GPIO31 = 1; //valido apenas para GPIO
    GpioCtrlRegs.GPACSEL4.bit.GPIO31 = GPIO_MUX_CPU1;
EDIS;
}

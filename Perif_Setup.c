/*
 * Perif_Setup.c
 *
 *  Created on: 6 de jul de 2021
 *      Author: paulo
 */

#include "Perif_Setup.h"

void Setup_GPIO_RED(void) {
    EALLOW;

    //GPI034 - LED RED
    GpioCtrlRegs.GPBGMUX1.bit.GPIO34 = 0;
    GpioCtrlRegs.GPBMUX1.bit.GPIO34 = 0;
    GpioCtrlRegs.GPBPUD.bit.GPIO34 = 1;
    GpioCtrlRegs.GPBDIR.bit.GPIO34 = 1; //valido apenas para GPIO
    GpioCtrlRegs.GPBCSEL1.bit.GPIO34 = GPIO_MUX_CPU1;

    EDIS;
}

void Setup_GPIO_Blue(void) {
    EALLOW;                                 // Enable EALLOW protected register acess

//GPI031 - LED Blue
       GpioCtrlRegs.GPAGMUX2.bit.GPIO31 = 0;
       GpioCtrlRegs.GPAMUX2.bit.GPIO31 = 0;
       GpioCtrlRegs.GPAPUD.bit.GPIO31 = 1;
       GpioCtrlRegs.GPADIR.bit.GPIO31 = 1; //valido apenas para GPIO
       GpioCtrlRegs.GPACSEL4.bit.GPIO31 = GPIO_MUX_CPU1;

EDIS;
}

void Setup_DAC(void)
{
    EALLOW;                                 // Enable EALLOW protected register acess

    //----- Configurte DAC-A control registers
          DacaRegs.DACCTL.all = 0x0001;
          // bit 15-8            0's: reserved
          // bit 7-4          0000: DAC PWMSYNC select, not used since LOADMODE=0
          // bit 3               0:   reserved
          // bit 2               0: LOADMODE, DACVALA load mode, 0=next SYSCLK, 1=next PWMSYNC specified by SYSCLK
          // bit 1               0: reserved
          // bit 0               1: DACREFSEL, DAC reference select, 0=VDAC/VSSA, 1=ADC VREFHI/VREFLO

      //--- Set DAC-A output to mid-range
          DacaRegs.DACVALS.all = 0x0800;          // DACVALS = bits 11-0. bits 15-12 reserved

      //--- Enable DAC-A output
          DacaRegs.DACOUTEN.bit.DACOUTEN = 1;     //DAC output enable, 0=disable, 1=enable

      //---DAC-A lock control register
          DacaRegs.DACLOCK.all = 0x0000;          // Write a 1 to lock (cannot be cleared once set)


//----- Configurte DAC-B control registers
    DacbRegs.DACCTL.all = 0x0001;
    // bit 15-8            0's: reserved
    // bit 7-4          0000: DAC PWMSYNC select, not used since LOADMODE=0
    // bit 3               0:   reserved
    // bit 2               0: LOADMODE, DACVALA load mode, 0=next SYSCLK, 1=next PWMSYNC specified by SYSCLK
    // bit 1               0: reserved
    // bit 0               1: DACREFSEL, DAC reference select, 0=VDAC/VSSA, 1=ADC VREFHI/VREFLO

//--- Set DAC-B output to mid-range
    DacbRegs.DACVALS.all = 0x0800;          // DACVALS = bits 11-0. bits 15-12 reserved

//--- Enable DAC-B output
    DacbRegs.DACOUTEN.bit.DACOUTEN = 1;     //DAC output enable, 0=disable, 1=enable

//---DAC-B lock control register
    DacbRegs.DACLOCK.all = 0x0000;          // Write a 1 to lock (cannot be cleared once set)



    EDIS;                                   // Disable EALLOW protected register access

}

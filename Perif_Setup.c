/*
 * Perif_Setup.c
 *
 *  Created on: 6 de jul de 2021
 *      Author: paulo e Wellington
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

    //----- Configurte DAC-A control registers Pino 30
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


//----- Configurte DAC-B control registers Pino 70
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

//******************************************
//          EPW10
//******************************************

void Setup_ePWM10(void){
    EALLOW;
    CpuSysRegs.PCLKCR2.bit.EPWM10 = 1;           //habilitar clock

    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 0;

    EPwm10Regs.TBPRD = 5000;                         //periodo (up/down) 10Khz Clock/4/fpwm LAB PWM

    //Largura do pulso 50%
    EPwm10Regs.CMPA.bit.CMPA = EPwm10Regs.TBPRD >> 1;

    EPwm10Regs.TBPHS.bit.TBPHS = 0;                  // Phase is 0
    EPwm10Regs.TBCTL.bit.SYNCOSEL = TB_CTR_ZERO;
    EPwm10Regs.TBCTR = 0x0000;                       // Clear counter

    EPwm10Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;  // Count up/down
    EPwm10Regs.TBCTL.bit.PHSEN = TB_DISABLE;         // Disable phase loading

    EPwm10Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;        // Clock ratio to SYSCLKOUT
    EPwm10Regs.TBCTL.bit.CLKDIV = TB_DIV1;

    EPwm10Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;     // Load registers every ZERO
    EPwm10Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO_PRD;
    EPwm10Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;     // Load registers every ZERO
    EPwm10Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO_PRD;

    EPwm10Regs.AQCTLA.bit.PRD = AQ_NO_ACTION;
    EPwm10Regs.AQCTLA.bit.ZRO = AQ_NO_ACTION;
    EPwm10Regs.AQCTLA.bit.CAU = AQ_CLEAR;            // set actions for EPWM10A
    EPwm10Regs.AQCTLA.bit.CAD = AQ_SET;

    //Trigger ADC
    EPwm10Regs.ETSEL.bit.SOCAEN = 1;                 // Enable SOC on A group
    EPwm10Regs.ETSEL.bit.SOCASEL = ET_CTR_PRDZERO;   // Dispara ADC no topo
    EPwm10Regs.ETPS.bit.SOCAPRD = ET_1ST;            // Trigger on every event

    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 1;
    EDIS;
}


//******************************************
//          ADC
//******************************************

void Setup_ADC (void){
    Uint16 acqps;

    //determine minimum acquisition window (in SYSCLKS) based on resolution

    if(ADC_RESOLUTION_12BIT == AdcaRegs.ADCCTL2.bit.RESOLUTION)
            acqps = 14;                             // 75ns
        else                                        // resolution is 16-bit
            acqps = 63;                             // 320ns

    EALLOW;
    CpuSysRegs.PCLKCR13.bit.ADC_A = 1;
    AdcaRegs.ADCCTL2.bit.PRESCALE = 6;               // set ADCCLK divider to /4 (200MHz/4=50MHz que é o máximo permitido neste ADC usado), o valor usado "6" foi retirado do manual de referência técnica, 11.16.2 ADC_REGS Registers tabela 11-14 2 linha clica em "Go" vai na Figura 11-27 olhar o prescaler que é dividido por 4.

    AdcSetMode(ADC_ADCA, ADC_RESOLUTION_12BIT, ADC_SIGNALMODE_SINGLE);      // ADC_RESOLUTION_12BIT olha na tabela 11-2 Analog to 12bit Digital Formulas

    AdcaRegs.ADCCTL1.bit.INTPULSEPOS = 1;           // Set pulse um ciclo antes do resultado
    AdcaRegs.ADCCTL1.bit.ADCPWDNZ = 1;              // Power up the ADC
    DELAY_US(1000);                                 // Delay for 1ms to allow ADC time to power up

    AdcaRegs.ADCSOC0CTL.bit.CHSEL = 3;              // ADCINA3 - J3 - Pin26
    AdcaRegs.ADCSOC0CTL.bit.ACQPS = acqps;         // Sample windows is 15 SYSCLK cycles
    AdcaRegs.ADCSOC0CTL.bit.TRIGSEL = 0x17;

    AdcaRegs.ADCSOC1CTL.bit.CHSEL = 4;              // ADCINA4 - J7 - PIN69
    AdcaRegs.ADCSOC1CTL.bit.ACQPS = acqps;
    AdcaRegs.ADCSOC1CTL.bit.TRIGSEL = 0x17;

    AdcaRegs.ADCINTSEL1N2.bit.INT1SEL = 0x01;       // end of S0C1 will set INT1 flag
    AdcaRegs.ADCINTSEL1N2.bit.INT1E = 1;            // enable INT1 flag
    AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;          // make sure INT1 flag is cleared

    EDIS;

}

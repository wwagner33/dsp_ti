

#include "Perif_Setup.h"

//#include "math.h"             //somente para uso de comandos seno, coseno, etc.
                                /*se usar __sin ou __cos eles executam direto nesta nossa placa sem
                                precisar desta biblioteca sendo mais rápido para gerar a tabela */

//uint32_t count = 0;

__interrupt void isr_timer0(void);
__interrupt void isr_timer1(void);
__interrupt void isr_timer2(void);

uint16_t index =0, senotable[400], cosenotable[400];

/**
 * main.c
 */
int main(void)
{
    InitSysCtrl();   //Initialize System
    DINT;

    InitPieCtrl(); // Initialize the PIE control registers to their

    IER = 0x0000;   // Disable CPU interrupts
    IFR = 0x0000;   // Clear all CPU interrupt flags:

    InitPieVectTable(); //Initialize o PIE Vector table

    // interrupcoes
   EALLOW;

    PieVectTable.TIMER0_INT = &isr_timer0;
    PieCtrlRegs.PIEIER1.bit.INTx7 = 1;
    PieVectTable.TIMER1_INT = &isr_timer1;
    PieVectTable.TIMER2_INT = &isr_timer2;

    EDIS;

    //  IER = 1; //habilita a coluna 1
    //  IER = 0x10 //desabilita a coluna 1 e habilita a coluna 2
     IER |= M_INT1;
     IER |= M_INT13; //enable INT13 in IER
     IER |= M_INT14;

    // configura timer0 e 1

    InitCpuTimers();
    ConfigCpuTimer(&CpuTimer0, 200, 50);
    CpuTimer0Regs.TCR.all = 0x4000;
    ConfigCpuTimer(&CpuTimer1, 200, 500000);
    CpuTimer1Regs.TCR.all = 0x4000;
    ConfigCpuTimer(&CpuTimer2, 200, 1000000);
    CpuTimer2Regs.TCR.all = 0x4000;

    // Setup dos GPIO
    Setup_GPIO_RED();
    Setup_GPIO_Blue();

    //Configura DAC
    Setup_DAC();

    //GpioDataRegs.GPASET.bit.GPIO14 = 1;

    //criar tabela da senoide
    for (index = 0; index < 400; index++){
        //senotable[index] = (uint16_t)(1000.0*(1.0+ sin((6.28318531/400.0)*((float)index))));
        //cosenotable[index] = (uint16_t)(1000.0*(1.0+ cos((6.28318531/400.0)*((float)index)))
        senotable[index] = (uint16_t)(1000.0*(1.0+ __sin((6.28318531/400.0)*((float)index))));
        cosenotable[index] = (uint16_t)(1000.0*(1.0+ __cos((6.28318531/400.0)*((float)index))));
    }
    index=0;

    //GpioDataRegs.GPACLEAR.bit.GPIO14 = 1;

    EINT;   // Enable Global interrupt INTM
    ERTM;   // Enable Global realtime interrupt DBGM

    GpioDataRegs.GPADAT.bit.GPIO31 = 1;
    GpioDataRegs.GPBDAT.bit.GPIO34 = 0;


//    while(1){
//        for (count = 0; count < 0x00FFFFFF; count++) {
//
//        }
//        GpioDataRegs.GPBTOGGLE.bit.GPIO34 = 1;
//        GpioDataRegs.GPATOGGLE.bit.GPIO31 = 1;
//    }

}
__interrupt void isr_timer0(void){

    index = (index == 399) ? 0 : (index+1);
       DacbRegs.DACVALS.all = senotable[index];
       DacaRegs.DACVALS.all = cosenotable[index];
       PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}

__interrupt void isr_timer1(void){
    GpioDataRegs.GPATOGGLE.bit.GPIO31 = 1;

}

__interrupt void isr_timer2(void){
    GpioDataRegs.GPBTOGGLE.bit.GPIO34 = 1;
}

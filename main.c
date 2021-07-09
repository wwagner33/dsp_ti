#include "Perif_Setup.h"


uint32_t count = 0; //Descomentar para piscar leds sem timers

  //Comentar esse codigo para que os dois leds possam piscar sem uso de timers 
//*************Inicio********************
//__interrupt void isr_timer0(void);
//__interrupt void isr_timer1(void);
//*************Fim********************

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
//*************Inicio Codigo Trabalho 2*************************
  //Comentar esse codigo para que os dois leds possam piscar sem uso de timers
  //Esse codigo corresponde ao trabalho 2
    // interrupcoes
//   EALLOW;

//    PieVectTable.TIMER0_INT = &isr_timer0;
//    PieCtrlRegs.PIEIER1.bit.INTx7 = 1;

    //Habilitar INT13

//    PieVectTable.TIMER1_INT = &isr_timer1;

//    EDIS;

    //  IER = 1; //habilita a coluna 1
    //  IER = 0x10 //desabilita a coluna 1 e habilita a coluna 2
//     IER |= M_INT1;
//     IER |= M_INT13;

    // configura timer0 e 1

//    InitCpuTimers();
//    ConfigCpuTimer(&CpuTimer0, 200, 500000);
//    CpuTimer0Regs.TCR.all = 0x4000;
//    ConfigCpuTimer(&CpuTimer1, 200, 2000000);
//    CpuTimer1Regs.TCR.all = 0x4000;
//*****************Fim Codigo do Trabalho 2***********************

    // Setup dos GPIO
    Setup_GPIO_Red();
    Setup_GPIO_Blue();
    EINT;   // Enable Global interrupt INTM
    ERTM;   // Enable Global realtime interrupt DBGM
    GpioDataRegs.GPBDAT.bit.GPIO34 = 0;
    GpioDataRegs.GPADAT.bit.GPIO31 = 1;
//Descomentar essse codigo para que os dois leds pisquem sem usar timers
    while(1){
        for (count = 0; count < 0x00FFFFFF; count++) {

        }
        GpioDataRegs.GPBTOGGLE.bit.GPIO34 = 1;
        GpioDataRegs.GPATOGGLE.bit.GPIO31 = 1;
    }

}

//Comentar esse codigo para que os dois leds possam piscar sem uso de timers
//Esse codigo corresponde ao trabalho 2
//__interrupt void isr_timer1(void){
//    GpioDataRegs.GPATOGGLE.bit.GPIO31 = 1;

//}
//__interrupt void isr_timer0(void){
//    GpioDataRegs.GPBTOGGLE.bit.GPIO34 = 1;
//    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
//}


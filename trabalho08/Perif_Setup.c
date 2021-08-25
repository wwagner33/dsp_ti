/*
* Perif_Setup.c
*
* Created on: 6 de jul de 2021
* Author: paulo e Wellington
*/

/*
 * Pinagem do trabalho 5
 * PWM1: 39 e 40
 * PWM2: 37 e 38
 *
 *
 */

/*
 * Pinagem do trabalho 6
 * PWM7: 72
 * PWM8: 32
 *
 *
 */




#include "Perif_Setup.h"
void Setup_GPIO(void) {
    EALLOW;

    //GPI034 - LED RED
    GpioCtrlRegs.GPBGMUX1.bit.GPIO34 = 0;
    GpioCtrlRegs.GPBMUX1.bit.GPIO34 = 0;
    GpioCtrlRegs.GPBPUD.bit.GPIO34 = 1;
    GpioCtrlRegs.GPBDIR.bit.GPIO34 = 1; //valido apenas para GPIO
    GpioCtrlRegs.GPBCSEL1.bit.GPIO34 = GPIO_MUX_CPU1;

    //GPI031 - LED Blue
    GpioCtrlRegs.GPAGMUX2.bit.GPIO31 = 0;
    GpioCtrlRegs.GPAMUX2.bit.GPIO31 = 0;
    GpioCtrlRegs.GPAPUD.bit.GPIO31 = 1;
    GpioCtrlRegs.GPADIR.bit.GPIO31 = 1; //valido apenas para GPIO 1 -. saida
    GpioCtrlRegs.GPACSEL4.bit.GPIO31 = GPIO_MUX_CPU1;

    EDIS;
}
void Setup_GPIO_Pwm(void) { // Enable EALLOW protected register acesso
    EALLOW;
    //IO 0 - EPWM1A (J4 - 40) GPIO0
    GpioCtrlRegs.GPAGMUX1.bit.GPIO0 = 0; // grupo 0
    GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 1; // coloca 1 para ser Pwm
    GpioCtrlRegs.GPAPUD.bit.GPIO0 = 1;
    //GpioCtrlRegs.GPADIR.bit.GPIO0 = 1; //valido apenas para GPIO 1 -. saida
    GpioCtrlRegs.GPACSEL1.bit.GPIO0 = GPIO_MUX_CPU1;

    //IO 0 - EPWM1B (J4 - 39) GPIO1
    GpioCtrlRegs.GPAGMUX1.bit.GPIO1 = 0;
    GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 1;
    GpioCtrlRegs.GPAPUD.bit.GPIO1 = 1;
    //GpioCtrlRegs.GPADIR.bit.GPIO1 = 1; //valido apenas para GPIO 1 -. saida
    GpioCtrlRegs.GPACSEL1.bit.GPIO1 = GPIO_MUX_CPU1;

    //IO 0 - EPWM2A (J4 - 38) GPIO2
    GpioCtrlRegs.GPAGMUX1.bit.GPIO2 = 0; // grupo 0
    GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 1; // coloca 1 para ser Pwm
    GpioCtrlRegs.GPAPUD.bit.GPIO2 = 1;
    //GpioCtrlRegs.GPADIR.bit.GPIO2 = 1; //valido apenas para GPIO 1 -. saida
    GpioCtrlRegs.GPACSEL1.bit.GPIO2 = GPIO_MUX_CPU1;

    //IO 0 - EPWM2B (J4 - 37) GPIO3
    GpioCtrlRegs.GPAGMUX1.bit.GPIO3 = 0;
    GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 1;
    GpioCtrlRegs.GPAPUD.bit.GPIO3 = 1;
    //GpioCtrlRegs.GPADIR.bit.GPIO3 = 1; //valido apenas para GPIO 1 -. saida
    GpioCtrlRegs.GPACSEL1.bit.GPIO3 = GPIO_MUX_CPU1;

    //IO 0 - EPWM7A DAC3 (J8 - 72) GPIO157
    GpioCtrlRegs.GPEGMUX2.bit.GPIO157 = 0;
    GpioCtrlRegs.GPEMUX2.bit.GPIO157 = 1;
    GpioCtrlRegs.GPEPUD.bit.GPIO157 = 1;


    //IO 0 - EPWM8A DAC1 (J4 - 32) GPIO159
    GpioCtrlRegs.GPEGMUX2.bit.GPIO159 = 0;
    GpioCtrlRegs.GPEMUX2.bit.GPIO159 = 1;
    GpioCtrlRegs.GPEPUD.bit.GPIO159 = 1;

    //GPIO 14 (J8 - 74) - Usado para sinalizacao ou seja para medir o tempo de execucao da funcao pin: 74
    GpioCtrlRegs.GPAGMUX1.bit.GPIO14 = 0;
    GpioCtrlRegs.GPAMUX1.bit.GPIO14 = 0;
    GpioCtrlRegs.GPAPUD.bit.GPIO14 = 1;
    GpioCtrlRegs.GPADIR.bit.GPIO14 = 1;
    GpioCtrlRegs.GPACSEL2.bit.GPIO14 = GPIO_MUX_CPU1;

    //GPIO 15 (J8 - 73) configurado para trabalhar com o CLA
    //GPIO 14 (J8 - 74) - Usado para sinalizacao ou seja para medir o tempo de execucao da funcao pin: 74
    GpioCtrlRegs.GPAGMUX1.bit.GPIO15 = 0;
    GpioCtrlRegs.GPAMUX1.bit.GPIO15 = 0;
    GpioCtrlRegs.GPAPUD.bit.GPIO15 = 1;
    GpioCtrlRegs.GPADIR.bit.GPIO15 = 1;
    GpioCtrlRegs.GPACSEL2.bit.GPIO15 = GPIO_MUX_CPU1CLA;


    EDIS;
}
void Setup_DAC(void)
{
    EALLOW; // Enable EALLOW protected register acess
    //----- Configurte DAC-A control registers Pino 30
    DacbRegs.DACCTL.all = 0x0001;
    // bit 15-8 0's: reserved
    // bit 7-4 0000: DAC PWMSYNC select, not used since LOADMODE=0
    // bit 3 0: reserved
    // bit 2 0: LOADMODE, DACVALA load mode, 0=next SYSCLK, 1=next PWMSYNC specified by SYSCLK
    // bit 1 0: reserved
    // bit 0 1: DACREFSEL, DAC reference select, 0=VDAC/VSSA, 1=ADC VREFHI/VREFLO

    //--- Set DAC-A output to mid-range
    DacbRegs.DACVALS.all = 0x0800; // DACVALS = bits 11-0. bits 15-12 reserved

    //--- Enable DAC-A output
    DacbRegs.DACOUTEN.bit.DACOUTEN = 1; //DAC output enable, 0=disable, 1=enable

    //---DAC-A lock control register
    DacbRegs.DACLOCK.all = 0x0000; // Write a 1 to lock (cannot be cleared once set)


    EDIS; // Disable EALLOW protected register access
}
//******************************************
// EPW1
//******************************************
void Setup_ePWM1(void){
    EALLOW;
    CpuSysRegs.PCLKCR2.bit.EPWM1 = 1; //habilitar clock módulo
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 0; // desabilitar Clock Contador
    //TBPRD=fosc/(2*Fpwm) -1 (para dente de serra)
    //TBCLK=fosc/2
    //TBPRD=fosc/(2*Fpwm) *1/2 = fosc/(4*Fpwm) (para up/down)
    // Fpwm = 1KHz => fosc = 200Mhz => TBRD = (200.10ˆ6)/(4*1*10ˆ3) = 50000
    //EPwm1Regs.TBPRD = 50000; //period Fosc/2*Fpwm or Fosc/4*Fpwm


    EPwm1Regs.TBPRD = 10000; //5Khz => TBRD = (200.10ˆ6)/(4*5*10ˆ3) =10000
    EPwm1Regs.TBPHS.bit.TBPHS = 0; // phase
    EPwm1Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_DISABLE;
    EPwm1Regs.TBCTR = 0; // clear counter
    EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; // counter up/down
    EPwm1Regs.TBCTL.bit.PHSEN = TB_DISABLE; // Disable phase loading
    EPwm1Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1; // Prescale
    EPwm1Regs.TBCTL.bit.CLKDIV = TB_DIV1;


    //EPwm1Regs.CMPA.bit.CMPA = EPwm1Regs.TBPRD >> 1; // duty 50%
    EPwm1Regs.CMPA.bit.CMPA = EPwm1Regs.TBPRD >> 2; // Duty 25%


    EPwm1Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW; // Load registers every ZERO
    EPwm1Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO_PRD;
    EPwm1Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW; // Load registers every ZERO
    EPwm1Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO_PRD;

    EPwm1Regs.AQCTLA.bit.CAU = AQ_CLEAR;
    // set actions for epwm1A (CAU = se CPMA estiver subindo e se encontrar com AQCTLA executa um CLEAR)
    EPwm1Regs.AQCTLA.bit.CAD = AQ_SET; // (CAD = se CPMA estiver Descendo e se encontrar com AQCTLA executa um SET)
    EPwm1Regs.AQCTLA.bit.PRD = AQ_NO_ACTION;
    EPwm1Regs.AQCTLA.bit.ZRO = AQ_NO_ACTION;


    EPwm1Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC; // active Hi complementary
    EPwm1Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE; // enable Dead-Band
//    EPwm1Regs.DBFED.bit.DBFED = 44; // time=DBxED*2*TBclk
//    EPwm1Regs.DBRED.bit.DBRED = 9;
    EPwm1Regs.DBFED.bit.DBFED = 40; // time=DBxED*2*TBclk
    EPwm1Regs.DBRED.bit.DBRED = 20;


    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 1; // Habilitar Clock Contador
    EDIS;
}
//******************************************
// EPW2

//******************************************
void Setup_ePWM2(void){
    EALLOW;
    CpuSysRegs.PCLKCR2.bit.EPWM2 = 1; //habilitar clock módulo
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 0; // desabilitar Clock Contador
    //TBPRD=fosc/(2*Fpwm) -1 (para dente de serra)
    //TBCLK=fosc/2
    //TBPRD=fosc/(2*Fpwm) *1/2 = fosc/(4*Fpwm) (para up/down)
    // Fpwm = 1KHz => fosc = 200Mhz => TBRD = (200.10ˆ6)/(4*1*10ˆ3) = 50000
    //EPwm2Regs.TBPRD = 50000; //period Fosc/2*Fpwm or Fosc/4*Fpwm


    EPwm2Regs.TBPRD = 10000; //5Khz => TBRD = (200.10ˆ6)/(4*5*10ˆ3) =10000
    EPwm2Regs.TBPHS.bit.TBPHS = 0; // phase
    EPwm2Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_DISABLE;
    EPwm2Regs.TBCTR = 0; // clear counter
    EPwm2Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; // counter up/down
    EPwm2Regs.TBCTL.bit.PHSEN = TB_DISABLE; // Disable phase loading
    EPwm2Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1; // Prescale
    EPwm2Regs.TBCTL.bit.CLKDIV = TB_DIV1;


    EPwm2Regs.CMPA.bit.CMPA = EPwm1Regs.TBPRD >> 1; // duty 50%


    EPwm2Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW; // Load registers every ZERO
    EPwm2Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO_PRD;
    EPwm2Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW; // Load registers every ZERO
    EPwm2Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO_PRD;

    EPwm2Regs.AQCTLA.bit.CAU = AQ_CLEAR; // set actions for epwm1A (CAU = se CPMA estiver subindo e se encontrar com AQCTLA executa um CLEAR)
    EPwm2Regs.AQCTLA.bit.CAD = AQ_SET; // (CAD = se CPMA estiver Descendo e se encontrar com AQCTLA executa um SET)
    EPwm2Regs.AQCTLA.bit.PRD = AQ_NO_ACTION;
    EPwm2Regs.AQCTLA.bit.ZRO = AQ_NO_ACTION;

    EPwm2Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC; // active Hi complementary
    EPwm2Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE; // enable Dead-Band
//    EPwm2Regs.DBFED.bit.DBFED = 44; // time=DBxED*2*TBclk
//    EPwm2Regs.DBRED.bit.DBRED = 9;
    EPwm2Regs.DBFED.bit.DBFED = 40; // time=DBxED*2*TBclk
    EPwm2Regs.DBRED.bit.DBRED = 20;

    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 1; // Habilitar Clock Contador
    EDIS;
}

//******************************************
// EPW7

//******************************************
void Setup_ePWM7(void){


    EALLOW;
    CpuSysRegs.PCLKCR2.bit.EPWM7 = 1; //habilitar clock módulo
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 0; // desabilitar Clock Contador
    //TBPRD=fosc/(2*Fpwm) -1 (para dente de serra)
    //TBCLK=fosc/2
    //TBPRD=fosc/(2*Fpwm) *1/2 = fosc/(4*Fpwm) (para up/down)
    // Fpwm = 1KHz => fosc = 200Mhz => TBRD = (200.10ˆ6)/(4*1*10ˆ3) = 50000
    //EPwm2Regs.TBPRD = 50000; //period Fosc/2*Fpwm or Fosc/4*Fpwm


    EPwm7Regs.TBPRD = 3255; //3255 - 15360 Hz    5000 - 10KHz
    EPwm7Regs.CMPA.bit.CMPA = 0;

    EPwm7Regs.TBCTR = 0; // clear counter
    EPwm7Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; // counter up/down

    EPwm7Regs.TBPHS.bit.TBPHS = 0;                 // Set Phase register to zero
    EPwm7Regs.TBCTL.bit.SYNCOSEL = TB_CTR_ZERO;    // Sync down-stream module
    EPwm7Regs.TBCTL.bit.PHSEN = TB_DISABLE; // Disable phase loading  // Master module
    EPwm7Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1; // Prescale  // Clock ratio to SYSCLKOUT
    EPwm7Regs.TBCTL.bit.CLKDIV = TB_DIV1;


    //EPwm7Regs.CMPA.bit.CMPA = EPwm7Regs.TBPRD >> 1; // duty 50%

    EPwm7Regs.TBCTL.bit.PRDLD = TB_SHADOW;
    EPwm7Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW; // Load registers every ZERO
    EPwm7Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO_PRD;

    // Set actions for EPWM7A
    EPwm7Regs.AQCTLA.bit.PRD = AQ_NO_ACTION;
    EPwm7Regs.AQCTLA.bit.ZRO = AQ_NO_ACTION;
    EPwm7Regs.AQCTLA.bit.CAU = AQ_CLEAR; // set actions for epwm1A (CAU = se CPMA estiver subindo e se encontrar com AQCTLA executa um CLEAR)
    EPwm7Regs.AQCTLA.bit.CAD = AQ_SET; // (CAD = se CPMA estiver Descendo e se encontrar com AQCTLA executa um SET)


//    EPwm7Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC; // active Hi complementary
//    EPwm7Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE; // enable Dead-Band
//    EPwm7Regs.DBFED.bit.DBFED = 44; // time=DBxED*2*TBclk
//    EPwm7Regs.DBRED.bit.DBRED = 9;


    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 1; // Habilitar Clock Contador
    EDIS;
}

//******************************************
// EPW8

//******************************************
void Setup_ePWM8(void){
    EALLOW;
    CpuSysRegs.PCLKCR2.bit.EPWM8 = 1; //habilitar clock módulo
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 0; // desabilitar Clock Contador
    //TBPRD=fosc/(2*Fpwm) -1 (para dente de serra)
    //TBCLK=fosc/2
    //TBPRD=fosc/(2*Fpwm) *1/2 = fosc/(4*Fpwm) (para up/down)
    // Fpwm = 1KHz => fosc = 200Mhz => TBRD = (200.10ˆ6)/(4*1*10ˆ3) = 50000
    //EPwm2Regs.TBPRD = 50000; //period Fosc/2*Fpwm or Fosc/4*Fpwm


    EPwm8Regs.TBPRD = 3255; // //3255 - 15360 Hz    5000 - 25KHz
    //EPwm8Regs.CMPA.bit.CMPA = 0;

    EPwm8Regs.TBCTR = 0; // clear counter
    EPwm8Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; // counter up/down

    EPwm8Regs.TBPHS.bit.TBPHS = 0;                 // Saidas sincronizadas. Valor deve ser alterado para gerar a defazagem,
    EPwm8Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN;    // Sync down-stream module
    EPwm8Regs.TBCTL.bit.PHSEN = TB_ENABLE;        // Enable phase loading  // Master module
    EPwm8Regs.TBCTL.bit.PHSDIR = TB_DOWN;         // Phase Up/Down

    EPwm8Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1; // Prescale  // Clock ratio to SYSCLKOUT
    EPwm8Regs.TBCTL.bit.CLKDIV = TB_DIV1;

    EPwm8Regs.CMPA.bit.CMPA = EPwm8Regs.TBPRD >> 1; // duty

    EPwm8Regs.TBCTL.bit.PRDLD = TB_SHADOW;
    EPwm8Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW; // Load registers every ZERO
    EPwm8Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO_PRD;

    // Set actions for EPWM7A
    EPwm8Regs.AQCTLA.bit.PRD = AQ_NO_ACTION;
    EPwm8Regs.AQCTLA.bit.ZRO = AQ_NO_ACTION;
    EPwm8Regs.AQCTLA.bit.CAU = AQ_CLEAR; // set actions for epwm1A (CAU = se CPMA estiver subindo e se encontrar com AQCTLA executa um CLEAR)
    EPwm8Regs.AQCTLA.bit.CAD = AQ_SET; // (CAD = se CPMA estiver Descendo e se encontrar com AQCTLA executa um SET)

    EPwm8Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC; // active Hi complementary
    EPwm8Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE; // enable Dead-Band
    EPwm8Regs.DBFED.bit.DBFED = 44; // time=DBxED*2*TBclk
    EPwm8Regs.DBRED.bit.DBRED = 9;


    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 1; // Habilitar Clock Contador
    EDIS;
}

//******************************************
// EPW10
//******************************************
void Setup_ePWM10(void){
    EALLOW;
    CpuSysRegs.PCLKCR2.bit.EPWM10 = 1; //habilitar clock módulo
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 0; // desabilitar Clock Contador
    EPwm10Regs.TBPRD = 3255; // 3255 - 15360 Hz    5000 - 25KHz  periodo (up/down) 10Khz Clock/4/fpwm LAB PWM

    //Largura do pulso 50%
    EPwm10Regs.CMPA.bit.CMPA = EPwm10Regs.TBPRD >> 1;
    EPwm10Regs.TBPHS.bit.TBPHS = 0; // Phase is 0
    EPwm10Regs.TBCTL.bit.SYNCOSEL = TB_CTR_ZERO;
    EPwm10Regs.TBCTR = 0x0000; // Clear counter
    EPwm10Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; // Count up/down
    EPwm10Regs.TBCTL.bit.PHSEN = TB_DISABLE; // Disable phase loading
    EPwm10Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1; // Clock ratio to SYSCLKOUT
    EPwm10Regs.TBCTL.bit.CLKDIV = TB_DIV1;

    EPwm10Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW; // Load registers every ZERO
    EPwm10Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO_PRD;
    EPwm10Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW; // Load registers every ZERO
    EPwm10Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO_PRD;
    EPwm10Regs.AQCTLA.bit.PRD = AQ_NO_ACTION;
    EPwm10Regs.AQCTLA.bit.ZRO = AQ_NO_ACTION;
    EPwm10Regs.AQCTLA.bit.CAU = AQ_CLEAR; // set actions for EPWM10A
    EPwm10Regs.AQCTLA.bit.CAD = AQ_SET;
    //Trigger ADC
    EPwm10Regs.ETSEL.bit.SOCAEN = 1; // Enable SOC on A group
    EPwm10Regs.ETSEL.bit.SOCASEL = ET_CTR_PRDZERO; // Dispara ADC no topo
    EPwm10Regs.ETPS.bit.SOCAPRD = ET_1ST; // Trigger on every event
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 1;
    EDIS;
}

//******************************************
// ADC
//******************************************
void Setup_ADC (void){
    Uint16 acqps;

    //determine minimum acquisition window (in SYSCLKS) based on resolution
    if(ADC_RESOLUTION_12BIT == AdcaRegs.ADCCTL2.bit.RESOLUTION)
        acqps = 14; // 75ns
    else // resolution is 16-bit
        acqps = 63; // 320ns

    EALLOW;
    CpuSysRegs.PCLKCR13.bit.ADC_A = 1;
    AdcaRegs.ADCCTL2.bit.PRESCALE = 6; //define o clock que chega ao modulo ADC. No caso, o clock que usamos e de 200MHz e
    //o maximo suportado pelo ADC e 50MHz. Assim, colocando o valor 6 teremos essa condica (pg. 1597 do Technical Reference Manual

//    set ADCCLK divider to /4
//    (200MHz/4=50MHz que é o máximo permitido neste ADC usado), o valor usado "6" foi retirado
//    do manual de referência técnica, 11.16.2 ADC_REGS Registers tabela 11-14 2 linha clica em
//    "Go" vai na Figura 11-27 olhar o prescaler que é dividido por 4.
    AdcSetMode(ADC_ADCA, ADC_RESOLUTION_12BIT, ADC_SIGNALMODE_SINGLE);

    // ADC_RESOLUTION_12BIT olha na tabela 11-2 Analog to 12bit Digital Formulas
    AdcaRegs.ADCCTL1.bit.INTPULSEPOS = 1; // Set pulse um ciclo antes do resultado
    AdcaRegs.ADCCTL1.bit.ADCPWDNZ = 1; // Power up the ADC
    DELAY_US(1000); // Delay for 1ms to allow ADC time to power up

    AdcaRegs.ADCSOC0CTL.bit.CHSEL = 3; // ADCINA3 - J3 - Pin 26
    AdcaRegs.ADCSOC0CTL.bit.ACQPS = acqps; // Sample windows is 15 SYSCLK cycles
    AdcaRegs.ADCSOC0CTL.bit.TRIGSEL = 0x17; //Para ativar pelo ePWM7 se for o ePWM10 = 0x17

    AdcaRegs.ADCSOC1CTL.bit.CHSEL = 4; // ADCINA4 - J7 - PIN 69
    AdcaRegs.ADCSOC1CTL.bit.ACQPS = acqps;
    AdcaRegs.ADCSOC1CTL.bit.TRIGSEL = 0x17; //Para ativar pelo ePWM7 se for o ePWM10 = 0x17

    AdcaRegs.ADCINTSEL1N2.bit.INT1SEL = 0x01; // end of S0C1 will set INT1 flag
    AdcaRegs.ADCINTSEL1N2.bit.INT1E = 1; // enable INT1 flag
    AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1; // make sure INT1 flag is cleared
    EDIS;
}

#include "Perif_Setup.h"
#include "sogi.h"
#include "CLA_config.h"


//variaveis propostas pelo professor
uint32_t count=0,index=0;

SPLL_SOGI v_pll;

float vrede = 0;
float vsync = 0;
float phase = 0;
float ampl = 0.5;

volatile SPLL_SOGI cla1_pll;
volatile float vrede_CLA;
volatile float phase_CLA=0;
volatile float ampl_CLA=0.5;
volatile uint32_t count_task=0;

#pragma DATA_SECTION(vrede_CLA,"Cla1ToCpuMsgRAM");

#pragma DATA_SECTION(cla1_pll,"CLADataLS0");
#pragma DATA_SECTION(phase_CLA,"CLADataLS0");
#pragma DATA_SECTION(ampl_CLA,"CLADataLS0");
#pragma DATA_SECTION(count_task,"CLADataLS0");

float plot1[512],plot2[512]; //para tensao da rede e tensao sincronizada (saida do PLL)
float *padc1 = &vrede;
float *padc2 = &vsync;

//Prototipo interrupcoes

__interrupt void isr_timer0(void);
__interrupt void isr_adc(void);

int main(void)
{
    InitSysCtrl(); //Initialize System

    DINT; // Disable CPU interrupts

    InitPieCtrl(); // Initialize the PIE control registers to their default state

    IER = 0x0000; // Disable CPU interrupts
    IFR = 0x0000; // Clear all CPU interrupt flags

    InitPieVectTable(); //Initialize o PIE Vector table

    // Setup dos GPIO
    Setup_GPIO();
    Setup_GPIO_Pwm();

    // interrupcoes

    EALLOW; // habilita acesso aos registradores protegidos
    PieVectTable.TIMER0_INT = &isr_timer0;
    PieVectTable.ADCA1_INT = &isr_adc;

    PieCtrlRegs.PIEIER1.bit.INTx7 = 1; // Timer 0
    PieCtrlRegs.PIEIER1.bit.INTx1 = 1; // ADC

    EDIS; // desabilita acesso aos registradores protegidos
    // IER = 1; //habilita a coluna 1
    // IER = 0x10 //desabilita a coluna 1 e habilita a coluna 2

    IER |= M_INT1;

    // configura timer
    InitCpuTimers();
    ConfigCpuTimer(&CpuTimer0, 200, 1000000);//timer0 usado para sinalizacao
    CpuTimer0Regs.TCR.all = 0x4000;


    //configurar PWM
    Setup_ePWM1();
    Setup_ePWM7();
    Setup_ePWM8();
    Setup_ePWM10();

    //configura AD
    Setup_ADC();

    //Configura DAC
    Setup_DAC();

    //Configura CLA
    CLA1_ConfigCLAMemory();
    CLA1_InitCpu1Cla1();

    //configuracao do SOGI
    SOGI_init(60,32.5520833E-06,&v_pll); //valores caluculados usando o documento do Solar. o valor 60 sao a frequencia que se quer sintonizar, ou seja, 60Hz
    SOGI_coeff_update(32.5520833E-06,376.99112,0.7,&v_pll);

    //Atualiza variaveis para o CLA
    SOGI_init(60,32.5520833E-06,&cla1_pll); //valores caluculados usando o documento do Solar. o valor 60 sao a frequencia que se quer sintonizar, ou seja, 60Hz
    SOGI_coeff_update(32.5520833E-06,376.99112,0.7,&cla1_pll);

    EINT; // Enable Global interrupt INTM
    ERTM; // Enable Global realtime interrupt DBGM


    GpioDataRegs.GPADAT.bit.GPIO31 = 1;  //Led azul
    GpioDataRegs.GPBDAT.bit.GPIO34 = 0; //Led vermelho

     while(1){
     for (count = 0; count < 0x00FFFFFF; count++) {

     }
     GpioDataRegs.GPBTOGGLE.bit.GPIO34 = 1;
     }

}
__interrupt void isr_timer0(void){
    GpioDataRegs.GPATOGGLE.bit.GPIO31 = 1; //Led azul

    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}

__interrupt void isr_adc(void){
    GpioDataRegs.GPADAT.bit.GPIO14 = 1; //incluido para o calculo do tempo gasto

    vrede = 0.0005*((int)AdcaResultRegs.ADCRESULT0 - 0x7FF); //recebe leitura do sinal da rede através do ResultReg e o valor 0.0005 deixa a entrada da rede variando entre -1 e 1
    //AdcaResultRegs.ADCRESULT1;

    v_pll.u[0] = vrede;//valor da rede vai para o PLL atraves do u (entrada do PLL)
    SPLL_SOGI_CALC(&v_pll); //passa o valor para a funcao de PLL

    vsync = v_pll.sin_; //vsync foi colocado aqui para que possamos ve-lo em nosso plot

    //phase - fase que se quer impor; theta é o angulo de defasagem da rede que se quer ler;ampl - aplitude que se quer impor
    //depois o valor deve ser normalizado para ficar dentro do intervalo de CMPA (0 a PRD=3255). No caso foi colocado 1627 (metade do PRD), pois o intervalo do valor do seno fica entre 0 e 2

    EPwm7Regs.CMPA.bit.CMPA = (uint16_t) (1627.0 *(1.0 + ampl * __sin(v_pll.theta[1] + phase)));


    //Essa parte abaixo foi removida para que se possa ter o mesmo tempo no CLA e no AD
//    EALLOW;
//    //manda o valor da senoide calculada para o DA. como o registrador do DA é de 12bit - vai de 0 a 4096 -  e foi usado a metade para deixar o valor normalizado, ja que o seno varia de 0 a 2
//    DacbRegs.DACVALS.bit.DACVALS = (uint16_t)(2047.0 * (1.0 + ampl * __sin(v_pll.theta[1] + phase)));
//    EDIS;

    //Nesse trabalho nao sera usada plotagem
//    plot1[index] = *padc1;
//    plot2[index] = *padc2;
//    index = (index == 511) ? 0: (index+1);

    AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1; //clear INT1 flag
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;

    GpioDataRegs.GPADAT.bit.GPIO14 = 0; //incluido para o calculo do tempo gasto
}
/*
 *Definicoes em CLA_Config.h
 *Interrupcoes das tarefas do CLA
 * */

__interrupt void CLA1_isr1(void){
    //count_task++;
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP11;
}
__interrupt void CLA1_isr2(void){
    asm("  ESTOP0");
}
__interrupt void CLA1_isr3(void){
    asm("  ESTOP0");
}
__interrupt void CLA1_isr4(void){
   asm("  ESTOP0");
}
__interrupt void CLA1_isr5(void){
   asm("  ESTOP0");
}
__interrupt void CLA1_isr6(void){
    asm("  ESTOP0");
}
__interrupt void CLA1_isr7(void){
    asm("  ESTOP0");
}
__interrupt void CLA1_isr8(void){
    asm("  ESTOP0");
}

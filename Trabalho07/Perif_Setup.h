/*
* Perif_Setup.h
*
* Created on: 6 de jul de 2021
* Author: paulo e Wellington
*/
#ifndef PERIF_SETUP_H_
#define PERIF_SETUP_H_

#include "F28x_Project.h"

void Setup_GPIO(void);

void Setup_GPIO_Pwm(void);

void Setup_DAC (void);
void Setup_ADC (void);

void Setup_ePWM1 (void);
void Setup_ePWM2 (void);
void Setup_ePWM7 (void);
void Setup_ePWM8 (void);
void Setup_ePWM10 (void); //Será o gatilho da conversão analógico/digital

#endif /* PERIF_SETUP_H_ */

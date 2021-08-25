/*
 * CLA.h
 *
 *  Created on: 24 de ago de 2021
 *      Author:  Wellington e Paulo
 */

#ifndef CLA_H_
#define CLA_H_

#include "F2837xD_Cla_defines.h"
#include "CLAMath.h"
#include "F28x_Project.h"
#include "sogi.h"

extern volatile float vrede_CLA;
extern volatile SPLL_SOGI cla1_pll;
extern volatile float phase_CLA;
extern volatile float ampl_CLA;
extern volatile uint32_t count_task;

//task's
__interrupt void CLA1Task1(void);
__interrupt void CLA1Task2(void);
__interrupt void CLA1Task3(void);
__interrupt void CLA1Task4(void);
__interrupt void CLA1Task5(void);
__interrupt void CLA1Task6(void);
__interrupt void CLA1Task7(void);
__interrupt void CLA1Task8(void);


#endif /* CLA_H_ */

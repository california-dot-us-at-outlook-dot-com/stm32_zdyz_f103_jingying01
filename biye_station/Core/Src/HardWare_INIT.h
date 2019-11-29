/*
 * HardWare_INIT.h
 *
 *  Created on: 2019年11月21日
 *      Author: cal
 */

#ifndef SRC_HARDWARE_INIT_H_
#define SRC_HARDWARE_INIT_H_

#include "main.h"

void RCC_INIT(uint8_t PLL);
void FSMC_LCD_INIT();
void JTAG_Set(uint8_t mode);
void sysTick_Set();

#endif /* SRC_HARDWARE_INIT_H_ */

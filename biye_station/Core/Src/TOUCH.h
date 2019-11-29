/*
 * TOUCH.h
 *
 *  Created on: 2019年11月21日
 *      Author: cal
 */

#ifndef SRC_TOUCH_H_
#define SRC_TOUCH_H_

#include "main.h"

#include "STRUCT_DEFINE.h"

#define TCLK (((GPIO_S*)(&(GPIOB->ODR)))->BIT1)//PB1
#define TDIN (((GPIO_S*)(&(GPIOF->ODR)))->BIT9)//PF9
#define DOUT (((GPIO_S*)(&(GPIOB->IDR)))->BIT2)//PB2
#define TPEN (((GPIO_S*)(&(GPIOF->IDR)))->BIT10)//PF10
#define TCS (((GPIO_S*)(&(GPIOF->ODR)))->BIT11)//PF11

void TOUCH_GPIO_Init();
uint8_t TP_Read_XY2(uint16_t *x,uint16_t *y);
uint8_t get_Pen_XY(uint16_t *x, uint16_t *y);
#endif /* SRC_TOUCH_H_ */

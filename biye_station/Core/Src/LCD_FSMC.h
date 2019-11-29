/*
 * LCD_FSMC.h
 *
 *  Created on: Nov 18, 2019
 *      Author: cal
 */

#ifndef SRC_LCD_FSMC_H_
#define SRC_LCD_FSMC_H_

#include"main.h"

void delay_us(uint32_t t);

void delay_ms(uint16_t delay_val);

void LCD_SetXY(uint16_t x, uint16_t y);

void LCD_WR_REG(uint16_t regval);

void LCD_WR_DATA(uint16_t datval);

void LCD_Init();

void LCD_WriteReg(uint16_t LCD_Reg, uint16_t LCD_RegValue);

void drawLine(uint16_t startX, uint16_t startY, uint16_t endX, uint16_t endY, uint16_t color);

void drawRect(uint16_t startX, uint16_t startY, uint16_t endX, uint16_t endY, uint16_t color);

void drawRectWithBorder(uint16_t startX, uint16_t startY, uint16_t endX, uint16_t endY, uint16_t color, uint8_t border);

#endif /* SRC_LCD_FSMC_H_ */

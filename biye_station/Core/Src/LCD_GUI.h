/*
 * LCD_GUI.h
 *
 *  Created on: Nov 18, 2019
 *      Author: cal
 */

#ifndef SRC_LCD_GUI_H_
#define SRC_LCD_GUI_H_

#include "LCD_FSMC.h"
#include "UNICODE.h"
#include "FATFS14/ff.h"

//char的结构体未使用， 用的是uint8_t[17]
typedef struct{
	uint8_t Char;
	uint8_t Module[16];
}Char_Module;

typedef struct{
	uint32_t *Word;
	uint16_t Module[16];
}Word_Module;

typedef struct Button_struct{
	uint16_t start_x;
	uint16_t start_y;
	uint16_t end_x;
	uint16_t end_y;
	uint16_t font_color;
	uint16_t back_color;
	uint16_t border_color;
	uint16_t id;
	uint16_t isPressed;
	uint16_t isRelated;
	uint16_t onePressedFlag;
	uint8_t name[12];
	void(*handler)(uint8_t) ;
}BUTTON_S;

void drawButton(uint8_t *name, uint16_t start_x, uint16_t start_y, uint16_t end_x, uint16_t end_y, uint16_t font_color, uint16_t back_color, uint16_t border_color);
void printNumWithClear(uint16_t x, uint16_t y, int32_t Num, uint8_t clearNum, uint16_t font_color, uint16_t back_color);
void printNum(uint16_t x, uint16_t y, int32_t Num, uint16_t font_color, uint16_t back_color);
void clearScreen(uint16_t color);
void drawSquare(uint16_t startX, uint16_t startY, uint16_t endX, uint16_t endY, uint16_t color);
void printString(uint16_t x, uint16_t y, uint8_t charTable[][17], Word_Module *wordTable, uint8_t* str, uint16_t font_color, uint16_t back_color);
void ButtonCreate(uint8_t *name, uint8_t id, uint16_t start_x, uint16_t start_y, uint16_t end_x, uint16_t end_y, void(*handle)(uint8_t), uint16_t font_color, uint16_t back_color, uint16_t border_color);
void ScreenScan();
void Button_dothings();
void ButtonsScan(uint8_t isPressed);
uint8_t printMultiString(uint16_t x, uint16_t y, uint8_t *p, uint16_t font_color, uint16_t back_color);
#endif /* SRC_LCD_GUI_H_ */

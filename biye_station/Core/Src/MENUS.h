/*
 * MENUS.h
 *
 *  Created on: 2019年11月23日
 *      Author: cal
 */

#ifndef SRC_MENUS_H_
#define SRC_MENUS_H_

#include "main.h"
#include "LCD_GUI.h"

void GUI_Menu01_Create(void(*menu_handler)(), uint8_t id);
void menu01_handler();
void GUI_Menu01_Scan();
void Menu02_loop();
void Menu01_loop();
#endif /* SRC_MENUS_H_ */

/*
 * Files_Handler.h
 *
 *  Created on: 2019年11月25日
 *      Author: cal
 */

#ifndef SRC_FILES_HANDLER_H_
#define SRC_FILES_HANDLER_H_

#include "stm32f1xx_hal.h"
#include "FATFS14/ff.h"
#include "LCD_GUI.h"


typedef enum {
	txt=1,
	bin,
	img,
	wav,
	dat,
	mp3,
	jpg,
	bmp,
	png,
	gif,
	tmp,
}FILE_TYPE;


uint8_t Files_Handler(uint8_t *name, uint8_t type);

#endif /* SRC_FILES_HANDLER_H_ */

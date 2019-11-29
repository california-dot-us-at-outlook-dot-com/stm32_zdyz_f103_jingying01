/*
 * Files_Handler.c
 *
 *  Created on: 2019年11月25日
 *      Author: cal
 */


#include "Files_Handler.h"

uint8_t file_buf[1024*16];



uint8_t Files_Handler(uint8_t *name, uint8_t type){

	uint8_t res=255;
	FIL fil01;
	FILINFO filinfo01;

	res = f_open(&fil01, name, FA_READ | FA_WRITE);
	if(res){
		for(int i=0;(i<5)&&(res);i++){
			SD_Init();
			res = f_open(&fil01, name, FA_READ | FA_WRITE);
		}
		if(res){
			return res;
		}
	}
	uint32_t ByteRead=0;
	for(;;){
		res = f_read(&fil01, fil01.buf, 512, &ByteRead);
		if((res != FR_OK)){
			f_close(&fil01);
			return res;
		}

		{
			//handle with 512 BYTE data
			extern uint8_t CharTable[][17];
			extern Word_Module WordTable[];

			printString(0, 250, CharTable, WordTable, fil01.buf, 0xffff, 0x0000);
		}

		if(ByteRead < 512){
			break;
		}
	}

	f_close(&fil01);

	return 0;
}


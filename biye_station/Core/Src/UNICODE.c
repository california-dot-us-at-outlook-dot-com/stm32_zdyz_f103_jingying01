/*
 * UNICODE.c
 *
 *  Created on: 2019年11月26日
 *      Author: cal
 */


#include "UNICODE.h"

uint32_t UTF8_2_UNICODE(uint8_t *str, uint8_t *size){

	uint8_t num = 0;
	uint32_t uni = 0;
	uint8_t uni_head = 0;
	if(!str){
		return 0xFFFFFFFF;
	}
	for(;num || (!uni_head);str++){
		if(((*str&0xE0)) == 0xC0){			//0b110
			uni_head = 1;
			num = 2;
			*size = 2;
			uni = (*str&(~0xE0)) << 1*6;
			num--;
		}else if(((*str&0xF0)) == 0xE0){		//0b1110
			uni_head = 1;
			num = 3;
			*size = 3;
			uni = (*str&(~0xF0)) << 2*6;
			num--;
		}else if(((*str&0xF8)) == 0xF0){		//0b11110
			uni_head = 1;
			num = 4;
			*size = 4;
			uni = (*str&(~0xF8)) << 3*6;
			num--;
		}else if(((*str)&0xFC) == 0xF8){		//0b111110
			uni_head = 1;
			num = 5;
			*size = 5;
			uni = (*str&(~0xFC)) << 4*6;
			num--;
		}else if(((*str)&0xFE) == 0xFC){		//0b1111110
			uni_head = 1;
			num = 6;
			*size = 6;
			uni = (*str&(~0xFE)) << 5*6;
			num--;
		}else if(((*str)&0xFF) == 0xFE){		//0b11111110
			uni_head = 1;
			num = 7;
			*size = 7;
			uni = 0;
			num--;
		}else if(((*str)&0xC0) == 0x80){		//0b10
			if(num){
				uni += (*str&(~0xC0)) << (num-1)*6;
				num--;
			}
		}else if(((*str)&0x80) == 0x00){		//0b0
			num = 1;
			*size = 1;
			uni = *str;
			uni_head = 1;
			num--;
		}

	}
	return uni;

}

/*
 * LCD_FSMC.c
 *
 *  Created on: Nov 18, 2019
 *      Author: cal
 */

#include "LCD_FSMC.h"
#include "HardWare_INIT.h"

//void delay_us(uint32_t t){
//	int i,j;
//
//	int a=0;
//
//	for(i=0;i<t;i++){
//		for(j=0;j<100;j++){
//			a++;
//		}
//	}
//
//}

void delay_us(uint32_t t){
	__asm(	"mov r1, r0\n"
			"ldr r2, =7\n"			//subs 和 bne 2个指令耗时10个时钟周期(测试得到的结果），所以36×t个循环。
			"mul r0, r1, r2\n"
			"mov r1, r1, lsr #3\n"
			"add r0, r0, r1\n"
			"mov r1, r1, lsr #1\n"
			"add r0, r0, r1\n"
			"loop:\n"
			"subs r0, r0, #1\n"
			"bne loop\n"
		);
}

void delay_ms(uint16_t delay_val){
	HAL_Delay(delay_val);
}

#define LCD_REG (uint16_t *)((0x6C000000 | 0x000007FE)+0)
#define LCD_DAT (uint16_t *)((0x6C000000 | 0x000007FE)+2)

void LCD_WR_REG(uint16_t regval){
	*(LCD_REG)=regval;
}

void LCD_WR_DATA(uint16_t datval){
	*(LCD_DAT)=datval;
}

void LCD_WriteReg(uint16_t LCD_Reg, uint16_t LCD_RegValue){
	*(LCD_REG) = LCD_Reg;
	*(LCD_DAT) = LCD_RegValue;
}



void LCD_WriteGRAM(uint16_t RGB_Code){
	LCD_WR_REG(0x2c);
	LCD_WR_DATA(RGB_Code);
}


void LCD_SetXY(uint16_t x, uint16_t y){
	uint16_t x_l=x;
	uint16_t x_h=(x>>8);

	uint16_t y_l=y;
	uint16_t y_h=(y>>8);

	LCD_WR_REG(0x2a);
	LCD_WR_DATA(x_h);
	LCD_WR_DATA(x_l);

	LCD_WR_REG(0x2b);
	LCD_WR_DATA(y_h);
	LCD_WR_DATA(y_l);

}

void LCD_DIR(){

}

void LCD_Init(){

	FSMC_LCD_INIT();

	LCD_WR_REG(0xCF);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0xC1);
	LCD_WR_DATA(0X30);
	LCD_WR_REG(0xED);
	LCD_WR_DATA(0x64);
	LCD_WR_DATA(0x03);
	LCD_WR_DATA(0X12);
	LCD_WR_DATA(0X81);
	LCD_WR_REG(0xE8);
	LCD_WR_DATA(0x85);
	LCD_WR_DATA(0x10);
	LCD_WR_DATA(0x7A);
	LCD_WR_REG(0xCB);
	LCD_WR_DATA(0x39);
	LCD_WR_DATA(0x2C);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x34);
	LCD_WR_DATA(0x02);
	LCD_WR_REG(0xF7);
	LCD_WR_DATA(0x20);
	LCD_WR_REG(0xEA);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x00);
	LCD_WR_REG(0xC0);    //Power control
	LCD_WR_DATA(0x1B);   //VRH[5:0]
	LCD_WR_REG(0xC1);    //Power control
	LCD_WR_DATA(0x01);   //SAP[2:0];BT[3:0]
	LCD_WR_REG(0xC5);    //VCM control
	LCD_WR_DATA(0x30); 	 //3F
	LCD_WR_DATA(0x30); 	 //3C
	LCD_WR_REG(0xC7);    //VCM control2
	LCD_WR_DATA(0XB7);
	LCD_WR_REG(0x36);    // Memory Access Control
	LCD_WR_DATA(0x48);
	LCD_WR_REG(0x3A);
	LCD_WR_DATA(0x55);
	LCD_WR_REG(0xB1);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x1A);
	LCD_WR_REG(0xB6);    // Display Function Control
	LCD_WR_DATA(0x0A);
	LCD_WR_DATA(0xA2);
	LCD_WR_REG(0xF2);    // 3Gamma Function Disable
	LCD_WR_DATA(0x00);
	LCD_WR_REG(0x26);    //Gamma curve selected
	LCD_WR_DATA(0x01);
	LCD_WR_REG(0xE0);    //Set Gamma
	LCD_WR_DATA(0x0F);
	LCD_WR_DATA(0x2A);
	LCD_WR_DATA(0x28);
	LCD_WR_DATA(0x08);
	LCD_WR_DATA(0x0E);
	LCD_WR_DATA(0x08);
	LCD_WR_DATA(0x54);
	LCD_WR_DATA(0XA9);
	LCD_WR_DATA(0x43);
	LCD_WR_DATA(0x0A);
	LCD_WR_DATA(0x0F);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x00);
	LCD_WR_REG(0XE1);    //Set Gamma
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x15);
	LCD_WR_DATA(0x17);
	LCD_WR_DATA(0x07);
	LCD_WR_DATA(0x11);
	LCD_WR_DATA(0x06);
	LCD_WR_DATA(0x2B);
	LCD_WR_DATA(0x56);
	LCD_WR_DATA(0x3C);
	LCD_WR_DATA(0x05);
	LCD_WR_DATA(0x10);
	LCD_WR_DATA(0x0F);
	LCD_WR_DATA(0x3F);
	LCD_WR_DATA(0x3F);
	LCD_WR_DATA(0x0F);
	LCD_WR_REG(0x2B);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x01);
	LCD_WR_DATA(0x3f);
	LCD_WR_REG(0x2A);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0xef);
	LCD_WR_REG(0x11); //Exit Sleep
	delay_ms(120);
	LCD_WR_REG(0x29); //display on

	LCD_WriteReg(0x36, 0x08);	//竖屏，扫描方向
	LCD_WriteReg(0x03,0x1003);	//坐标
}


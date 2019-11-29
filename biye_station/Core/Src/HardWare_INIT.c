/*
 * HardWare_INIT.c
 *
 *  Created on: 2019年11月21日
 *      Author: cal
 */

#include "HardWare_INIT.h"

//JTAG模式设置,用于设置JTAG的模式
//mode:jtag,swd模式设置;00,全使能;01,使能SWD;10,全关闭;
//#define JTAG_SWD_DISABLE   0X02
//#define SWD_ENABLE         0X01
//#define JTAG_SWD_ENABLE    0X00
void JTAG_Set(uint8_t mode)
{
	uint32_t temp;
	temp=mode;
	temp<<=25;
	RCC->APB2ENR|=1<<0;     //开启辅助时钟
	AFIO->MAPR&=0XF8FFFFFF; //清除MAPR的[26:24]
	AFIO->MAPR|=temp;       //设置jtag模式
}

void sysTick_Set(){
	SysTick->CTRL |= 0x07;
	SysTick->LOAD = 72000;
}

//设置向量表偏移地址
//NVIC_VectTab:基址
//Offset:偏移量
void MY_NVIC_SetVectorTable(uint32_t NVIC_VectTab, uint32_t Offset)
{
	SCB->VTOR = NVIC_VectTab|(Offset & (uint32_t)0x1FFFFF80);//设置NVIC的向量表偏移寄存器
	//用于标识向量表是在CODE区还是在RAM区
}

void MYRCC_DeInit(void)
{
 	RCC->APB1RSTR = 0x00000000;//复位结束
	RCC->APB2RSTR = 0x00000000;

  	RCC->AHBENR = 0x00000014;  //睡眠模式闪存和SRAM时钟使能.其他关闭.
  	RCC->APB2ENR = 0x00000000; //外设时钟关闭.
  	RCC->APB1ENR = 0x00000000;
	RCC->CR |= 0x00000001;     //使能内部高速时钟HSION
	RCC->CFGR &= 0xF8FF0000;   //复位SW[1:0],HPRE[3:0],PPRE1[2:0],PPRE2[2:0],ADCPRE[1:0],MCO[2:0]
	RCC->CR &= 0xFEF6FFFF;     //复位HSEON,CSSON,PLLON
	RCC->CR &= 0xFFFBFFFF;     //复位HSEBYP
	RCC->CFGR &= 0xFF80FFFF;   //复位PLLSRC, PLLXTPRE, PLLMUL[3:0] and USBPRE
	RCC->CIR = 0x00000000;     //关闭所有中断
	//配置向量表
#ifdef  VECT_TAB_RAM
	MY_NVIC_SetVectorTable(0x20000000, 0x0);
#else
	MY_NVIC_SetVectorTable(0x08000000,0x0);
#endif
}

void RCC_INIT(uint8_t PLL){
	unsigned char temp=0;
	MYRCC_DeInit();		  //复位并配置向量表
 	RCC->CR|=0x00010000;  //外部高速时钟使能HSEON
	while(!(RCC->CR>>17));//等待外部时钟就绪
	RCC->CFGR=0X00000400; //APB1=DIV2;APB2=DIV1;AHB=DIV1;
	PLL-=2;				  //抵消2个单位（因为是从2开始的，设置0就是2）
	RCC->CFGR|=PLL<<18;   //设置PLL值 2~16
	RCC->CFGR|=1<<16;	  //PLLSRC ON
	FLASH->ACR|=0x32;	  //FLASH 2个延时周期
	RCC->CR|=0x01000000;  //PLLON
	while(!(RCC->CR>>25));//等待PLL锁定
	RCC->CFGR|=0x00000002;//PLL作为系统时钟
	while(temp!=0x02)     //等待PLL作为系统时钟设置成功
	{
		temp=RCC->CFGR>>2;
		temp&=0x03;
	}
}

void FSMC_LCD_INIT(){
	RCC->AHBENR|=1<<8;     	 	//使能FSMC时钟
  	RCC->APB2ENR|=1<<3;     	//使能PORTB时钟
	RCC->APB2ENR|=1<<5;     	//使能PORTD时钟
	RCC->APB2ENR|=1<<6;     	//使能PORTE时钟
 	RCC->APB2ENR|=1<<8;      	//使能PORTG时钟
	GPIOB->CRL&=0XFFFFFFF0;		//PB0 推挽输出 背光
	GPIOB->CRL|=0X00000003;
	GPIOB->ODR |= 0x01;
	//PORTD复用推挽输出
	GPIOD->CRH&=0X00FFF000;
	GPIOD->CRH|=0XBB000BBB;
	GPIOD->CRL&=0XFF00FF00;
	GPIOD->CRL|=0X00BB00BB;
	//PORTE复用推挽输出
	GPIOE->CRH&=0X00000000;
	GPIOE->CRH|=0XBBBBBBBB;
	GPIOE->CRL&=0X0FFFFFFF;
	GPIOE->CRL|=0XB0000000;
	//PORTG12复用推挽输出
	GPIOG->CRH&=0XFFF0FFFF;
	GPIOG->CRH|=0X000B0000;
	GPIOG->CRL&=0XFFFFFFF0;//PG0->RS
	GPIOG->CRL|=0X0000000B;

	//寄存器清零
	//bank1有NE1~4,每一个有一个BCR+TCR，所以总共八个寄存器。
	//这里我们使用NE4 ，也就对应BTCR[6],[7]。
	FSMC_Bank1->BTCR[6]=0X00000000;
	FSMC_Bank1->BTCR[7]=0X00000000;
	FSMC_Bank1E->BWTR[6]=0X00000000;
	//操作BCR寄存器	使用异步模式
	FSMC_Bank1->BTCR[6]|=1<<12;		//存储器写使能
	FSMC_Bank1->BTCR[6]|=1<<14;		//读写使用不同的时序
	FSMC_Bank1->BTCR[6]|=1<<4; 		//存储器数据宽度为16bit
	//操作BTR寄存器
	//读时序控制寄存器
	FSMC_Bank1->BTCR[7]|=0<<28;		//模式A
	FSMC_Bank1->BTCR[7]|=1<<0; 		//地址建立时间（ADDSET）为2个HCLK 1/36M=27ns(实际>200ns)
	//因为液晶驱动IC的读数据的时候，速度不能太快，尤其对1289这个IC。
	FSMC_Bank1->BTCR[7]|=0XF<<8;  	//数据保存时间为16个HCLK
	//写时序控制寄存器
	FSMC_Bank1E->BWTR[6]|=0<<28; 	//模式A
	FSMC_Bank1E->BWTR[6]|=0<<0;		//地址建立时间（ADDSET）为1个HCLK
 	//4个HCLK（HCLK=72M）因为液晶驱动IC的写信号脉宽，最少也得50ns。72M/4=24M=55ns
	FSMC_Bank1E->BWTR[6]|=3<<8; 	//数据保存时间为4个HCLK
	//使能BANK1,区域4
	FSMC_Bank1->BTCR[6]|=1<<0;		//使能BANK1，区域4

}

/*
 * TOUCH.c
 *
 *  Created on: 2019年11月21日
 *      Author: cal
 */


#include "TOUCH.h"

uint16_t touch_x=0;
uint16_t touch_y=0;

uint16_t touch_onLCD_x=0;
uint16_t touch_onLCD_y=0;

void TOUCH_GPIO_Init(){

	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOF_CLK_ENABLE();

	((GPIO_CONFIG_S*)(&(GPIOB->CRL)))->GPIO2 = 0b1000;	//DOUT(MISO)
	(((GPIO_S*)(&(GPIOB->ODR)))->BIT2) = 1;				//PULL UP

	((GPIO_CONFIG_S*)(&(GPIOB->CRL)))->GPIO1 = 0b0001;	//TCLK
	(((GPIO_S*)(&(GPIOB->ODR)))->BIT2) = 0;				//

	((GPIO_CONFIG_S*)(&(GPIOF->CRH)))->GPIO2 = 0b1000;	//TPEN 10-8=2
	(((GPIO_S*)(&(GPIOB->ODR)))->BIT10) = 1;				//PULL UP

	((GPIO_CONFIG_S*)(&(GPIOF->CRH)))->GPIO3 = 0b0001;	//TCS 11-8=3
	(((GPIO_S*)(&(GPIOB->ODR)))->BIT11) = 0;				//

	((GPIO_CONFIG_S*)(&(GPIOF->CRH)))->GPIO1 = 0b0001;	//TDIN 9-8=1
	(((GPIO_S*)(&(GPIOB->ODR)))->BIT9) = 0;				//

}

//SPI写数据
//向触摸屏IC写入1byte数据
//num:要写入的数据
void TP_Write_Byte(uint8_t num)
{
	uint8_t count=0;
	for(count=0;count<8;count++)
	{
		if(num&0x80)TDIN=1;
		else TDIN=0;
		num<<=1;
		TCLK=0;
		delay_us(1);
		TCLK=1;		//上升沿有效
	}
}
//SPI读数据
//从触摸屏IC读取adc值
//CMD:指令
//返回值:读到的数据
uint16_t TP_Read_AD(uint8_t CMD)
{
	uint8_t count=0;
	uint16_t Num=0;
	TCLK=0;		//先拉低时钟
	TDIN=0; 	//拉低数据线
	TCS=0; 		//选中触摸屏IC
	TP_Write_Byte(CMD);//发送命令字
	delay_us(6);//ADS7846的转换时间最长为6us
	TCLK=0;
	delay_us(1);
	TCLK=1;		//给1个时钟，清除BUSY
	delay_us(1);
	TCLK=0;
	for(count=0;count<16;count++)//读出16位数据,只有高12位有效
	{
		Num<<=1;
		TCLK=0;	//下降沿有效
		delay_us(1);
 		TCLK=1;
 		if(DOUT)Num++;
	}
	Num>>=4;   	//只有高12位有效.
	TCS=1;		//释放片选
	return(Num);
}
//读取一个坐标值(x或者y)
//连续读取READ_TIMES次数据,对这些数据升序排列,
//然后去掉最低和最高LOST_VAL个数,取平均值
//xy:指令（CMD_RDX/CMD_RDY）
//返回值:读到的数据
#define READ_TIMES 5 	//读取次数
#define LOST_VAL 1	  	//丢弃值
uint16_t TP_Read_XOY(uint8_t xy)
{
	uint16_t i, j;
	uint16_t buf[READ_TIMES];
	uint16_t sum=0;
	uint16_t temp;
	for(i=0;i<READ_TIMES;i++)buf[i]=TP_Read_AD(xy);
	for(i=0;i<READ_TIMES-1; i++)//排序
	{
		for(j=i+1;j<READ_TIMES;j++)
		{
			if(buf[i]>buf[j])//升序排列
			{
				temp=buf[i];
				buf[i]=buf[j];
				buf[j]=temp;
			}
		}
	}
	sum=0;
	for(i=LOST_VAL;i<READ_TIMES-LOST_VAL;i++)sum+=buf[i];
	temp=sum/(READ_TIMES-2*LOST_VAL);
	return temp;
}

#define CMD_RDX 0xd0
#define CMD_RDY 0x90

//读取x,y坐标
//最小值不能少于100.
//x,y:读取到的坐标值
//返回值:0,失败;1,成功。
uint8_t TP_Read_XY(uint16_t *x,uint16_t *y)
{
	uint16_t xtemp,ytemp;
	xtemp=TP_Read_XOY(CMD_RDX);
	ytemp=TP_Read_XOY(CMD_RDY);
	//if(xtemp<100||ytemp<100)return 0;//读数失败
	*x=xtemp;
	*y=ytemp;
	return 1;//读数成功
}
//连续2次读取触摸屏IC,且这两次的偏差不能超过
//ERR_RANGE,满足条件,则认为读数正确,否则读数错误.
//该函数能大大提高准确度
//x,y:读取到的坐标值
//返回值:0,失败;1,成功。
#define ERR_RANGE 50 //误差范围
uint8_t TP_Read_XY2(uint16_t *x,uint16_t *y)
{
	uint16_t x1,y1;
 	uint16_t x2,y2;
 	uint8_t flag;
    flag=TP_Read_XY(&x1,&y1);
    if(flag==0)return(0);
    flag=TP_Read_XY(&x2,&y2);
    if(flag==0)return(0);
    if(((x2<=x1&&x1<x2+ERR_RANGE)||(x1<=x2&&x2<x1+ERR_RANGE))//前后两次采样在+-50内
    &&((y2<=y1&&y1<y2+ERR_RANGE)||(y1<=y2&&y2<y1+ERR_RANGE)))
    {
        *x=(x1+x2)/2;
        *y=(y1+y2)/2;
        return 1;
    }else return 0;
}

uint8_t get_Pen_XY(uint16_t *touch_onLCD_x, uint16_t *touch_onLCD_y){
	uint16_t touch_x, touch_y;

	if(!TPEN){
		TP_Read_XY2(&touch_x,&touch_y);
		*touch_onLCD_x=(touch_x-200)*(240.0/3700);
		*touch_onLCD_y=(touch_y-200)*(320.0/3700);
		return 1;
	}
	return 0;
}

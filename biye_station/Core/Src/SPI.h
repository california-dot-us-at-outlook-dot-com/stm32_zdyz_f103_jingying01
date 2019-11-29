/*
 * SPI.h
 *
 *  Created on: 2019年11月23日
 *      Author: cal
 */

#ifndef SRC_SPI_H_
#define SRC_SPI_H_

#include "main.h"

// SPI总线速度设置
#define SPI_SPEED_2   		0
#define SPI_SPEED_4   		1
#define SPI_SPEED_8   		2
#define SPI_SPEED_16  		3
#define SPI_SPEED_32 		4
#define SPI_SPEED_64 		5
#define SPI_SPEED_128 		6
#define SPI_SPEED_256 		7

void SPI2_Init(void);			 //初始化SPI2口
void SPI2_SetSpeed(uint8_t SpeedSet); //设置SPI2速度
uint8_t SPI2_ReadWriteByte(uint8_t TxData);//SPI2总线读写一个字节


#endif /* SRC_SPI_H_ */

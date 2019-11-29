/*
 * STRUCT_DEFINE.h
 *
 *  Created on: 2019年11月23日
 *      Author: cal
 */

#ifndef SRC_STRUCT_DEFINE_H_
#define SRC_STRUCT_DEFINE_H_

typedef struct{
    uint32_t BIT0:1;
    uint32_t BIT1:1;
    uint32_t BIT2:1;
    uint32_t BIT3:1;
    uint32_t BIT4:1;
    uint32_t BIT5:1;
    uint32_t BIT6:1;
    uint32_t BIT7:1;
    uint32_t BIT8:1;
    uint32_t BIT9:1;
    uint32_t BIT10:1;
    uint32_t BIT11:1;
    uint32_t BIT12:1;
    uint32_t BIT13:1;
    uint32_t BIT14:1;
    uint32_t BIT15:1;
}GPIO_S;

typedef struct{
	uint32_t GPIO0:4;
	uint32_t GPIO1:4;
	uint32_t GPIO2:4;
	uint32_t GPIO3:4;
	uint32_t GPIO4:4;
	uint32_t GPIO5:4;
	uint32_t GPIO6:4;
	uint32_t GPIO7:4;
}GPIO_CONFIG_S;

#endif /* SRC_STRUCT_DEFINE_H_ */

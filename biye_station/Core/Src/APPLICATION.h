/*
 * APPLICATION.h
 *
 *  Created on: 2019年11月27日
 *      Author: cal
 */

#ifndef SRC_APPLICATION_H_
#define SRC_APPLICATION_H_

#include "stm32f1xx_hal.h"

typedef enum state{

    success=200,
    fail,
	exception,
}State;

typedef enum msgType{   //最好小于256, 不然会是int, 在0-255是unsigned char, 在STM32CubeIDE中

   signin = 30,
   signin_back,
   status,
   status_back,
    query,
    query_back,
    map,
    execution,
	ack,

}MsgType;

typedef struct msgStruct{

    uint8_t msgRxAddr[6];
    uint8_t msgContext[32];

}MsgStruct;

typedef enum nodeType{

    moveNode=10,
    stationNode,
    warehouseNode,

}NodeType;

typedef struct node{

    uint8_t id;
    NodeType type;
    uint8_t location;
    uint8_t space;
    uint8_t power;
    uint8_t busy;
    MsgStruct msgStruct;

}Node;



#define THISID 0

#endif /* SRC_APPLICATION_H_ */

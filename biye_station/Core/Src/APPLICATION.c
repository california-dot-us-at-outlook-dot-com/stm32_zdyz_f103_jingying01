/*
 * APPLICATION.c
 *
 *  Created on: 2019年11月27日
 *      Author: cal
 */


#include "APPLICATION.h"
#include "NRF24L01P.h"

Node nodes[5];

//crc校验
State crcGeneration(uint8_t *msgContext, uint8_t msgLen, uint8_t *crcA_ptr, uint8_t *crcB_ptr){

	uint8_t crcA=0;
	uint8_t crcB=0;

	if(msgLen>30){
		return fail;
	}

	for(int i=0;i<msgLen;i++){
		crcA += msgContext[i];
		crcB += crcA;
	}

	(*crcA_ptr)=crcA;
	(*crcB_ptr)=crcB;

	return success;
}

State crcCheck(uint8_t *msgContext, uint8_t msgLen, uint8_t A, uint8_t B){

	uint8_t crcA=0;
	uint8_t crcB=0;

	if(msgLen>30){
		return fail;
	}

	for(int i=0;i<msgLen;i++){
		crcA += msgContext[i];
		crcB += crcA;
	}

	if((crcA!=A) || (crcB!=B)){
		return fail;
	}

	return success;

}



State msgStructGeneration(MsgStruct *msgStruct, MsgType msgType,uint8_t argc, uint8_t *argv, uint8_t *msgRxAddr){

	msgStruct->msgContext[0]=msgType;

	if(msgType==query){

		msgStruct->msgContext[0]=query;
		msgStruct->msgContext[1]=3;
//#if THISTYPE == StationType
//		msgStruct->msgContext[2]=stationNode;
//#endif
//		0 0 0 0 0 0 0 0   1 1 1 1 1 1 1 1   2 2 2 2 2 2 2 2   3 3 3 3 3 3 3 3
//		t l N x x x x x   x x x x x x x x   x x x x x x x x   x x x x x x x x
//		y e o
//		p n d
//		e   e
	}else if(msgType==signin_back){
		msgStruct->msgContext[0]=signin_back;
		msgStruct->msgContext[1]=4;
		msgStruct->msgContext[2]=success;
//		msgStruct->msgContext[3]=getNewId();
		//		0 0 0 0 0 0 0 0  1 1 1 1 1 1 1 1  2 2 2 2 2 2 2 2  3 3 3 3 3 3 3 3
		//		t l x x x x x x  x x x x x x x x  x x x x x x x x  x x x x x x x x
		//		y e
		//		p n
		//		e
	}else if(msgType==status_back){
		msgStruct->msgContext[0]=status_back;
		msgStruct->msgContext[1]=3;
		msgStruct->msgContext[2]=success;
		//		0 0 0 0 0 0 0 0  1 1 1 1 1 1 1 1  2 2 2 2 2 2 2 2  3 3 3 3 3 3 3 3
		//		t l 0 x x x x x  x x x x x x x x  x x x x x x x x  x x x x x x x x
		//		y e
		//		p n
		//		e
	}else if(msgType==query_back){
		msgStruct->msgContext[0]=query_back;
		msgStruct->msgContext[1]=9;
		msgStruct->msgContext[2]=success;
		msgStruct->msgContext[3]=nodes[THISID].id;
		msgStruct->msgContext[4]=nodes[THISID].location;
		msgStruct->msgContext[5]=nodes[THISID].busy;
		msgStruct->msgContext[6]=nodes[THISID].space;
		msgStruct->msgContext[7]=nodes[THISID].type;
		msgStruct->msgContext[8]=nodes[THISID].power;
		//		0 0 0 0 0 0 0 0  1 1 1 1 1 1 1 1  2 2 2 2 2 2 2 2  3 3 3 3 3 3 3 3
		//		t l x x x x x x  x x x x x x x x  x x x x x x x x  x x x x x x x x
		//		y e
		//		p n
		//		e
	}else if(msgType==signin){
		msgStruct->msgContext[0]=signin;
		msgStruct->msgContext[1]=8;
		msgStruct->msgContext[2]=nodes[THISID].id;
		msgStruct->msgContext[3]=nodes[THISID].location;
		msgStruct->msgContext[4]=nodes[THISID].busy;
		msgStruct->msgContext[5]=nodes[THISID].space;
		msgStruct->msgContext[6]=nodes[THISID].type;
		msgStruct->msgContext[7]=nodes[THISID].power;
		//		0 0 0 0 0 0 0 0  1 1 1 1 1 1 1 1  2 2 2 2 2 2 2 2  3 3 3 3 3 3 3 3
		//		t l x x x x x x  x x x x x x x x  x x x x x x x x  x x x x x x x x
		//		y e
		//		p n
		//		e
	}else if(msgType==status){
		msgStruct->msgContext[0]=status;
		msgStruct->msgContext[1]=8;
		msgStruct->msgContext[2]=nodes[THISID].id;
		msgStruct->msgContext[3]=nodes[THISID].location;
		msgStruct->msgContext[4]=nodes[THISID].busy;
		msgStruct->msgContext[5]=nodes[THISID].space;
		msgStruct->msgContext[6]=nodes[THISID].type;
		msgStruct->msgContext[7]=nodes[THISID].power;
		//		0 0 0 0 0 0 0 0  1 1 1 1 1 1 1 1  2 2 2 2 2 2 2 2  3 3 3 3 3 3 3 3
		//		t l x x x x x x  x x x x x x x x  x x x x x x x x  x x x x x x x x
		//		y e
		//		p n
		//		e
	}else if(msgType==map){
		msgStruct->msgContext[0]=signin;
		msgStruct->msgContext[1]=30;
//		msgStruct->msgContext[2]=;
		//		0 0 0 0 0 0 0 0  1 1 1 1 1 1 1 1  2 2 2 2 2 2 2 2  3 3 3 3 3 3 3 3
		//		t l x x x x x x  x x x x x x x x  x x x x x x x x  x x x x x x x x
		//		y e
		//		p n
		//		e
	}else if(msgType==execution){
		msgStruct->msgContext[0]=execution;
		msgStruct->msgContext[1]=2+argc;
		for(int i=0;i<argc;i++){
			msgStruct->msgContext[i+2]=argv[i];
		}
		//		0 0 0 0 0 0 0 0  1 1 1 1 1 1 1 1  2 2 2 2 2 2 2 2  3 3 3 3 3 3 3 3
		//		t l x x x x x x  x x x x x x x x  x x x x x x x x  x x x x x x x x
		//		y e
		//		p n
		//		e
	}else if(msgType==ack){
		msgStruct->msgContext[0]=ack;
		msgStruct->msgContext[1]=2+argc;
		for(int i=0;i<argc;i++){
			msgStruct->msgContext[i+2]=argv[i];
		}
	}


	for(int i=0;i<5;i++){
		msgStruct->msgRxAddr[i]=msgRxAddr[i];
	}

	if(crcGeneration(msgStruct->msgContext, msgStruct->msgContext[1], (msgStruct->msgContext+msgStruct->msgContext[1]), msgStruct->msgContext+msgStruct->msgContext[1]+1)==fail){
		return fail;
	}

	return success;
}

State sendMsg(MsgStruct *msgStruct){

	NRF24L01_TX_Mode(msgStruct->msgRxAddr);

	if(NRF2401_TxPacket(msgStruct->msgContext)!=TX_OK){
		return fail;
	}
	return success;
}

State recvMsg_wq(MsgStruct *msgStruct, uint16_t timeout){

	if(timeout){
		NRF2401_RX_Mode(msgStruct->msgRxAddr);
		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_11);
//		HAL_Delay(timeout);
//		NRF2401_RX_Mode(msgStruct->msgRxAddr);

		extern __IO uint32_t uwTick;

		uint32_t time_tick_1=uwTick;

		while(NRF_RxPacket_timeout(msgStruct->msgContext, timeout)&&((uwTick-time_tick_1)<timeout)){
//			HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_11);
			delay_ms(20);

		}

	}else{
		if(NRF_RxPacket(msgStruct->msgContext)!=0){
			return fail;
		}
	}
	return success;
}


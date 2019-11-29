/*
 * HARDWARE.c
 *
 *  Created on: 2019年11月25日
 *      Author: cal
 */


#include "HARDWARE.h"

uint8_t RAM_disk_status(){
	return 0;
}

uint8_t RAM_disk_initialize(){
	return 0;
}

uint8_t RAM_disk_read(BYTE *buff, LBA_t sector, UINT count){
	return 0;
}

uint8_t RAM_disk_write(BYTE *buff, LBA_t sector, UINT count){
	return 0;
}


uint8_t MMC_disk_status(){
	return 0;
}

uint8_t MMC_disk_initialize(){
	uint8_t res = SD_Init();
	return res;
}

uint8_t MMC_disk_read(BYTE *buff, LBA_t sector, UINT count){
	uint8_t res = SD_ReadDisk(buff, sector, count);
	while(res){
		MMC_disk_initialize();
		res = SD_ReadDisk(buff, sector, count);
	}
	return res;
}

uint8_t MMC_disk_write(BYTE *buff, LBA_t sector, UINT count){
	uint8_t res = SD_WriteDisk(buff, sector, count);
	while(res){
		MMC_disk_initialize();
		res = SD_WriteDisk(buff, sector, count);
	}
	return res;
}


uint8_t USB_disk_status(){
	return 0;
}

uint8_t USB_disk_initialize(){
	return 0;
}

uint8_t USB_disk_read(BYTE *buff, LBA_t sector, UINT count){
	return 0;
}

uint8_t USB_disk_write(BYTE *buff, LBA_t sector, UINT count){
	return 0;
}

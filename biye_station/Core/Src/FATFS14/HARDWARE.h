/*
 * HARDWARE.h
 *
 *  Created on: 2019年11月25日
 *      Author: cal
 */

#ifndef SRC_FATFS14_HARDWARE_H_
#define SRC_FATFS14_HARDWARE_H_

#include "stm32f1xx_hal.h"
#include "ff.h"
#include "diskio.h"
#include "../SDIO.h"

uint8_t MMC_disk_status();
uint8_t MMC_disk_initialize();
uint8_t MMC_disk_read(BYTE *buff, LBA_t sector, UINT count);
uint8_t MMC_disk_write(BYTE *buff, LBA_t sector, UINT count);

#endif /* SRC_FATFS14_HARDWARE_H_ */

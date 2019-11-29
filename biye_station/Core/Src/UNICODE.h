/*
 * UNICODE.h
 *
 *  Created on: 2019年11月26日
 *      Author: cal
 */

#ifndef SRC_UNICODE_H_
#define SRC_UNICODE_H_

#include "stm32f1xx_hal.h"

uint32_t UTF8_2_UNICODE(uint8_t *str, uint8_t *size);

#endif /* SRC_UNICODE_H_ */

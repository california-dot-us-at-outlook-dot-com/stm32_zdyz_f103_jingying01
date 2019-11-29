/*
 * integer.h
 *
 *  Created on: 2019年11月24日
 *      Author: cal
 */

#ifndef SRC_FATFS_ZDYZ_INTEGER_H_
#define SRC_FATFS_ZDYZ_INTEGER_H_

#include "stm32f1xx_hal.h"


/* This type MUST be 8 bit */
typedef unsigned char	BYTE;

/* These types MUST be 16 bit */
typedef short			SHORT;
typedef unsigned short	WORD;
typedef unsigned short	WCHAR;

/* These types MUST be 16 bit or 32 bit */
typedef int				INT;
typedef unsigned int	UINT;

/* These types MUST be 32 bit */
typedef long			LONG;
typedef unsigned long	DWORD;


#endif /* SRC_FATFS_ZDYZ_INTEGER_H_ */

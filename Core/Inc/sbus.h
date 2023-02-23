/*
 * sbus.h
 *
 *  Created on: 26 Nov 2022
 *      Author: will
 */

#ifndef INC_SBUS_H_
#define INC_SBUS_H_

#define sbuslen 25
#define SBUS_START_BIT 0x0f
#define CH17_MSK 0x01
#define CH18_MSK 0x02
#define LOST_FRAME_MSK 0x04
#define FAILSAFE_MSK 0x08

#include "stm32f4xx.h"
#include <stdint.h>
#include <stdbool.h>
//#include "string.h"
//#include "stdio.h"



typedef struct {
	uint8_t RxBuf[sbuslen];
	uint16_t CH[16+1];
	bool dropped_frame;
	bool fail_safe;
	bool ch17;
	bool ch18;
} SBUS;

void SBUS_Init(SBUS *s, UART_HandleTypeDef *huart);
void SBUS_readDMA(SBUS *s, UART_HandleTypeDef *huart);
void SBUS_Parse(SBUS *s);


#endif /* INC_SBUS_H_ */

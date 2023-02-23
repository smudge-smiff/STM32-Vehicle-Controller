#include "sbus.h"


void SBUS_Init(SBUS *s, UART_HandleTypeDef *huart){
	__HAL_UART_ENABLE_IT(huart, UART_IT_IDLE);
	HAL_UART_Receive_DMA(huart, s->RxBuf, sbuslen);
	memset(&s->CH[16+1], 0, sizeof(s->CH));
}

void SBUS_readDMA(SBUS *s,UART_HandleTypeDef *huart){
	/*
	 * We start by clearing the idle line flag
	 * We then immediatly read the DMA buffer and assign the contents to the sbus RX buffer
	 */
	__HAL_UART_CLEAR_IDLEFLAG(huart);
	HAL_UART_Receive_DMA(huart, s->RxBuf, sbuslen);
}

void SBUS_Parse(SBUS *s)
{
	if(s->RxBuf[0]==SBUS_START_BIT){


		s->CH[1] = ((int16_t)s->RxBuf[ 1] >> 0 | ((int16_t)s->RxBuf[ 2] << 8 )) & 0x07FF;
		s->CH[2] = ((int16_t)s->RxBuf[ 2] >> 3 | ((int16_t)s->RxBuf[ 3] << 5 )) & 0x07FF;
		s->CH[3] = ((int16_t)s->RxBuf[ 3] >> 6 | ((int16_t)s->RxBuf[ 4] << 2 ) | (int16_t)s->RxBuf[ 5] << 10 ) & 0x07FF;
		s->CH[4] = ((int16_t)s->RxBuf[ 5] >> 1 | ((int16_t)s->RxBuf[ 6] << 7 )) & 0x07FF;
		s->CH[5] = ((int16_t)s->RxBuf[ 6] >> 4 | ((int16_t)s->RxBuf[ 7] << 4 )) & 0x07FF;
		s->CH[6] = ((int16_t)s->RxBuf[ 7] >> 7 | ((int16_t)s->RxBuf[ 8] << 1 ) | (int16_t)s->RxBuf[9] << 9 ) & 0x07FF;
		s->CH[7] = ((int16_t)s->RxBuf[ 9] >> 2 | ((int16_t)s->RxBuf[10] << 6 )) & 0x07FF;
		s->CH[8] = ((int16_t)s->RxBuf[10] >> 5 | ((int16_t)s->RxBuf[11] << 3 )) & 0x07FF;
		s->CH[9] = ((int16_t)s->RxBuf[12] << 0 | ((int16_t)s->RxBuf[13] << 8 )) & 0x07FF;
		s->CH[10] = ((int16_t)s->RxBuf[13] >> 3 | ((int16_t)s->RxBuf[14] << 5 )) & 0x07FF;
		s->CH[11] = ((int16_t)s->RxBuf[14] >> 6 | ((int16_t)s->RxBuf[15] << 2 ) | (int16_t)s->RxBuf[16] << 10 ) & 0x07FF;
		s->CH[12] = ((int16_t)s->RxBuf[16] >> 1 | ((int16_t)s->RxBuf[17] << 7 )) & 0x07FF;
		s->CH[13] = ((int16_t)s->RxBuf[17] >> 4 | ((int16_t)s->RxBuf[18] << 4 )) & 0x07FF;
		s->CH[14] = ((int16_t)s->RxBuf[18] >> 7 | ((int16_t)s->RxBuf[19] << 1 ) | (int16_t)s->RxBuf[20] << 9 ) & 0x07FF;
		s->CH[15] = ((int16_t)s->RxBuf[20] >> 2 | ((int16_t)s->RxBuf[21] << 6 )) & 0x07FF;
		s->CH[16] = ((int16_t)s->RxBuf[21] >> 5 | ((int16_t)s->RxBuf[22] << 3 )) & 0x07FF;

		//uint8_t txbuf[64] = {0};
		//sprintf(txbuf, "CH1: %hd \n\r", s->CH[1]);
		//CDC_Transmit_FS(txbuf, strlen(txbuf));
		/*uint16_t ch1 = ((int16_t)s->RxBuf[ 1] >> 0 | ((int16_t)s->RxBuf[ 2] << 8 )) & 0x07FF;
		uint8_t txbuf[64] = {0};
		sprintf(txbuf, "CH1: %hd \n\r", ch1);
		CDC_Transmit_FS(txbuf, strlen(txbuf));*/
	} else {
		uint8_t txbuf[64] = {0};
		sprintf(txbuf, "Error");
		//CDC_Transmit_FS(txbuf, strlen(txbuf));
	}
}


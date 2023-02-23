/*
 * mpu6050.c
 *
 *  Created on: Dec 12, 2022
 *      Author: will
 */
#include "mpu6050.h"
HAL_StatusTypeDef MPU6050_Init(MPU6050 *dev, I2C_HandleTypeDef *i2cHandle, uint8_t Address){
	dev->i2cHandle = i2cHandle;
	dev->ADDR = (Address << 1);
	// Enable MPU6050
	MPU6050_WriteRegister(dev, 0x6B, (uint8_t *)0x00);
	MPU6050_WriteRegister(dev, 0x1C, (uint8_t *)0x08);
	MPU6050_WriteRegister(dev, 0x1B, (uint8_t *)0x08);
}
HAL_StatusTypeDef MPU6050_ReadTemp(MPU6050 *dev){
	int16_t data;
	uint8_t data_h = 0;
	uint8_t data_l = 0;
	uint8_t res = MPU6050_ReadRegister(dev, 0x41, &data_h);
	MPU6050_ReadRegister(dev, 0x42, &data_l);
	data = (data_h << 8) | data_l;
	dev->temp_C = 36.53+(data)/340.0;
	uint8_t txbuf[64] = {0};
	sprintf(txbuf, "TEMP: %f \n\r", dev->temp_C);
	HAL_UART_Transmit(txbuf, strlen(txbuf));
}


/*
 * I2C Handlers
 */

HAL_StatusTypeDef MPU6050_ReadRegister( MPU6050 *dev, uint8_t reg, uint8_t *data ) {

	return HAL_I2C_Mem_Read( dev->i2cHandle, dev->ADDR, reg, I2C_MEMADD_SIZE_8BIT, data, 1, HAL_MAX_DELAY );

}

HAL_StatusTypeDef MPU6050_ReadRegisters( MPU6050 *dev, uint8_t reg, uint8_t *data, uint8_t length ) {

	return HAL_I2C_Mem_Read( dev->i2cHandle, dev->ADDR, reg, I2C_MEMADD_SIZE_8BIT, data, length, HAL_MAX_DELAY );

}

HAL_StatusTypeDef MPU6050_WriteRegister( MPU6050 *dev, uint8_t reg, uint8_t *data ) {

	return HAL_I2C_Mem_Write( dev->i2cHandle, dev->ADDR, reg, I2C_MEMADD_SIZE_8BIT, data, 1, HAL_MAX_DELAY );

}

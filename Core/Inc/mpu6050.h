/*
 * mpu6050.h
 *
 *  Created on: Dec 12, 2022
 *      Author: will
 */

#ifndef INC_MPU6050_H_
#define INC_MPU6050_H_


#include "stm32f4xx.h"


//#define MPU6050_I2C_ADDR (0x68 << 1)

typedef struct {
	I2C_HandleTypeDef *i2cHandle; // What I2C bus is the sensor on

	/* Address of the Chip */
	uint8_t ADDR;

	/* Readings */
	float temp_C;
} MPU6050;

HAL_StatusTypeDef MPU6050_Init(MPU6050 *dev, I2C_HandleTypeDef *i2cHandle, uint8_t Address);
HAL_StatusTypeDef MPU6050_ReadTemp(MPU6050 *dev);
/*
 * LOW-LEVEL FUNCTIONS
 */
HAL_StatusTypeDef MPU6050_ReadRegister(  MPU6050 *dev, uint8_t reg, uint8_t *data );
HAL_StatusTypeDef MPU6050_ReadRegisters( MPU6050 *dev, uint8_t reg, uint8_t *data, uint8_t length );

HAL_StatusTypeDef MPU6050_WriteRegister( MPU6050 *dev, uint8_t reg, uint8_t *data );



#endif /* INC_MPU6050_H_ */

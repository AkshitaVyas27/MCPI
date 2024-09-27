/*
 * accel.h
 *
 *  Created on: Sep 26, 2024
 *      Author: asus
 */

#ifndef ACCEL_H_
#define ACCEL_H_

#include "stm32f4xx.h"
#include "spi.h"
#define LIS_C4_ADDR 0x20
#define LIS_STATUS_ADDR 0x27
#define LIS_XL_ADDR  0x28
#define LIS_XH_ADDR  0x29
#define LIS_YL_ADDR  0x2A
#define LIS_YH_ADDR  0x2B
#define LIS_ZL_ADDR  0x2C
#define LIS_ZH_ADDR  0x2D


#define LIS_C4_XEN BV(0)
#define LIS_C4_YEN BV(1)
#define LIS_C4_ZEN BV(2)

#define LIS_C4_RATE_25 BV(6)

#define LIS_SR_XDA  BV(0)
#define LIS_SR_YDA_  BV(1)
#define LIS_SR_ZDA  BV(2)
#define LIS_SR_XYZDA  BV(3)

void SPI_DataWriteIO(uint8_t regr,uint8_t data[], uint8_t size);
void SPI_DataReadIO(uint8_t regr,uint8_t data[], uint8_t size);


typedef struct values{
	int16_t x;
	int16_t y;
	int16_t z;
}LIS_Data;

void LIS_InIt(void);
int LIS_IsDataAvail(void);
LIS_Data LIS_GetData(void);

#endif /* ACCEL_H_ */

/*
 * accel.c
 *
 *  Created on: Sep 26, 2024
 *      Author: asus
 */
#include "accel.h"

void SPI_DataWriteIO(uint8_t regr,uint8_t data[], uint8_t size){
	SPI_CS_Enable();
	regr &= ~BV(7);
	SPI_Transmit(regr);
	for(int i=0;i<size;i++){
		SPI_Transmit(data[i]);
	}
	SPI_CS_Disable();
}


void SPI_DataReadIO(uint8_t regr,uint8_t data[], uint8_t size){
	SPI_CS_Enable();
		regr |= BV(7);
		SPI_Transmit(regr);
		for(int i=0;i<size;i++){
			data[i]=SPI_Receive();
		}
		SPI_CS_Disable();
}

void LIS_InIt(void){
	SPI_InIt();
	DelayMs(3);
	uint8_t config= (LIS_C4_RATE_25|LIS_C4_XEN|LIS_C4_YEN|LIS_C4_ZEN);
	SPI_DataWriteIO(LIS_C4_ADDR, &config, 1);

}

int LIS_IsDataAvail(void){
	uint8_t ready;
	do{
		SPI_DataReadIO(LIS_STATUS_ADDR, &ready, 1);
	}while(!(ready & LIS_SR_XYZDA));
	return 1;
}

LIS_Data LIS_GetData(void){
	uint8_t data[2];
	LIS_Data val;
	SPI_DataReadIO(LIS_XL_ADDR, data,2);
	val.x=((uint16_t)data[1]<<8)|data[0];
	SPI_DataReadIO(LIS_YL_ADDR, data,2);
	val.y=((uint16_t)data[1]<<8)|data[0];
	SPI_DataReadIO(LIS_ZL_ADDR,data,2);
	val.z=((uint16_t)data[1]<<8)|data[0];
	return val;

}



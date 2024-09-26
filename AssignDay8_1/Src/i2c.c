/*
 * i2c.c
 *
 *  Created on: Sep 24, 2024
 *      Author: asus
 */
#include"i2c.h"
void I2CInIt(void){
	//GPIO
	RCC->AHB1ENR|=RCC_AHB1ENR_GPIOBEN;
	GPIOB->MODER |= (BV(SCL_PIN*2+1) | BV(SDA_PIN*2+1));
		GPIOB->MODER &= ~(BV(SCL_PIN*2) | BV(SDA_PIN*2));
	    GPIOB->PUPDR &= ~(BV(SCL_PIN*2+1) | BV(SDA_PIN*2+1) | BV(SCL_PIN*2) | BV(SDA_PIN*2));
	    GPIOB->AFR[0] |= BV(30) | BV(26);
	       GPIOB->AFR[0] &= ~(BV(31) | BV(29) | BV(28) | BV(27) | BV(25) | BV(24));

	RCC->APB1ENR|=RCC_APB1ENR_I2C1EN;
	I2C1->CR1 =I2C_CR1_SWRST;
	I2C1->CR1=0;
	I2C1->CR2|=16;
	I2C1->CCR &= ~I2C_CCR_FS;
	I2C1->CCR |=80;
	I2C1->TRISE |=17;


	I2C1->CR1|= I2C_CR1_ACK;
	I2C1-> CR1 |= I2C_CR1_PE;
}



void I2C_Start(void){
	I2C1->CR1|=I2C_CR1_START;
	while(!(I2C1->SR1 & I2C_SR1_SB));

}
void I2C_RepeatStart(void){
	I2C_Start();

}
void I2C_Stop(void){
	I2C1->CR1 |= I2C_CR1_STOP;
	while(!(I2C1->SR2& I2C_SR2_BUSY));
}
void I2C_SendSlavAdd(uint8_t slaveadrr){
	I2C1->DR=slaveadrr;
	while(!(I2C1->SR1 & I2C_SR1_ADDR));
	(void)I2C1->SR1;
	  (void)I2C1->SR2;
}
void I2C_Data(uint8_t data){
	while(!(I2C1->SR1|=I2C_SR1_TXE));
	I2C1->DR=data;
	while(!(I2C1->SR1 & I2C_SR1_BTF));


}
uint16_t I2C_DataRecv(void){
	I2C1->CR1 |= I2C_CR1_ACK|I2C_CR1_POS;
	while(!(I2C1->SR1 & I2C_SR1_RXNE));
		uint16_t val=I2C1->DR;
		return val;

}
uint16_t I2C_DataRecvNack(void){
	I2C1->CR1 &= ~(I2C_CR1_ACK | I2C_CR1_POS);
		while(!(I2C1->SR1 & I2C_SR1_RXNE));
			uint16_t val=I2C1->DR;
			return val;
}
int I2CIsdeviceReady(uint8_t slaveadrr){
	I2C1->DR=slaveadrr;
	while(!(I2C1->SR1 & I2C_SR1_ADDR));
		(void)I2C1->SR1;
		(void)I2C1->SR2;
		return 1;
}



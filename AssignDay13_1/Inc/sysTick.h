/*
 * sysTick.h
 *
 *  Created on: Oct 2, 2024
 *      Author: asus
 */

#ifndef SYSTICK_H_
#define SYSTICK_H_
#include"stm32f4xx.h"

void SysTick_InIt(void);
void SysTick_Delay(uint32_t ms);
void SysTick_Handler(void);
extern volatile uint32_t jiffies;

#endif /* SYSTICK_H_ */

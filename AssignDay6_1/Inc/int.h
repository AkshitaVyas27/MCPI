/*
 * int.h
 *
 *  Created on: Sep 22, 2024
 *      Author: asus
 */

#ifndef INT_H_
#define INT_H_
#include "stm32f4xx.h"
#define SWITCH_GPIO GPIOA
#define SWITCH_PIN 0
#define SWITCH_CLOKEN 0
#define SWITCH_EXTI 0

void SwitchInIt(void);
void EXTI0_IRQHandler(void);
extern volatile uint32_t SwitchExtiFlag;
extern int count;


#endif /* INT_H_ */

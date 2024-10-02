/*
 * intr.c
 *
 *  Created on: Sep 22, 2024
 *      Author: asus
 */

#include"int.h"


void SwitchInIt(void){
	RCC->AHB1ENR|=BV(SWITCH_CLOKEN);
	SWITCH_GPIO->MODER&= ~(BV(SWITCH_PIN*2+1)|BV(SWITCH_PIN*2));
	SWITCH_GPIO->OTYPER&= ~BV(SWITCH_PIN);
	SWITCH_GPIO->PUPDR &= ~(BV(SWITCH_PIN*2+1) | BV(SWITCH_PIN*2));
	EXTI->FTSR |= BV(SWITCH_EXTI);
	EXTI->IMR |= BV(SWITCH_EXTI);
	SYSCFG->EXTICR[0]&= ~(BV(3)|BV(2)|BV(1)|BV(0));
	NVIC_EnableIRQ(EXTI0_IRQn);
}
uint32_t SwitchExtiFlag = 0;


void EXTI0_IRQHandler(void){
	EXTI->PR |= BV(SWITCH_EXTI);
	SwitchExtiFlag=1;
}

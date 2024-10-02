/*
 * sysTick.c
 *
 *  Created on: Oct 2, 2024
 *      Author: asus
 */
#include"sysTick.h"
volatile uint32_t jiffies=0;
void SysTick_InIt(void){
	SysTick_Config(SystemCoreClock/1000);
}

void SysTick_Handler(void){
	jiffies++;

}

void SysTick_Delay(uint32_t ms){
	uint32_t until=jiffies+ms;
	while(jiffies<until)
		;

}

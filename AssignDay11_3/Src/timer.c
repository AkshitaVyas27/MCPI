/*
 * timer.c
 *
 *  Created on: Sep 30, 2024
 *      Author: asus
 */
#include "timer.h"


void Timer_InIt(uint32_t ms){
	//Initialize Timer
	RCC->APB1ENR|= RCC_APB1ENR_TIM7EN;
	//Set Timer clock
	TIM7->PSC= (PR-1);
	//Calculate number of clocks to count (CNT).
		uint32_t cnt= (TCLK/1000)*ms/PR;
		//Set CNT in ARR.
		TIM7->ARR= (cnt-1);
		TIM7->CNT=0;
		//Enable Timer Interrupt in DIER.
		TIM7->DIER|= TIM_DIER_UIE;
		//Wait for UIF flag (in SR).

		//	Enable Timer Interrupt in NVIC.
				NVIC_EnableIRQ(TIM7_IRQn);
		//Stop Timer in CR1.
				TIM7->CR1|= TIM_CR1_CEN;


}

int count=0;

void TIM7_DAC_IRQHandler(void){
	//Check if UIF flag is set (in SR).
	if(TIM7->SR & TIM_SR_UIF){
		TIM7->SR &= ~TIM_SR_UIF;
		count++;
	}
}

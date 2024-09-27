/*
 * led.h
 *
 *  Created on: Sep 19, 2024
 *      Author: asus
 */

#ifndef LED_H_
#define LED_H_
#include "stm32f4xx.h"

#define GPIO_LED GPIOD
#define GPIO_GREEN 12
#define GPIO_ORANGE 13
#define GPIO_RED 14
#define GPIO_BLUE 15
#define GPIO_LED_CLOCK 3

void LedInIt(uint32_t pin);
void LedOn(uint32_t pin);
void LedOff(uint32_t pin);
void LedBlink(uint32_t pin, uint32_t delay);

#endif /* LED_H_ */

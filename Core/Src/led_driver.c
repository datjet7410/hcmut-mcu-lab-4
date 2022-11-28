/*
 * led_driver.c
 *
 *  Created on: Nov 28, 2022
 *      Author: datjet7410
 */

#include "led_driver.h"

void led1test(){
	HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
}

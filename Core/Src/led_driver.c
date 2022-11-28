/*
 * led_driver.c
 *
 *  Created on: Nov 28, 2022
 *      Author: datjet7410
 */

#include "led_driver.h"

void debug_led_run(){
	HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
}

void aqua_led_run(){
	HAL_GPIO_TogglePin(LED_AQUA_GPIO_Port, LED_AQUA_Pin);
}
void orange_led_run(){
	HAL_GPIO_TogglePin(LED_ORANGE_GPIO_Port, LED_ORANGE_Pin);
}
void pink_led_run(){
	HAL_GPIO_TogglePin(LED_PINK_GPIO_Port, LED_PINK_Pin);
}
void yellow_led_run(){
	HAL_GPIO_TogglePin(LED_YELLOW_GPIO_Port, LED_YELLOW_Pin);
}
void green_led_run(){
	HAL_GPIO_TogglePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin);
}

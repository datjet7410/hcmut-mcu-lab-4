/*
 * scheduler.c
 *
 *  Created on: Nov 28, 2022
 *      Author: datjet7410
 */

#include "scheduler.h"


sTasks SCH_tasks_G[SCH_MAX_TASKS];

/* Last task in SCH_tasks_G */
uint8_t last_task_index = 0;

void SCH_Init(void){
	last_task_index = 0;
}

uint8_t SCH_Add_Task(
		void (*pFunction)(),
		uint32_t DELAY,
		uint32_t PERIOD
		){
	if(last_task_index < SCH_MAX_TASKS){
		SCH_tasks_G[last_task_index].pTask = pFunction;
		SCH_tasks_G[last_task_index].Delay = DELAY / TIMER_CYCLE;
		SCH_tasks_G[last_task_index].Period = PERIOD / TIMER_CYCLE;
		SCH_tasks_G[last_task_index].RunMe = 0;

		return last_task_index++;
	}

	return 1;
}

void SCH_Update_Tasks(void){
	for(int i = 0; i < last_task_index; i++){
		if(SCH_tasks_G[i].Delay > 0){
			SCH_tasks_G[i].Delay--;
		}else{
			SCH_tasks_G[i].Delay = SCH_tasks_G[i].Period;
			SCH_tasks_G[i].RunMe++;
		}
	}
}

void SCH_Dispatch_Tasks(void){
	for(int i = 0; i < last_task_index; i++){
		if(SCH_tasks_G[i].RunMe > 0){
			SCH_tasks_G[i].RunMe--;
			(*SCH_tasks_G[i].pTask)();

			/* For One shot task */
			if(SCH_tasks_G[i].Period == 0 ){
				SCH_Delete_Task(i);
			}
		}
	}
}

uint8_t SCH_Delete_Task(uint8_t task_index){
	/* Shift array */
	for(int i = task_index + 1; i < last_task_index; i++){
		SCH_tasks_G[i - 1] = SCH_tasks_G[i];
	}

	SCH_tasks_G[last_task_index].pTask = 0x0000;
	SCH_tasks_G[last_task_index].Delay = 0;
	SCH_tasks_G[last_task_index].Period = 0;
	SCH_tasks_G[last_task_index].RunMe = 0;

	last_task_index--;

	return 0;
}

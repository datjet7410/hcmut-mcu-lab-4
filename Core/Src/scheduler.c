/*
 * scheduler.c
 *
 *  Created on: Nov 28, 2022
 *      Author: datjet7410
 */

#include "scheduler.h"


sTasks SCH_tasks_G[SCH_MAX_TASKS];

/* Real size of tasks' queue */
uint8_t tasks_queue_size = 0;

void SCH_Init(void){
	tasks_queue_size = 0;
}

uint8_t SCH_Add_Task(
		void (*pFunction)(),
		uint32_t DELAY,
		uint32_t PERIOD
		){
	if(tasks_queue_size < SCH_MAX_TASKS){
		SCH_tasks_G[tasks_queue_size].pTask = pFunction;
		SCH_tasks_G[tasks_queue_size].Delay = DELAY / TIMER_CYCLE;
		SCH_tasks_G[tasks_queue_size].Period = PERIOD / TIMER_CYCLE;
		SCH_tasks_G[tasks_queue_size].RunMe = 0;

		return tasks_queue_size++;
	}

	return 1;
}

void SCH_Update_Tasks(void){
	for(int i = 0; i < tasks_queue_size; i++){
		if(SCH_tasks_G[i].Delay > 0){
			SCH_tasks_G[i].Delay--;
		}else{
			/* Period - 1 -> 0 count Period times */
			SCH_tasks_G[i].Delay = SCH_tasks_G[i].Period - 1;
			SCH_tasks_G[i].RunMe++;
		}
	}
}

void SCH_Dispatch_Tasks(void){
	for(int i = 0; i < tasks_queue_size; i++){
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
	for(int i = task_index + 1; i < tasks_queue_size; i++){
		SCH_tasks_G[i - 1] = SCH_tasks_G[i];
	}

	tasks_queue_size--;

	return 0;
}

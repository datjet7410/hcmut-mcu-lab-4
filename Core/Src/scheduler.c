/*
 * scheduler.c
 *
 *  Created on: Nov 28, 2022
 *      Author: datjet7410
 */

#include "scheduler.h"


sTasks SCH_tasks_G[SCH_MAX_TASKS];
uint8_t current_task_index = 0;

void SCH_Init(void){
	current_task_index = 0;
}

uint8_t SCH_Add_Task(
		void (*pFunction)(),
		uint32_t DELAY,
		uint32_t PERIOD
		){
	if(current_task_index < SCH_MAX_TASKS){
		SCH_tasks_G[current_task_index].pTask = pFunction;
		SCH_tasks_G[current_task_index].Delay = DELAY;
		SCH_tasks_G[current_task_index].Period = PERIOD;
		SCH_tasks_G[current_task_index].RunMe = 0;

		return current_task_index++;
	}

	return current_task_index;
}

void SCH_Update_Tasks(void){
	for(int i = 0; i < current_task_index; i++){
		if(SCH_tasks_G[i].Delay > 0){
			SCH_tasks_G[i].Delay--;
		}else{
			SCH_tasks_G[i].Delay = SCH_tasks_G[i].Period;
			SCH_tasks_G[i].RunMe++;
		}
	}
}

void SCH_Dispatch_Tasks(void){
	for(int i = 0; i < current_task_index; i++){
		if(SCH_tasks_G[i].RunMe > 0){
			SCH_tasks_G[i].RunMe--;
			(*SCH_tasks_G[i].pTask)();

			if(SCH_tasks_G[i].Period == 0 ){
				SCH_Delete_Task(i);
			}
		}
	}
}


uint8_t SCH_Delete_Task(uint8_t task_index){
	return 0;
}

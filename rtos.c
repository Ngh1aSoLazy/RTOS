/*
 * rtos.c
 *
 *  Created on: Mar 29, 2026
 *      Author: MinhNghia_hehe
 */

#include "rtos.h"
#include "stm32f1xx.h"

Task tasks[MAX_TASKS]; // Danh sách các task
int current_task = 0; // index task đang run
int task_count = 0; // Số task đã được tạo

// Tạo task
void rtos_create_task(void (*task_func)(void)) // "void (*task_func)(void)" truyền vào 1 hàm task_n(void) và ko trả về giá trị ->void task)n(void)
{
	Task *t = &tasks[task_count]; // Pointer trỏ tới phần tử chứa task thứ n

	uint32_t *sp = &(t -> stack[STACK_SIZE - 16]);

	sp[15] = (uint32_t)task_func; // PC
	sp[14] = 0x01000000; // xPSR
	sp[13] = 0xFFFFFFFD; // LR (EXC_RETURN)

	t->sp = sp;

	task_count++;
}

// Scheduler round-robin
void scheduler(void)
{
	current_task = (current_task + 1) % task_count;
}

// Start scheduler
void rtos_start(void)
{
	__set_PSP((uint32_t)tasks[0].sp);
	__set_CONTROL(0x02);
	__ISB();

	__asm volatile
	(
		"POP {R4-R11}\n"
		"POP {R0-R3}\n"
		"POP {R12}\n"
		"POP {LR}\n"
		"POP {PC}\n"
	);

}


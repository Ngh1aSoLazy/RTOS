/*
 * rtos.h
 *
 *  Created on: Mar 29, 2026
 *      Author: MinhNghia_hehe
 */

#ifndef INC_RTOS_H_	// Header guard
#define INC_RTOS_H_ // Header guard

#include <stdint.h>

#define MAX_TASKS 5 // Số task tối đa
#define STACK_SIZE 128 // Số phần tử của 1 task

typedef struct
{
	uint32_t *sp;	// Khởi tạo stack pointer
					// Dùng để trỏ vào vị trí hiện tại của stack
					// nhằm save context và restore context

	uint32_t stack[STACK_SIZE];		// 128 * 4 bytes = 512 bytes / 1 task
									// Lưu biến local, return address, và context CPU
}Task;

// API (Tập hợp các hàm RTOS cung cấp để dev giao tiếp với kernel, chứ thực tế dev ko trực tiếp điều khiển kernel)
void rtos_init(void);
void rtos_create_task(void (*task_func)(void));	// Hàm tạo task
void rtos_start(void); // Hàm khởi động scheduler

#endif /* INC_RTOS_H_ */

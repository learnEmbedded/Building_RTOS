#ifndef OS_KERNEL_H
#define OS_KERNEL_H

#include <stdint.h>  

#define NUM_OF_THREADS 3
#define STACK_SIZE 100


typedef struct tcbType {
    uint32_t *stackPt;        
    struct tcbType *nextPt;   
} tcbType;

extern tcbType tcbs[NUM_OF_THREADS];
extern tcbType *currentPt;
extern uint32_t TCB_STACK[NUM_OF_THREADS][STACK_SIZE];

void osKernelLaunch(uint32_t quanta);
void osKernelStackInit(int i);
uint8_t osKernelAddThread(void (*task0)(void), void (*task1)(void), void (*task2)(void));
void osKernelInit(void);
#endif

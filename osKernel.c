#include "osKernel.h"
#include "stm32f10x.h"

tcbType tcbs[NUM_OF_THREADS];
tcbType *currentPt;
uint32_t TCB_STACK[NUM_OF_THREADS][STACK_SIZE];

void osKernelStackInit(int i) {
    tcbs[i].stackPt = &TCB_STACK[i][STACK_SIZE-16]; // StackPointer
    /* Set bit 21 (T-Bit) in PSR to 1 to operate it in Thumb Mode */
    TCB_STACK[i][STACK_SIZE-1] = 1 << 24; /* PSR */
    /* Dummy stack content */
    TCB_STACK[i][STACK_SIZE-3] = 0xAAAAAAAA; /* R14 (LR) */
    TCB_STACK[i][STACK_SIZE-4] = 0xAAAAAAAA; /* R12 */
    TCB_STACK[i][STACK_SIZE-5] = 0xAAAAAAAA; /* R3 */
    TCB_STACK[i][STACK_SIZE-6] = 0xAAAAAAAA; /* R2 */
    TCB_STACK[i][STACK_SIZE-7] = 0xAAAAAAAA; /* R1 */
    TCB_STACK[i][STACK_SIZE-8] = 0xAAAAAAAA; /* R0 */
    TCB_STACK[i][STACK_SIZE-9] = 0xAAAAAAAA; /* R11 */
    TCB_STACK[i][STACK_SIZE-10] = 0xAAAAAAAA; /* R10 */
    TCB_STACK[i][STACK_SIZE-11] = 0xAAAAAAAA; /* R9 */
    TCB_STACK[i][STACK_SIZE-12] = 0xAAAAAAAA; /* R8 */
    TCB_STACK[i][STACK_SIZE-13] = 0xAAAAAAAA; /* R7 */
    TCB_STACK[i][STACK_SIZE-14] = 0xAAAAAAAA; /* R6 */
    TCB_STACK[i][STACK_SIZE-15] = 0xAAAAAAAA; /* R5 */
    TCB_STACK[i][STACK_SIZE-16] = 0xAAAAAAAA; /* R4 */
}

uint8_t osKernelAddThread(void (*task0)(void), void (*task1)(void), void (*task2)(void)) {
    /* Disable global interrupts */
    __disable_irq();
    tcbs[0].nextPt = &tcbs[1];
    tcbs[1].nextPt = &tcbs[2];
    tcbs[2].nextPt = &tcbs[0];

    osKernelStackInit(0);
    TCB_STACK[0][STACK_SIZE-2] = (uint32_t)(task0);

    osKernelStackInit(1);
    TCB_STACK[1][STACK_SIZE-2] = (uint32_t)(task1);

    osKernelStackInit(2);
    TCB_STACK[2][STACK_SIZE-2] = (uint32_t)(task2);

    currentPt = &tcbs[0];

    /* Enable global interrupts */
    __enable_irq();

    return 1;
}

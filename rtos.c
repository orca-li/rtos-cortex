#include <CMWrap.h>
#include <stdio.h>
#include <include/threads.h>
#include <include/kernel.h>

#define STACK_SIZE_GreenBlink (64)
void vThreadGreenBlink(void);
uint32_t aThreadGreenBlinkStack[STACK_SIZE_GreenBlink];
tcb tcbGreenBlink = {
    .sp = &aThreadGreenBlinkStack[STACK_SIZE_GreenBlink]
};

#define STACK_SIZE_RedBlink (64)
void vThreadRedBlink(void);
uint32_t aThreadRedBlinkStack[STACK_SIZE_RedBlink];
tcb tcbRedBlink = {
    .sp = &aThreadRedBlinkStack[STACK_SIZE_RedBlink]
};

void rtos_init(void)
{
    xThreadCreate(&tcbRedBlink, vThreadRedBlink, aThreadRedBlinkStack, sizeof(aThreadRedBlinkStack));
    xThreadCreate(&tcbGreenBlink, vThreadGreenBlink, aThreadGreenBlinkStack, sizeof(aThreadGreenBlinkStack));

    // stack_dump();
}

void vThreadGreenBlink(void)
{
    // printf("vThreadGreenBlink is running\r\n");

    while(1)
    {
        GPIOA->ODR ^= GPIO_ODR_OD0_Msk;
        delay_ms(1000);
    }
}

void vThreadRedBlink(void)
{
    // printf("vThreadRedBlink is running\r\n");

    while(1)
    {
        GPIOA->ODR ^= GPIO_ODR_OD1_Msk;
        delay_ms(1000);
    }
}
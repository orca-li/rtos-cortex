#if !defined(__RTOS_THREAD_H__)
#define __RTOS_THREAD_H__

/* Thread Constrol Block */
typedef struct RTOS_TCB {
    void *sp; /* stack pointer */
} tcb;

typedef void (*thread)(void);

void stack_dump(void);
void xThreadCreate(tcb *me, thread handle, void *stack, uint32_t stack_size);

#endif /* __RTOS_THREAD_H__ */
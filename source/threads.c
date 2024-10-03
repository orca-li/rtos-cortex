#include <include/threads.h>

#define align 8
#define STACK_BEGIN_INDEX 1U
#define NULL (void *)0x00000000;

void xThreadCreate(tcb *me, thread handle, void *stack, uint32_t stack_size)
{
    uint32_t *sp = (uint32_t *)((((uint32_t)stack + stack_size) / align) * align);
    uint32_t *stack_limit = NULL;

    *(--sp) = (1 << 24); /* xPSR */
    *(--sp) = (uint32_t)handle; /* PC */
    *(--sp) = 0x0000000Eu; /* LR */
    *(--sp) = 0x0000000Cu; /* R12 */
    *(--sp) = 0x00000003u; /* R3 */
    *(--sp) = 0x00000002u; /* R2 */
    *(--sp) = 0x00000001u; /* R1 */
    *(--sp) = 0x00000000u; /* R0 */
    /* additionaly, fake registers R4-R11 */
    *(--sp) = 0x0000000Bu; /* R11 */
    *(--sp) = 0x0000000Au; /* R10 */
    *(--sp) = 0x00000009u; /* R9 */
    *(--sp) = 0x00000008u; /* R8 */
    *(--sp) = 0x00000007u; /* R7 */
    *(--sp) = 0x00000006u; /* R6 */
    *(--sp) = 0x00000005u; /* R5 */
    *(--sp) = 0x00000004u; /* R4 */

    /* save the top of the stack in the thread's attribute */
    me->sp = sp;

    /* round up the bottom of the stack to the 8-byte boundary */
    stack_limit = (uint32_t*)(((((uint32_t)stack - STACK_BEGIN_INDEX) / align) + STACK_BEGIN_INDEX) * align);

    /* pre-fill the unused part of the stack with 0x00C0FFEE */
    for (sp = sp - 1u; sp > stack_limit; --sp)
    {
        *sp = 0x00C0FFEE;
    }
}
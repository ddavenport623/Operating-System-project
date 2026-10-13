#include <stdint.h>

int const _STACK_SIZE = 10;

struct Stack
{
    struct Stack *next;
    uint64_t stack [_STACK_SIZE];
};

struct PCB {
    uint64_t * sp; // Stack pointer
    int pid; // process ID
    void(*fun)(); // pointer to process' function
    Stack *procStack; // pointer to process' stack
    PCB_t *pcb; // pointer to PCB_t
};
typedef struct PCB PCB_t;
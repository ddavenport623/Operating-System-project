#include <stdint.h>
#include <stdalign.h>
#include "kernel.h"
#include "init.h"

struct Stack
{
    struct Stack *next;
    alignas(16) uint64_t stack [_STACK_SIZE];
};

typedef struct Stack Stack_t;
Stack_t Stacks[_MAX_PROCESSES];

Stack_t * Stack_free_list;

uint64_t* Stack_alloc();
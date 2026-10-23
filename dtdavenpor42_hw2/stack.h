#pragma once

#include <stdint.h>
#include <stdalign.h>

#define _STACK_SIZE 1024

typedef struct Stack Stack_t;

struct Stack
{
    Stack_t *next;
    alignas(16) uint64_t stack [_STACK_SIZE];
};

uint64_t* Stack_alloc();
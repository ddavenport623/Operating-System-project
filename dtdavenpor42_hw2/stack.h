#pragma once

#include <stdint.h>
#include <stdalign.h>

#define _STACK_SIZE 1024

struct Stack
{
    struct Stack *next;
    alignas(16) uint64_t stack [_STACK_SIZE];
};

typedef struct Stack Stack_t;

uint64_t* Stack_alloc();
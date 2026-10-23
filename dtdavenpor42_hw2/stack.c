#include "stack.h"
#include "kernel.h"

uint64_t* Stack_alloc(){
    if (Stack_free_list == 0){
        return 0;
    }
    Stack_t *val = Stack_free_list;
    Stack_free_list = Stack_free_list->next;
    return (uint64_t *)val;
}
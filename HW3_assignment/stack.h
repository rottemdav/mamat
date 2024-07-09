#include <stdbool.h>
#ifndef STACK_H
#define STACK_H

typedef enum STACK_STATUS_T{
    STACK_SUCCESS, /* Assigned to 0 by default */
    STACK_FAILURE, /* Assigned to 1 by default */
} STACK_STATUS;

/* Pointer to an element of the stack */ 
typedef void* elem_t; 

/* Pointers to user function to clone, destroy and print an element in stack */
typedef elem_t (*clone_t)(elem_t e); /* Clones the element */
typedef void (*destroy_t)(elem_t e); /* Deallocate all memory of the element */
typedef void (*print_t)(elem_t e); /* Prints the element */

typedef struct stack stack; /* Opaque pointer to hide implemantation */

/* */
stack* stack_create(int max_stack_size, clone_t clone,
             destroy_t destroy, print_t print);

/* Return if the stack was destroyed successfully */
STACK_STATUS stack_destroy(stack *stack_pointer); 

/* Return if element was pushed successfully to the stack */
STACK_STATUS stack_push(stack *stack_pointer, elem_t* new_element);

/* Pops an element from the top of the stack */
void stack_pop(stack *stack_pointer);

/* Returns a pointer to the element in the top of the stack */
elem_t stack_peek(stack *stack_pointer);

/* Return the stack size, return 1 in case of failiure */
int stack_size(stack *stack_pointer); 

/* Return true if the stack is empty, false otherwise */
bool stack_is_empty(stack *stack_pointer);

/* Returns the number of available slots in the stack */
int stack_capacity(stack *stack_pointer);

/*Prints the stack elements in decsending order - LIFO*/
void stack_print(stack *stack_pointer);

#endif /* STACK_H_ */
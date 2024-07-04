#ifndef STACK_H
#define STACK_H

typedef enum {
    STACK_SUCCESS, /* Assigned to 0 by default */
    STACK_FAILURE, /* Assigned to 1 by default */
} STACK_STATUS;

/* Pointer to an element of the stack */ 
typedef void *elem_t; 

/* Pointers to user function to clone, destroy and print an element in stack */
typedef elem_t (*clone_t)(elem_t e); /* Clones the element */
typedef void (*destroy_t)(elem_t e); /* Deallocate all memory of the element */
typedef void (*print_t)(elem_t e); /* Prints the element */

typedef struct Stack_t* Stack; /* Opaque pointer to hide implemantation */

/* */
Stack* stack_create(int max_stack_size, clone_t clone,
             destroy_t destroy, print_t print);

/* Return if the stack was destroyed successfully */
STACK_STATUS stack_destroy(Stack *pointer_to_stack); 

/* Return if element was pushed successfully to the stack */
STACK_STATUS stack_push(Stack *pointer_to_stack, void* new_element);

/* Pops an element from the top of the stack */
void stack_pop(Stack *pointer_to_stack);

/* Returns a pointer to the element in the top of the stack */
void* stack_peek(Stack *pointer_to_stack);

/* Return the stack size, return 1 in case of failiure */
int stack_size(Stack *pointer_to_stack); 

/*Prints the stack elements in decsending order - LIFO*/
void stack_print(Stack *pointer_to_stack);


#endif /* STACK_H_ */
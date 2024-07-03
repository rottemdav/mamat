#include <stack.h>
#include <stdlib.h>


typedef struct node {
    /* Must use struct node* because Node/node* typedef is only defined outside
       of the defenition */
    struct node* next; 

    elem_t *value;
} Node;

typedef struct Stack_t{
    Node* top;
    int max_size;
    clone_t clone;
    destroy_t destroy_t;
    print_t print;
} Stack;

Stack* stack_create(int max_stack_size, clone_t clone,
                    destroy_t destroy, print_t print){
    
    Node *new_node;
    new_node = (Node *)malloc(sizeof(new_node));
    
    new_node->next = NULL;
    new_node->value = NULL;

    /* Initialize a pointer to the newly created stack */
    Stack *new_stack;
    new_stack = (Stack *)malloc(sizeof(new_stack));

    new_stack->top = new_node;
    new_stack->max_size = max_stack_size;
    new_stack->clone = clone;
    new_stack->destroy_t = destroy;
    new_stack->print = print;
        
    if (!new_stack){
        /*return error*/
    }

    return new_stack;

}

int stack_destroy(stack *stack_pointer) {

}

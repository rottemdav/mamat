#include <stack.h>
#include <stdlib.h>


typedef struct node {
    struct node* prev;
    struct node* next;
    const char *value;
} Node;

struct Stack{
    Node* top;
    int max_size;
    clone_t clone;
    destroy_t destroy_t;
    print_t print;
   // elem_t element; 
};

Stack* stack_create(int max_stack_size, clone_t clone,
                    destroy_t destroy, print_t print){
    
    Node *new_node;
    new_node = (Node *)malloc(sizeof(new_node));
    
    new_node->prev = NULL;
    new_node->next = NULL;
    new_node->value = NULL;

    Stack *new_stack;
    new_stack = (Stack *)malloc(sizeof(new_stack));

    new_stack->top = new_node;
    new_stack->max_size = max_stack_size;
    new_stack->clone = clone;
    new_stack->destroy_t = destroy;
    new_stack->print = print;
        
    if (!new_stack){
        
    }

    return new_stack;

}

int stack_destroy(stack *stack_pointer) {

}

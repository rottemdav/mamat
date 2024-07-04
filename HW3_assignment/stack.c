#include <stack.h>
#include <stdlib.h>

/* --- Defining the ADT needed - stack implementation using linked list --- */

typedef struct node {
    /* Must use struct node* because Node/node* typedef is only defined outside
       of the defenition */
    struct node* next; 

    /* Pointer to the element in a stack node */
    elem_t *value;
} Node;

typedef struct Stack_t{
    Node* top;              /* Store the top node */
    int max_size;           /* Max size of the stack given by user */
    clone_t clone;          /* Clone function of the user */
    destroy_t destroy_t;    /* Mememory dislocation function of the user */
    print_t print;          /* Printing function of the user */
} Stack;


/* -------- Implementation of the functions to handle the stack --------*/

Stack* stack_create(int max_stack_size, clone_t clone,
                    destroy_t destroy, print_t print){
    
    /* Create a new node the will serve as the top of the stack */
    Node *new_node;         
    new_node = (Node *)malloc(sizeof(Node));
    
    new_node->next = NULL;
    new_node->value = NULL;

    /* Initialize a pointer to the newly created stack */
    Stack *new_stack;
    new_stack = (Stack *)malloc(sizeof(Stack));

    new_stack->top = new_node;
    new_stack->max_size = max_stack_size;
    new_stack->clone = clone;
    new_stack->destroy_t = destroy;
    new_stack->print = print;

    /* Check if the stack was initialized unsuccessfully */    
    if (!new_stack){ 
        return NULL;        /* Return error*/
    }

    return new_stack;       /* Return a pointer to the stack ADT */

}

STACK_STATUS stack_destroy(Stack *stack_pointer) {
    
    /* Assign a temporary node so we can free up the memory it contain and 
       assign the next node as top */
    Node *tmp_top_to_remove = stack_pointer->top;

    while (stack_pointer->top != NULL){
        
        /* Set tmp to the top of stack*/
        tmp_top_to_remove = stack_pointer->top; 
        
        /* Set top to next node*/
        stack_pointer->top = stack_pointer->top->next; 

        /* Dislocate the element inside the note using the user destroy func */
        stack_pointer->destroy_t(tmp_top_to_remove->value);

        /* Dislocate the memory of what used to be the top node in stack */
        free(tmp_top_to_remove);
    }

    /* After we've done freeing each node in the stack we will free the entire 
       stack struct */
    free(stack_pointer); 
    
    if (!stack_pointer){        /* If stack pointer isn't NULL */
        return STACK_SUCCESS;
    } else {
        return STACK_FAILURE;
    }
}

STACK_STATUS stack_push(Stack *stack_pointer, elem_t new_element){
    
    /* Allocate memory for new node and insert the user element as value */
    Node *new_node;
    new_node = (Node *)malloc(sizeof(Node));
    new_node->value = new_element;

    /* Temporary node to check if a new node was pushed successfully*/
    Node *tmp_node = stack_pointer-> top;

    new_node->next = stack_pointer->top; /* Set next node as top of the stack */
    stack_pointer->top = new_node; /* Set the top of the stack as the new node*/ 

    /* If the top isn't the new node or set to null return failure */
    if (stack_pointer->top == tmp_node || !stack_pointer->top){
        return STACK_FAILURE;
    }

    /* New element was successfully pushed to the stack */
    return STACK_SUCCESS;
}


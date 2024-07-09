#include "student.h"
#include "common.h"
#include <stdlib.h>
#include <string.h>

/*struct student {
    char *name;
    int age;
    int id;
};*/

student* student_clone(student* student_to_clone) {
    student* clone;
    clone = (student *)malloc(sizeof(student));

    /* Checking if memory allocation is successful */
    if (!clone){
        return NULL;
    }

    /* Assign all the data from the original student to the clone */
    clone->name = (char *)malloc(sizeof(char)*strlen(student_to_clone->name)); 
    
    /* Checking if memory allocation is successful */
    if (!clone->name){
        free(clone->name);
        free(clone);
        return NULL;
    }
    
    strcpy(clone->name,student_to_clone->name);
    clone->age = student_to_clone->age;
    clone->id = student_to_clone->id;

    return clone;
}

void student_destroy(student* student_to_destroy){
    /* Check if the student exists */
    if (student_to_destroy != NULL){
        
        /* Check if need to dislocate name memory (string needs to be free) */
        if (student_to_destroy->name != NULL){
            free(student_to_destroy->name);
        }

        free(student_to_destroy);
    }
}

void student_print(student* student_to_print){
    /* Check if the student exists */
    if (student_to_print != NULL){

        /* Check if the students name exists */
        if (student_to_print->name != NULL){
            printf("student name: %s, age: %d, id: %d.\n", 
            student_to_print->name,
            student_to_print->age,
            student_to_print->id);    
        }
    }
}


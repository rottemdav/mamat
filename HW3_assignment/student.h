#ifndef STUDENT_H
#define STUDENT_H

typedef struct student {
    char* name;
    int age;
    int id;
} student; /* Opaque pointer */

student* student_clone(student* student_to_clone);
void student_destroy(student* student_to_destroy);
void student_print(student* student_to_print);

#endif /* STUDENT_H_ */
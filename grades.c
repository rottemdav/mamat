#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include "grades.h"
#include "linked-list.h"

#define ERROR -1
#define SUCCESS 0
#define FAIL 1

/* grades == list of all students
*   list of all students containts single Student struct
*   Student >> list of grades for each student 
*   list of grades for each student contains single Course struct
*   Course >> grade
*/

/* Node of student that contains list of grades, next student
   node, id and name. */
typedef struct grades{
    struct list* students;
} Grades;

/* Single student struct with name and age. */
typedef struct student{
    struct list* grades_info;
    char* name;
    int id;
} Student;

/* Single course struct with the matching grade. */
typedef struct course{  
    int grade_value;
    char* course_name; 
} Course;

/* Inside functions for our own use */
Course* create_new_course(const char* name, int grade) ;
Course* find_course(struct list* courses_list, const char* name);
Student* create_new_student(const char* name, int id);
Student* find_student(struct list* student_list, int student_id);

/* Inside clone and destroy functions for students and grades lists */
int course_clone(void *src, void **dst);
void student_destroy(void *student_elem);
void course_destroy(void *course_ptr);

/* A function to clone student element*/
int student_clone(void *src, void **dst){
    /* If there is nothing to clone */
    if (src == NULL){
        return FAIL;
    }

    Student* src_student = (Student *)src;
    Student* clone = (Student *)malloc(sizeof(Student)); 

    if (clone == NULL){
        return FAIL;
    }

    /* Copy the name (and allocates memory)*/
    clone->name = (char *)malloc(sizeof(char)*(strlen(src_student->name)+1));
    if (clone->name == NULL){
        free(clone);
        return FAIL;
    }
    
    strcpy(clone->name,src_student->name);
    /* Check strcpy */
    if (clone->name == NULL){
        free(clone);
        return FAIL;
    }

    /* Initialize a list for grades */
    clone->grades_info = list_init(course_clone,course_destroy);
    if (clone->grades_info == NULL){
        free(clone->name);
        free(clone);
        return FAIL;
    }

    /* Copy each course by elements with course clone using a loop */
    struct iterator* course_it = list_begin(src_student->grades_info);
    while (course_it != NULL){
        
        Course* course = (Course*)list_get(course_it);
        Course* new_course = NULL;

        /* Cloning the course and deallocates the memory otherwise */
        if (course_clone((void*)course, (void**)&new_course) == FAIL) {
            list_destroy(clone->grades_info);
            free(clone->name);
            free(clone);
            return FAIL;
        }

        /* Pushes the new course into the students list */
        if (list_push_back(clone->grades_info, (void*)new_course) == FAIL){
            list_destroy(clone->grades_info);
            free(clone->name);
            free(clone);
            return FAIL;
        }
        course_it = list_next(course_it);
    }

    clone->id = src_student->id;
    *dst = clone;

    return SUCCESS;
}

/* A function to deallocate student element */
void student_destroy(void* student_elem){
    Student* student_ptr = (Student *)student_elem;

    if (student_ptr != NULL){
        if (student_ptr->grades_info != NULL){
            list_destroy(student_ptr->grades_info);
        }

        if (student_ptr->name != NULL){
            free(student_ptr->name);
        }
        free(student_ptr);
    }
}

/* A function to clone course element. */
int course_clone(void *src, void **dst){
    if (src == NULL){
        return FAIL;
    }

    Course* src_course = (Course *)src;
    Course* clone = (Course *)malloc(sizeof(Course));
    if (clone == NULL){
        return FAIL;
    }

    clone->course_name = 
        (char *)malloc(sizeof(char)*(strlen(src_course->course_name)+1));
    /* Check memory allocation */
    if (clone->course_name == NULL){
        free(clone);
        return FAIL;
    }
    
    strcpy(clone->course_name,src_course->course_name);
    /* Check strcpy */
    if (clone->course_name == NULL){
        free(clone);
        return FAIL;
    }

    clone->grade_value = src_course->grade_value;
    *dst = clone;

    return SUCCESS;
}

/* A function to dealocate the memory of course-lists */
void course_destroy(void *course_elem){
    Course* course_ptr = (Course *)course_elem;
    
    if (course_ptr != NULL){
        if (course_ptr->course_name != NULL){
            free(course_ptr->course_name);
        }
        free(course_ptr);
    }
}

Grades* grades_init(){
    Grades* grade_system = (Grades *)malloc(sizeof(Grades));
    
    /* Checking for corret memory allocation */
    if (grade_system == NULL){
        return NULL;
    }
    
    /* Alllocates memory for list of students */
    grade_system->students = list_init(student_clone, student_destroy);
        
    /* Checking for corret memory allocation */
    if (grade_system->students == NULL) {
        free(grade_system);
        return NULL;
    }
    
    return grade_system;
}

void grades_destroy(Grades *grades){
    /* Check if grade system exists, try to destory a non-existant struct. */
    if (grades != NULL) {
        if (grades->students != NULL){
            list_destroy(grades->students);
        }
        free(grades);
    } 
}

int grades_add_student(Grades *grades, const char *name, int id){
    /* Check if the student list pointer exists at all */
    if (grades == NULL || name == NULL){
        return FAIL;
    }

    if (grades->students == NULL){
        return FAIL;
    }

    /* If student exists */
    Student* ghost_student = find_student(grades->students,id);
    if (ghost_student != NULL){
        return FAIL;

    } else {
        /* Will create new student element */
        Student* new_student = create_new_student(name,id);
        if (new_student == NULL){
            return FAIL;
        }
        if (list_push_back(grades->students,(void *)new_student) != SUCCESS){
            student_destroy((void *)new_student);
            return FAIL;
        }

        student_destroy((void *)new_student);
    }
    
    return SUCCESS; 
}

/* Allocates memory for new course if grade list exists otherwise, 
   will alocate memory for new grade sheet and course */
int grades_add_grade(Grades* grades, const char* name,
                     int id, int grade){

    /* Check for existing DS*/                    
    if (grades == NULL || name == NULL || grades->students == NULL) {
        return FAIL;
    }

    if (grade > 100 || grade < 0){
        return FAIL;
    }

    /* Get the wanted student id.  */
    Student* student = find_student(grades->students, id);

    /* There's no existing student with this id. */
    if (student == NULL) {
        return FAIL;
    }

    /* Student grade sheet not created*/
    if (student->grades_info == NULL){
        /* Memory allocations for both grade sheet and course element */
        student->grades_info = list_init(course_clone,course_destroy);
        if (student->grades_info == NULL){
            return FAIL;
        }
        
        Course* new_course = create_new_course(name,grade);
        
        if (new_course == NULL){
            list_destroy(student->grades_info);
            return FAIL;
        }

        /* Will push the new course element into list, if fails free memory */
        if (list_push_front(student->grades_info,(void *)new_course) != SUCCESS)
        {
            free(new_course->course_name);
            free(new_course);
            list_destroy(student->grades_info);
            return FAIL;
        }
        /* Free the memory of the course instance because clone is in list */
        course_destroy((void *)new_course);
        
    } else {    /* Grade sheet exists */
        if (find_course(student->grades_info, name) != NULL){
            return FAIL;
        }

        /* Memory allocations for new course element */
        Course* new_course = create_new_course(name,grade);
        
        /* Check memory allocation of course */
        if (new_course == NULL){
            return FAIL;
        }

        if (list_push_back(student->grades_info, (void *)new_course) 
        != SUCCESS){
            free(new_course->course_name);
            free(new_course);
            return FAIL;
        }
        /* Free the memory of the course instance because clone is in list */
        course_destroy((void *)new_course);
        
    }
    
    return SUCCESS;
}

float grades_calc_avg(struct grades *grades, int id, char **out){

    /* Checks if there is a grade system */
    if (grades == NULL){
        *out = NULL;
        return ERROR;
    }
    
    /* Checks if there is a student list */
    if (grades->students == NULL){
        *out = NULL;
        return ERROR;
    }

    /* Checks if student exists in list */
    Student* student_to_check = find_student(grades->students,id);
    if (student_to_check == NULL){
        *out = NULL;
        return ERROR;
    }

    if (student_to_check->name == NULL || student_to_check->grades_info == NULL)
    {
        *out = NULL;
        return ERROR;
    }

    /* Allocate memory for name*/
    *out = (char *)malloc(sizeof(char)*(strlen(student_to_check->name)+1));
    if (*out == NULL){
        return ERROR;
    }

    strcpy(*out, student_to_check->name);
    /* Check strcpy */
    if (*out == NULL){
        return ERROR;
    }

    int sum = 0;
    int amount_of_courses = 0;
    float average = 0;

    /* Start to check from the begining of the list */
    struct iterator* current_course = list_begin(student_to_check->grades_info);
    while (current_course != NULL){
        Course* course = (Course *)list_get(current_course);
        sum += course->grade_value;
        amount_of_courses++;

        current_course = list_next(current_course);
    }
    if (amount_of_courses == 0) {
        average = 0;
    } else {
        average = (float)sum / amount_of_courses;
    }

    return average;
}

int grades_print_student(Grades* grades, int id){
    /* NULL Errors check. */
    if (!grades) return FAIL;
    if (!grades->students) return FAIL;

    /* Find and create a student to print */
    Student* s_to_print = find_student(grades->students, id);

    /* NULL errors check. */
    if (s_to_print == NULL || s_to_print->name == NULL) return FAIL;

    /* Checks if grades-info exists for list-begin call */
    if (s_to_print->grades_info == NULL) return FAIL;
    

    struct iterator* course_itr = list_begin(s_to_print->grades_info);

    /* Loop through the list and print . */
        
    printf("%s %d:%s", s_to_print->name, s_to_print->id, (course_itr == NULL)
    ? "" : " ");
    
    while (course_itr) {

        /* Get a single course element from the grades list to print. */
        Course* c_to_print = (Course *)list_get(course_itr);

        /* Checks if course and course name exists (doesn't suppose to happen)*/
        if (c_to_print == NULL || c_to_print->course_name == NULL) return FAIL;

        printf("%s %d%s", c_to_print->course_name, c_to_print->grade_value,
        (list_next(course_itr) == NULL) ? "" : ", ");

        course_itr = list_next(course_itr);    
    }
    //printf("boo\n");
    if (course_itr == NULL) {
        printf("\n");
    }
    //
    return SUCCESS;

}

int grades_print_all(Grades* grades){
     /* NULL Errors check. */
    if (grades == NULL) return FAIL;
    
    /* Access to the top of the students list. */
    struct iterator* student_itr = list_begin(grades->students);
    //if (student_itr == NULL) return SUCCESS;

    /* Loop through the list and print */
    while(student_itr != NULL) {
        /* Get a single student element from the list to print. */
        Student* s_to_print = (Student *)list_get(student_itr);

        grades_print_student(grades, s_to_print->id);
        
        /* Go down a row */
        //printf("\n");
        student_itr = list_next(student_itr);
        /*if(student_itr == NULL) {
            printf("\n");
        }*/
        
    }
    //printf("\n");
    return SUCCESS;
}

/**
 * @brief Finds the student (if exists) inside the list
 * @param student_list The list of students we provide
 * @param student_id The student we wish to find
 * @return A pointer to the student, NULL if not found
 * @note Iterates through all the nodes in linked list and compare with id
 * @note No memory allocation
 */
Student* find_student(struct list* student_list, int student_id){
    
    /* Check if the student list or target student pointer is null */
    if (student_list == NULL){
        return NULL; 
    }
  
    /* Start searching from the first node in list */
    struct iterator* student_iterator = list_begin(student_list);
      
    /* Initialize student to return */
    Student* current_student = NULL;

    while (student_iterator != NULL){
        
        /* Get the student element from the list */
        current_student = (Student *)list_get(student_iterator);
        
        /* Checks if student in the node exist*/
        if (current_student == NULL){
            return NULL;
        }

        /* Checks if student id shows in list, if so returns it */
        if (current_student->id == student_id){
            return current_student;          
        }

        /* Advance the iterator */
        student_iterator = list_next(student_iterator);         


    } /* If while loop finished, the student doesn't exist and iterator is on
         NULL */

    return NULL;
}

/**
 * @brief Create a new student element
 * @param name Student's name
 * @param id Student id
 * @return Return a pointer to student element, return NULL in-case of error 
 * @note This function allocates memory for the new student
 */

Student* create_new_student(const char* name, int id){
    Student* new_student = (Student *)malloc(sizeof(Student));
    /* Check memory allocation was successful */
    if (new_student == NULL){
        return NULL;
    }
    
    /* Initialize new list of grades for the student */
    struct list* new_grade_info = list_init(course_clone,course_destroy);
    
    /* Check memory allocation of the grade list was successful */
    if (new_grade_info == NULL){
        free(new_student);
        return NULL;
    }

    new_student->grades_info = new_grade_info;

    /* Allocates memory for name */
    new_student->name = (char *)malloc(sizeof(char)*(strlen(name)+1));
    /* Check memory allocation was successful */
    if (new_student->name == NULL){
        list_destroy(new_grade_info);
        free(new_student);
        return NULL;
    }
    strcpy(new_student->name,name);
    /* Check strcpy */
    if (new_student->name == NULL){
        list_destroy(new_grade_info);
        free(new_student);
        return NULL;
    }

    new_student->id = id;

    return new_student;
}

/**
 * @brief Create a new course element
 * @param name Course's name
 * @param grade Course's grade
 * @return Return a pointer to the course's element, NULL if error
 * @note This function allocated memory for a new course if needed
 */

Course* create_new_course(const char* name, int grade) {
        Course* new_course = (Course *)malloc(sizeof(Course));
        /* Memory allocation check */
        if (new_course == NULL) {
            return NULL;
        }

        new_course->course_name = (char *)malloc(sizeof(char)*(strlen(name)+1));
        /* Memory allocation check */
        if (new_course->course_name == NULL) {
            free(new_course);
            return NULL;
        }
        
        strcpy(new_course->course_name, name);
        if (new_course->course_name == NULL) {
            free(new_course);
            return NULL;
        }
        
        new_course->grade_value = grade;

        return new_course;
}

/**
 * @brief Search for a specific course.
 * @param courses_list grades info.
 * @param name Wanted course name.
 * @return return a pointer to the wanted course. 
 */

Course* find_course(struct list* courses_list, const char* name) {
    if (courses_list == NULL || name == NULL) {
        return NULL;
    }
    
    /* Create the iterato, and assign the begging of the list to it. */
    struct iterator* course_iterator = list_begin(courses_list);

    /* Create the checked course value. */
    Course* current_course = NULL;

    while(course_iterator != NULL) {
        current_course = (Course *)list_get(course_iterator);

        if (strcmp(current_course->course_name, name) == 0) {
            return current_course; 
        }
        course_iterator = list_next(course_iterator);
    }

    return NULL;
}

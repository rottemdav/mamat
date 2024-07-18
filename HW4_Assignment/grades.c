#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
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
Course* create_new_course(char* name, int grade);
Course* find_course(struct list* courses_list, const char* name);
Student* create_new_student(const char* name, int id);
Student* find_student(struct list* student_list, int student_id);

/* Inside clone and destroy functions for students and grades lists */
int course_clone(Course* src, Course **dst);
void student_destroy(Student* student_ptr);
void course_destroy(Course *course_ptr);

/* A function to clone student element*/
int student_clone(Student* src, Student **dst){
    if (src == NULL || dst == NULL){
        return FAIL;
    }

    Student* clone = (Student *)malloc(sizeof(Student));
    if (clone == NULL){
        return FAIL;
    }

    /* Copy the name (and allocates memory)*/
    clone->name = (char *)malloc(sizeof(char)*(strlen(src->name)+1));
    strcpy(clone->name,src->name);
    if (clone->name == NULL){
        free(clone);
        return FAIL;
    }

    /* Initialize a list for grades */
    clone->grades_info = list_init(course_clone,course_destroy);
    if (clone->grades_info == NULL){
        list_destroy(clone->grades_info);
        free(clone->name);
        free(clone);
        return FAIL;
    }
    /* Copy each course by elements with course clone using a loop */
    struct iterator* course_it = list_begin(src->grades_info);
    while (course_it != NULL){
        
        Course* course = (Course*)list_get(course_it);
        Course* new_course;

        /* Cloning the course and deallocates the memory otherwise */
        if (course_clone(course, &new_course) == FAIL) {
            list_destroy(clone->grades_info);
            free(clone->name);
            free(clone);
            return FAIL;
        }

        /* Pushes the new course into the students list */
        if (list_push_back(clone->grades_info, new_course) == FAIL){
            list_destroy(clone->grades_info);
            free(clone->name);
            free(clone);
            return FAIL;
        }
        course_it = list_next(course_it);
    }

    clone->id = src->id;
    *dst = clone;

    return SUCCESS;
}

/* A function to deallocate student element */
void student_destroy(Student* student_ptr){
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
int course_clone(Course* src, Course **dst){
    if (src == NULL || dst == NULL){
        return FAIL;
    }

    Course* clone = (Course *)malloc(sizeof(Course));
    if (clone == NULL){
        free(clone);
        return FAIL;
    }

    clone->course_name = strdup(src->course_name);
    if (clone->course_name == NULL){
        free(clone->course_name);
        free(clone);
        return FAIL;
    }

    clone->grade_value = src->grade_value;
    *dst = clone;

    return SUCCESS;
}

/* A function to dealocate the memory of course-lists */
void course_destroy(Course *course_ptr){ 
    /* Checks if course pointer exists, if so free the memory*/
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
    struct list* new_students = list_init(student_clone, student_destroy);
        
    /* Checking for corret memory allocation */
    if (new_students == NULL) {
        grades_destroy(grade_system);
        return NULL;
    }

    grade_system->students = new_students;
    
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
    if (find_student(grades->students,id) != NULL){
        return FAIL;

    } else {
        /* Will create new student element */
        Student* new_student = create_new_student(name,id);
        if (new_student == NULL){
            return FAIL;
        }
        if (list_push_front(grades->students, new_student) != SUCCESS){
            student_destroy(new_student);
            return FAIL;
        }

        student_destroy(new_student);
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
        if (list_push_front(student->grades_info,new_course) != SUCCESS){
            free(new_course->course_name);
            free(new_course);
            list_destroy(student->grades_info);
            return FAIL;
        }
        /* Free the memory of the course instance because clone is in list */
        course_destroy(new_course);
        
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

        if (list_push_front(student->grades_info, new_course) != SUCCESS){
            free(new_course->course_name);
            free(new_course);
            return FAIL;
        }
        /* Free the memory of the course instance because clone is in list */
        course_destroy(new_course);
        
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

    strcpy(*out,student_to_check->name);

    int sum = 0;
    int amount_of_courses = 0;
    float average = 0;

    /* Start to check from the begining of the list */
    struct iterator* current_course = list_begin(student_to_check->grades_info);
    while (current_course != NULL){
        Course* course = list_get(current_course);
        sum += course->grade_value;
        amount_of_courses++;

        current_course = list_next(current_course);
    }

    average = (float)sum / amount_of_courses;

    return average;
}

int grades_print_student(Grades* grades, int id){
    /* NULL Errors check. */
    if (!grades) return FAIL;
    if (!grades->students) return FAIL;

    /* Find and create a student to print */
    Student* s_to_print = find_student(grades->students, id);

    /* NULL errors check. */
    if (!s_to_print) return FAIL;
    if (!s_to_print->name) return FAIL;

    /* Checks if grades-info exists for list-begin call */
    if (!s_to_print->grades_info) return FAIL;
    
    /* Loop through the list and print . */
    printf("%s %d: ", s_to_print->name, id);

    struct iterator* course_itr = list_begin(s_to_print->grades_info);
    while (course_itr) {

        /* Get a single course element from the grades list to print. */
        Course* c_to_print = (Course*)list_get(course_itr);

        /* Checks if course and course name exists (doesn't suppose to happen) */
        if (!c_to_print) return FAIL;
        if (!c_to_print->course_name) return FAIL;


        printf("%s %d, ", c_to_print->course_name, c_to_print->grade_value);
        
        course_itr = list_next(course_itr);                 
    }

    return SUCCESS;

}

int grades_print_all(Grades* grades){
     /* NULL Errors check. */
    if (!grades) return FAIL;

    /* Access to the top of the students list. */
    struct iterator* student_itr = list_begin(grades->students);

    /* Loop through the list and print */
    while(student_itr != NULL) {
        /* Get a single student element from the list to print. */
        Student* s_to_print = (Student*)list_get(student_itr);
        grades_print_student(grades, s_to_print->id);
        
        /* Go down a row */
        printf("\n");
        student_itr = list_next(student_itr);
        
    }
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
        current_student = list_get(student_iterator);
        
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
        list_destroy(new_grade_info);
        free(new_student);
        return NULL;
    }

    /* Allocates memory for name */
    char* new_name = strdup(name);
    
    /* Check memory allocation was successful */
    if (new_name == NULL){
        free(new_name);
        list_destroy(new_grade_info);
        free(new_student);
        return NULL;
    }

    new_student->grades_info = new_grade_info;
    new_student->name = new_name;
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

Course* create_new_course(char* name, int grade) {
        Course* new_course = (Course *)malloc(sizeof(Course));
        /* Memory allocation check */
        if (new_course == NULL) {
            return FAIL;
        }

        new_course->course_name = strdup(name);
        /* Memory allocation check */
        if (new_course->course_name == NULL) {
            free(new_course);
            return FAIL;
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
        current_course = list_get(course_iterator);

        if (strcmp(current_course->course_name, name) == 0) {
            return current_course; 
        }
        course_iterator = list_next(course_iterator);
    }

    return NULL;
}
#include "grades.h"
#include "linked-list.h"
#include <string.h>
#include <stdbool.h>

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

/* A function to clone student element*/
int student_clone(Student* src, Student **dst){
    if (src == NULL || dst == NULL){
        return FAIL;
    }
    Student* clone = (Student *)malloc(sizeof(Student*));
    if (clone == NULL){
        return FAIL;
    }

    *clone = *src;
    *dst = clone;
}

/* A function to deallocate student element */
void student_destroy(Student* student_ptr){
    if (student_ptr != NULL){
        if (student_ptr->grades_info != NULL){
             list_destroy(student_ptr->grades_info);
        }
    }
   free(student_ptr->name);
   free(student_ptr);
}

/* A function to clone course element. */
int grade_clone(Course* src, Course **dst){
    if (src == NULL || dst == NULL){
        return FAIL;
    }
    Course* clone = (Course *)malloc(sizeof(Course*));
    if (clone == NULL){
        return FAIL;
    }

    *clone = *src;
    *dst = clone;
}

/* A function to dealocate the memory that stored a single course struct*/
void grade_destroy(Course* course_ptr){
   free(course_ptr->course_name);
   free(course_ptr);
}

Grades* grades_init(){
    Grades* grade_system = (Grades *)malloc(sizeof(Grades));
    
    /* Checking for corret memory allocation */
    if (grade_system == NULL){
        return NULL;
    }
    
    struct list* new_students = list_init(student_clone, student_destroy);
        
    /* Checking for corret memory allocation */
    if (new_students == NULL) {
        return NULL;
    }

    grade_system->students = new_students;
    
    return grade_system;
}

void grades_destroy(Grades *grades){
    /* Check for a try to destory a non-existant struct. */
    if (grades == NULL) {
        return;
    } 
    /* There's a student list - deallocate */
    list_destroy(grades->students);
}

int grades_add_student(Grades *grades, const char *name, int id){
    /* Check if the student list pointer exists at all*/
    if (grades == NULL){
        return FAIL;
    }
    
    /* If list of students is empty - will add student*/
    if (grades->students == NULL){
        Student* new_student = (Student *)malloc(sizeof(Student *));
        
    } else { /* List of students not empty (need to check existence) */
       
        /* Checks if the student is already in the list */
        struct iterator* student_position = find_student(grades->students, id);       
        if (student_position != NULL){
            return FAIL; 
        }

        /* ---- Student not on list so we create a new one ---- */

        Student* new_student = create_new_student(name,id);
        if (new_student == NULL){
            return FAIL;
        }
        
        /* Insert the student to the back of the list */
        list_push_back(grades->students, new_student);

    } /* Succesfully created a student */
    
    return SUCCESS; 
}

int grades_add_grade(Grades* grades, const char* name,
                     int id, int grade){

    /* Check for existing DS*/                    
    if (grades == NULL) {
        return FAIL;
    }

    /* Get the wanted student id.  */
    Student* student_id = (Student*)find_student(grades->students, id);

    /* There's not an existing student with this id. */
    if (student_id == NULL) {
        return FAIL;
    }
    
    /* Checks if there's grades info, if not, allocate new course. */
    if (student_id->grades_info == NULL) {
        Course* new_course = create_new_course(name, grade);

        new_course->course_name = name;
        new_course->grade_value = grade;

        /* Adds the course to the front of grades info.*/
        if (list_push_front(student_id->grades_info, new_course) != 0) {
            return FAIL;
        };

    /* There's courses in the grades info, find the relevant course. */
    } else {    
        Course* mod_course = find_course(student_id->grades_info, name);

        /* There's not an existing course, create a new one. */
        if (mod_course == NULL) {
            Course* new_course = create_new_course(name, grade);
            if (new_course == NULL) {
                return FAIL;
            }
            new_course->course_name = name;
            new_course->grade_value = grade;
            
            /* Insert the course to the back of grades info list. */
            if (list_push_back(student_id->grades_info, new_course) != 0 )  {
                return FAIL;
            } 
        /* There's existing course, updating the grade.*/    
        } else {
            mod_course->grade_value = grade;
        }

    }
    return SUCCESS;
}

float grades_calc_avg(struct grades *grades, int id, char **out){
    if (grades == NULL){
        *out = NULL;
        return ERROR;
    }
    Student* student_to_check = find_student(grades->students,id);
    if (student_to_check == NULL){
        *out = NULL;
        return ERROR;
    }

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
}

int grades_print_student(){

}

int grades_print_all(){

}

/**
 * @brief Finds the student (if exists) inside the list
 * @param student_list The list of students we provide
 * @param student_id The student we wish to find
 * @return A pointer to iterator for node position in list, NULL if not found
 * @note Iterates through all the nodes in linked list and compare with id
 * @note No memory allocation
 */
struct iterator* find_student(struct list* student_list, int student_id){
    
    /* Check if the student list or target student pointer is null */
    if (student_list == NULL){
        return NULL; 
    }
    
    /* Current node to check*/
    struct iterator* student_iterator; 
        
    /* Start searching from the first node in list */
    student_iterator = list_begin(student_list);
        
    while (student_iterator != NULL){
        
        /* Get the student element from the list */
        Student* current_student = list_get(student_iterator); /* --?-- Type managment needed? to change the iterator type to student. --?-- */
        
        /* Checks if student id shows in list */
        if (current_student->id == student_id){
            return student_iterator;          /* --?-- isn't the value that should be returned is the 'current_student' and not the iterator, since we're extracting the current student based on the iterator? --?-- */

        }

        /* Advance the iterator */
        list_next(student_iterator);         /* --?-- missing assignment? --?-- */


    } /* If while loop finished, the student doesn't exist and iterator is on
         NULL */

    /* Returns the position of the student inside the linked list */
    return student_iterator;
}

/**
 * @brief Create a new student element
 * @param name Student's name
 * @param id Student id
 * @return Return a pointer to student element, return NULL in-case of error 
 * @note This function allocates memory for the new student
 */

Student* create_new_student(char* name, int id){
    Student* new_student = (Student *)malloc(sizeof(Student *));
    /* Check memory allocation was successful */
    if (new_student == NULL){
        return NULL;
    }
    
    struct list* new_grade_info = list_init(grade_clone,grades_destroy);
    /* Check memory allocation was successful */
    if (new_grade_info == NULL){
        return NULL;
    }

    /* Check memory allocation was successful */
    char* new_name = (char *)malloc(sizeof(char)*(strlen(name)+1));
    if (new_name == NULL){
        return NULL;
    }

    strcpy(new_name, name);

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
        Course* new_course = (Course *)malloc(sizeof(Course *));
        /* Memory allocation check */
        if (new_course == NULL) {
            return FAIL;
        }

        char* new_course_name = (char*)malloc(sizeof(char)*(strlen(name)+1));
        /* Memory allocation check */
        if (new_course_name == NULL) {
            return FAIL;
        }

        strcpy(new_course_name, name);

        new_course->course_name = new_course_name;
        new_course->grade_value = grade;

        return new_course;

}

/**
 * @brief Search for a specific course.
 * @param courses_list grades info.
 * @param name Wanted course name.
 * @return return a pointer to the wanted course. 
 */

struct iterator* find_course(struct list* courses_list, char* name) {
    if (courses_list == NULL) {
        return NULL;
    }
    /* Create the iterato, and assign the begging of the list to it. */
    struct iterator* course_iterator; 
    course_iterator = list_begin(courses_list);

    /* Create the checked course value. */
    Course* current_course;

    while(course_iterator != NULL) {
        current_course = (Course*)list_get(course_iterator);
        if (strcmp(current_course->course_name, name) == 0) {
            return current_course; 
        }
        course_iterator = list_next(course_iterator);
    }

    return current_course;

}

/* Old implementation 
    struct iterator* i_student = list_begin(grades);
    Student* current_student;
    while(!i_student){
        current_student = (Student*)list_get(current_student);
        if (current_student->id == id) {
            break;
        }
        i_student = list_next(i_student);
    }
*/
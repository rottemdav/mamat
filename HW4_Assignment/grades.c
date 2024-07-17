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

    return SUCCESS;
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
int course_clone(Course* src, Course **dst){
    if (src == NULL || dst == NULL){
        return FAIL;
    }
    Course* clone = (Course *)malloc(sizeof(Course*));
    if (clone == NULL){
        return FAIL;
    }

    *clone = *src;
    *dst = clone;

    return SUCCESS;
}

/* A function to dealocate the memory of course-lists */
void course_destroy(Course *course_ptr){ 
   free(course_ptr->course_name);
   free(course_ptr);
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
        return NULL;
    }

    grade_system->students = new_students;
    
    return grade_system;
}

void grades_destroy(Grades *grades){
    /* Check if grade system exists, try to destory a non-existant struct. */
    if (grades == NULL) {
        return;
    } 
    /* There's a student list - deallocate */
    list_destroy(grades->students);
}

int grades_add_student(Grades *grades, const char *name, int id){
    /* Check if the student list pointer exists at all */
    if (grades == NULL){
        return FAIL;
    }
    
    /* If list of students is empty - will add student */
    if (grades->students == NULL){
        /* Allocate memory for new student */
        Student* new_student = create_new_student(name,id);

        /* Checks memory allocation for student */
        if (!new_student){
            return FAIL;
        }
        
        /* Pushes the student into the list, checks for pushing attempt */
        if (list_push_back(grades->students, new_student) != SUCCESS){
            return FAIL;
        }
        
    } else { /* List of students not empty (need to check existence) */
       
        /* Checks if the student is already in the list */
        Student* student_to_check = find_student(grades->students, id);       
        if (student_to_check != NULL){
            return FAIL; 
        }

        /* ---- Student not on list so we create a new one ---- */

        Student* new_student = create_new_student(name,id);
        
        /* Checks for memory allocation */
        if (new_student == NULL){
            return FAIL;
        }
        
        /* Insert the student to the back of the list, checks pushing attempt */
        if (list_push_back(grades->students, new_student) != SUCCESS){
            return FAIL;
        }

    } /* Succesfully created a student and pushed inside the list */
    
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

    /* There's no existing student with this id. */
    if (student_id == NULL) {
        return FAIL;
    }
    
    /* Checks if there's grades info, if not, allocate new course. */
    if (student_id->grades_info == NULL) {
        Course* new_course = create_new_course(name, grade);
        
        /* Checks memory allocation for new course */
        if (new_course == NULL){
            return FAIL;
        }
        
        /* Adds the course to the front of grades info, checks push attempt */
        if (list_push_front(student_id->grades_info, new_course) != SUCCESS) {
            return FAIL;
        };

    /* There's courses in the grades info, find the relevant course. */
    } else {    
        Course* mod_course = find_course(student_id->grades_info, name);

        /* There's no existing course, create a new one. */
        if (mod_course == NULL) {
            Course* new_course = create_new_course(name, grade);
            
            /* Checks memory allocation */
            if (new_course == NULL) {
                return FAIL;
            }
            
            /* Insert the course to the back of grades info list. */
            if (list_push_back(student_id->grades_info, new_course) != SUCCESS){
                return FAIL;
            }
             
        /* There's existing course, update the grade.*/    
        } else {
            
            /* Checks if grade value is between 0-100 */
            if (grade < 0 || grade > 100){
                return FAIL;
            }
            
            mod_course->grade_value = grade;
        }

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

    if (student_to_check->name == NULL){
        *out = NULL;
        return ERROR;
    }

    /* Allocate memory for name*/
    *out = (char *)malloc(sizeof(char)*(strlen(student_to_check->name) + 1));

    /* Checks memory allocation for out*/
    if (*out == NULL){
        return ERROR;
    }

    /* Checks if there is a list of grades */
    if (student_to_check->grades_info == NULL){
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
    strcpy(*out, student_to_check->name);

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
    while (!course_itr) {

        /* Get a single course element from the grades list to print. */
        Course* c_to_print = (Course*)list_get(s_to_print->grades_info);

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
    struct iterator* student_itr = list(begin(grades->students));

    /* Loop through the list and print . */
    while(!student_itr) {
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
    
    /* Current node to check*/
    struct iterator* student_iterator; 
        
    /* Initialize student to return */
    Student* current_student = NULL;

    /* Start searching from the first node in list */
    student_iterator = list_begin(student_list);

    while (student_iterator != NULL){
        
        /* Get the student element from the list */
        current_student = list_get(student_iterator);
        
        /* Checks if student in the node exist*/
        if (!current_student){
            return NULL;
        }

        /* Checks if student id shows in list */
        if (current_student->id == student_id){
            return current_student;          

        }

        /* Advance the iterator */
        student_iterator = list_next(student_iterator);         


    } /* If while loop finished, the student doesn't exist and iterator is on
         NULL */

    /* Returns the position of the student inside the linked list */
    return current_student;
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
    
    /* Initialize new list of grades for the student */
    struct list* new_grade_info = list_init(course_clone,course_destroy);
    
    /* Check memory allocation of the grade list was successful */
    if (new_grade_info == NULL){
        return NULL;
    }

    /* Allocates memory for name */
    char* new_name = (char *)malloc(sizeof(char)*(strlen(name)+1));
    
    /* Check memory allocation was successful */
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

struct Course* find_course(struct list* courses_list, char* name) {
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
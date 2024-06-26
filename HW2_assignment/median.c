#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

void operate(FILE *f);


/**
 * @param argv supposed to get the file grades.txt.  
 * @return median of the grades.
 */

int main (int argc, char** argv){
    FILE *f;

    /* checks if there's a file in the input, or if strcmp =="0", 
     * meaning that the user entered "-" as an argument 
     */
    if (argc == 1 || !strcmp("-", argv[1])) {
        f = stdin;
    } else {    // otherwise will read the file 
        f = fopen(argv[1], "r");
    }

    if (!f){
        fprintf(stderr, "file not found: \"%s\"\n", argv[1]);
        return 1;
    }

    operate(f);

    fclose(f);
}

void operate(FILE *f){
    int grade;
    int retval;
    int median;
    int hist[100] = {0};
    
    int line_n = 1;
    while (1) {
        retval = fscanf(f, "%d", &grade);
        if (retval == EOF) {
            break; /*reached the end of the file*/
        } else if (retval != 1) {
            /*error*/
            fprintf(stderr, "Error: not a number\n");
            exit(1);
            
        } else if (grade < 0 || grade > 100){ 
            /*error*/
            fprintf(stderr, "Error at line %d: grade %d invalid",
            line_n, grade);
            exit(1);
        } else { // Grade is legal and add a new line and fill the histogram
            hist[grade]++;
            line_n++;
        }
    }
    
    // Intiialize counter
    int counter = 0;

    // Find the median by going over the histogram
    for (int current_grade = 0; current_grade < 100; current_grade++){
        if (hist[current_grade] == 0) {
            continue;
        } else {
            counter += hist[current_grade];
        }
        
        /*
         * Check to see if the amount of students counted so far in the 
         * histogram is above or equal to half for every grade. If so, return
         * the grade (hist[current_grade]) as the median.
         */         
        if (counter >= line_n/2){
            //printf("found the median.\n");
            median = current_grade;
            break;
        }
    }

    printf("%d\n", median);
}
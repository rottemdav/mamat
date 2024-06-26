#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void operate (FILE *f );

int main(int argc, char **argv) { /*gets the input argments number and content*/
    FILE *f;

    if (argc == 1 || !strcmp("-", argv[1])) { /* checks if there's a file in the
input, or if strcmp =="0", meaning that the user entered "-" as an argument */
        f = stdin; 
        //fprintf(stdout, "getting keyboard data.\n");
    } else {
        f = fopen(argv[1], "r"); /*gets the file name*/
        //fprintf(stdout, "getting file data.\n");
    }

    /*errors check*/

    if(!f) {
        fprintf(stderr, "File not found: \"%s\"\n", argv[1]);
        return 1;
    }
    
    operate(f);

    if (f != stdin) {
        fclose(f);
    }

}

void operate(FILE *f) {
    int grade;
    int retval;
    int max;
    int line_n; 

    max = 0;
    line_n = 0;

    while (1) {
        retval = fscanf(f, "%d", &grade);
        if (retval == EOF) {
            break; /*reached the end of the file*/
        } else if (retval != 1) {
            /*error*/
            fprintf(stderr, "Error: not a number\n");
            exit(1);
        } else if (grade < 0 || grade > 100) { 
            /*error*/
            fprintf(stderr, "Error at line %d: grade %d invalid",
            line_n, grade);
            exit(1);
        }
        if (grade > max) {
            max = grade;
        }
        /*printf("max: %d\n",max );*/
        line_n++;
    }
    printf("%d\n", max);
}
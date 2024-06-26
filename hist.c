#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static FILE *f;
static int nbins = 10;

void operate(int *bins);

void parse_arg(int argc, char **argv) {
    f = stdin; /*makes the pointer points to the same file as the stdin*/
    for (int i = 1; i < argc; i++) { /*the for loop is for handling several writing orders*/
        if (!strcmp(argv[i], "-")) {
            f = stdin;
            //fprintf(stdout, "getting keyboard data.\n");
        } else if (!strcmp(argv[i], "-nbins")) { /*the user entered the desired bins number*/
            nbins = i<argc-1 ? atoi(argv[i+1]) : 10 ; /*checks if there's a number for n_bins. if not - defaults to 10*/
            i++;
        } else {
            f = fopen(argv[i], "r"); /* if there isn't keyboard input - access the given file on read mode*/
            //fprintf(stdout, "getting file data.\n");
        }
    }
}

int main(int argc, char **argv) {

    parse_arg(argc, argv);
    /* error check*/

    if (!f) {
        fprintf(stderr, "file not found: \"%s\"\n", argv[1]);
        return 1;
    }
    /*creates an array*/
    int *hist_arr = (int*)calloc(nbins, sizeof(int));
    for (int i = 0; i <nbins; i++) { /*initialize the histogram array to all zeros*/
        hist_arr[i] = 0;
    }

    operate(hist_arr);
    free(hist_arr);

    if (f != stdin) {
        fclose(f);
    }
}

void operate(int *bins) {
    int grade;
    int retval;
    int line_n;
    double bin_width;
    
    line_n = 0;


    while(1) {
        retval = fscanf(f, "%d", &grade);
        if (retval == EOF) {
            break; /*reached the end*/
        } else if (retval != 1) {
            /*error */
            fprintf(stderr, "Error: not a number\n");
            exit(1);
        } else if (grade < 0 || grade > 100) { 
            /*error*/
            fprintf(stderr, "Error at line %d: grade %d invalid",
            line_n, grade);
            exit(1);
        }
        /*allocate the bin*/
        int location = grade / (100/nbins);
        bins[location]++;
    }

    /*print the histogram*/
    bin_width = 100 / nbins;
    for (int i=0; i<nbins; i++) {
        printf("%d-%d\t%d\n",
        i * bin_width, /* lower edge */
        (i<nbins-1)? ((i+1) * bin_width-1):100, /*higher edge*/
        bins[i]); /* value*/
    } 
}
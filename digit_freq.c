// 123456789
#include <stdio.h>  // printf, scanf
#include <stdlib.h> // malloc, free
#include <string.h> // strlen, strcat, etc.
#include <math.h>   // sqrt, pow, floor, ceil, etc.

#define HIST_SIZE 10

int main() {

    int hist[HIST_SIZE] = {0}; // Initialize our occurence histogram.
    char input_char;

    while (scanf("%c",&input_char) != EOF){
        int diff = (int)input_char - (int)'0';

        /**  
         * If the current character is a number than update the histogram
         * accordingly.
        */ 
        if (diff >= 0 && diff <= 9){ 
            hist[diff]++;
        }
    }

    // Will print out the histogram of the number occurences.
    for (int i = 0; i < HIST_SIZE; i++){
        printf("%d%s", hist[i], i<9 ? " " : "");
    }

    /* Enter your code here. Read input from STDIN. Print output to STDOUT */    
    return 0;
}

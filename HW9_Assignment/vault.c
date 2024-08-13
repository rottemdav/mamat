
#include <stdio.h>
#include <stdlib.h>
#include "support.h"
#include "phases.h"


FILE *infile;

int main(int argc, char *argv[])
{
    char *input;

    /* When run with no arguments, the vault reads its input lines
     * from standard input. */
    if (argc == 1) {
    infile = stdin;
    }

    /* When run with one argument <file>, the vault reads from <file>
     * until EOF, and then switches to standard input. Thus, as you
     * solve each phase, you can add its solution string to <file> and
     * avoid having to retype it. */
    else if (argc == 2) {
    if (!(infile = fopen(argv[1], "r"))) {
        printf("%s: Error: Couldn't open %s\n", argv[0], argv[1]);
        exit(8);
    }
    }

    /* You can't call the vault with more than 1 command line argument. */
    else {
    printf("Usage: %s [<input_file>]\n", argv[0]);
    exit(8);
    }

    /* Do all sorts of secret stuff that makes the vault harder to solve. */
    initialize_bomb();

    printf("Welcome to my cyber vault. You have 6 phases ..\n");
    printf("try not to blow yourself up. Have a nice vacation!\n");

    /* Hmm...  Six phases must be more secure than one phase! */
    input = read_line();             /* Get input                   */
    phase_1(input);                  /* Run the phase               */
    phase_defused();                 /* Drat!  They figured it out!
                      * Let me know how they did it. */
    printf("Phase 1 solved. It was too easy. How about the next one?\n");

    /* The second phase is harder.  No one will ever figure out
     * how to defuse this... */
    input = read_line();
    phase_2(input);
    phase_defused();
    printf("That's number 2.  Keep going!\n");

    /* I guess this is too easy so far.  Some more complex code will
     * confuse people. */
    input = read_line();
    phase_3(input);
    phase_defused();
    printf("Halfway there! Already got a passing grade ;)\n");

    /* Oh yeah?  Well, how good is your math?  Try on this saucy problem! */
    input = read_line();
    phase_4(input);
    phase_defused();
    printf("So you got that one.  Try this one.\n");

    /* Round and round in memory we go,  */
    input = read_line();
    phase_5(input);
    phase_defused();
    printf("Good work!  On to the final...\n");

    /* This phase will never be used, since no one will get past the
     * earlier ones.  But just in case, make this one extra hard. */
    input = read_line();
    phase_6(input);
    phase_defused();

    /* Wow, they got it!  */


    return 0;
}


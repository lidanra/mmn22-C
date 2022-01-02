
/* A program that receives commands about sets from the user and executes them.*/

#include "input.h"

/* A function that initializes the sets sets to a value of 0 */
void initialize();

/* A function that performs the entire process of the program and the user interaction */
void program_process(char line[]);

set setA, setB, setC, setD, setE, setF;

/* The main method: */
int main() {
    char line[LINE_LEN];
    initialize(); /* Initialize the set variables to a value of 0 */
    program_process(line);
    return 0;
}


void initialize() {
    unsigned int tmp[]={0,0,0,0};
    read_set(&setA, tmp);
    read_set(&setB, tmp);
    read_set(&setC, tmp);
    read_set(&setD, tmp);
    read_set(&setE, tmp);
    read_set(&setF, tmp);
}


void program_process(char line[]) {
    while (1) { /* Until the stop command or the end of the file (there is an exit function) */
        get_line(line); /* get the input line the user entered */
        handleLine(line); /* handle the line the user entered */
    }
}


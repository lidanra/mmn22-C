
#include "set.h"
#include <ctype.h>
#include <string.h>
#include <stdlib.h> /* for atof */

#define LINE_LEN 100
#define NUM_FUNC 7
#define NUM_SET 6

/* Macros for common errors: */

#define EXTRANEOUS_TEXT(ch) \
    if (ch) {\
        printf("Extraneous text after end of command\n");\
        return;\
    }
#define UNDEFINED_COMMAND_NAME(ch) \
    if (ch == -1) { \
        printf("Undefined command name\n"); \
        return; \
        }

#define MISSING_PARAMETER(ch) \
    if (!ch) {\
        printf("Missing parameter\n");\
        return;\
    }

#define OUT_OF_RANGE(ch) \
    if (ch <-1 || ch> 127){ \
        printf("Invalid set member - value out of range\n");    \
        return; \
    }

#define MISSING_COMMA(ch) \
    if (ch != ',') {\
        printf("Missing comma\n");\
        return;\
    }

#define MULTIPLE_CONSECUTIVE_COMMAS(ch) \
    if (ch == ',') {\
        printf("Multiple consecutive commas\n");\
        return;\
    }
#define NOT_TERMINATED_CORRECTLY(ch) \
    if(num!=-1){\
        printf("List of set members is not terminated correctly\n");\
        return;\
}

/* numbers to identify the command names */
enum names {
    READ_SET, PRINT_SET, UNION_SET, INTERSECT_SET, SUB_SET, SYMDIFF_SET, STOP
};
enum sets {
    SETA, SETB, SETC, SETD, SETE, SETF
};

/* A function that get into line the line the user inserted, and prints it */
void get_line(char line[]);

/* A function that receives an input line and handle it (does the command or prints an error) */
void handleLine(char line[]);

/* A function that prints a goodbye message to the user and exits the program */
void stop();

/* A function that gets a pointer to the beginning of the first word in a command and returns a
 * number representing the command (or -1 if the first word is not a command) */
int firstWord(char *line);

/* A function that gets a pointer to the beginning of the set word in a command and returns a
 * number representing the set (or -1 if the first word is not a set) */
int setWord(char *line);

/* A function that receives a string and returns a pointer to the first non-white character in the string */
char *skipSpacesAndTabs(char *s);

/* A function that accepts one of the integers 0, 1, 2, 3, 4, 5 and
 * returns a pointer to the set with the same name as the enum */
set *whichSet(int x);

/* A function that receives a int (enum) and checks whether he is a name of a set (SETA,SETB,SETC,SETD,SETE,SETF) */
int isSet(int x);

/* A function that receives a string and removes the white characters from it */
void removeSpaces(char *str);

/*A function that accepts a char pointer (to the beginning of a number) and returns a pointer to the end of the number */
char *skipNum(char *s);







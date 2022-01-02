
#include "input.h"

/* we need access to these variables in this file */
extern set setA, setB, setC, setD, setE, setF;

/* an array to easily compare the first word to the command names */
char *commandNames[NUM_FUNC] = {"read_set", "print_set", "union_set", "intersect_set", "sub_set",
                                "symdiff_set", "stop"};
char *setNames[NUM_SET] = {"SETA", "SETB", "SETC", "SETD", "SETE", "SETF"};

void get_line(char line[]) {
    printf("Please enter a command:\n"); /* User friendly message */

    /* If there's no line (not even line break character) the
     * program reached the end of the file before receiving stop command */
    if (fgets(line, LINE_LEN, stdin) == NULL) {
        printf("\nReached EOF before stop command\n");
        exit(0);
    }

    /* print the line the user entered: */
    printf("The line you entered is:\n");
    printf("%s", line);

}

void handleLine(char line[]) {
    int i = 0;
    int setA = 0;
    int setB = 0;
    int setC = 0;
    char *p = NULL;
    char *nextNum = NULL;

    p = line;

    p = skipSpacesAndTabs(p); /* if there are spaces or tabs at the beginning we ignore them */

    if (p[0] == '\n') { /* check if the line is only with spaces */
        printf("(blank line)\n");
        return;
    }

    i = firstWord(p); /* we classify the command name */
    if (i == -1) {
        printf("Undefined command name\n");
        return;
    }
  p += strlen(commandNames[i]); /* We no longer need the command name */

    removeSpaces(p); /* In this part of the line we do not need spaces */

    if (p[0] == ',') {
        printf("Illegal comma\n");
        return;
    }


    if (i == STOP) {
        EXTRANEOUS_TEXT(p[0])
        stop(); /* we need to stop the program (the user entered "stop") */
    }

    /* In all the other functions the first variable is SETA,SETB,SETC,SETD,SETE,SETF : */

    MISSING_PARAMETER(p[0])

    setA = setWord(p); /* we classify the first set */


    if (setA == -1) {
        printf("Undefined set name\n");
        return;
    }

    p += strlen(setNames[setA]); /* We no longer need the set name */

    /* we now know that setA is a set */
    if (i == PRINT_SET) { /* need only one SET name */
        EXTRANEOUS_TEXT(p[0])
        print_set(whichSet(setA));

        return;
    }
    /* check if missing the next paeameter */
    if(p[0]=='\0'){
        printf("Missing parameter\n");
        return;
    }
    MISSING_COMMA(p[0])
    if (i == UNION_SET || i == INTERSECT_SET || i == SUB_SET || i == SYMDIFF_SET) { /* need 2 more sets (two more) */
        p++;
        MULTIPLE_CONSECUTIVE_COMMAS(p[0])
        removeSpaces(p);
        setB = setWord(p); /* we classify the second set */
        if (setB == -1) {
            printf("Undefined set name\n");
            return;
        }

        p += strlen(setNames[setB]); /* We no longer need the set name */

        removeSpaces(p);
        /* check if missing the next set ot missing a comma */
        MISSING_PARAMETER(p[0])
        MISSING_COMMA(p[0])
        p++;
        removeSpaces(p);
        MULTIPLE_CONSECUTIVE_COMMAS(p[0])
        setC = setWord(p); /* we classify the thired set */
        UNDEFINED_COMMAND_NAME(setC) /* check if the set is recogniezd */
        p += strlen(setNames[setC]);
        EXTRANEOUS_TEXT(p[0])

        if (i == UNION_SET){
            union_set(whichSet(setA), whichSet(setB), whichSet(setC));}
        else if (i == INTERSECT_SET)
            intersect_set(whichSet(setA), whichSet(setB), whichSet(setC));
        else if (i == SUB_SET)
            sub_set(whichSet(setA), whichSet(setB), whichSet(setC));
        else
            symdiff_set(whichSet(setA), whichSet(setB), whichSet(setC));
        return;
    }
    /* we now know that i is READ_SET(so we need a first number:)*/


    if (!isdigit(p[1])) { /* the parameter may not be a number */
        MISSING_PARAMETER(p[1])
        MULTIPLE_CONSECUTIVE_COMMAS(p[1])


        if (p[1] != '-' || !isdigit(p[2])) { /* check for negative number */
            printf("Invalid parameter - not a integer\n");
            return;
        }
    }

    /* we now know that there is a first number */
    MISSING_COMMA(p[0])
    if (i == READ_SET) { /* we need one more comma and more number\s */
        unsigned int num_arr [] ={0,0,0,0};
        int num = atof(p + 1);
        nextNum = skipNum(p + 1);
        OUT_OF_RANGE(num)
        if (num == -1){
            nextNum = skipNum(nextNum + 1);
        }
	
        while (num != -1 && *nextNum!='\0'){
            num_arr[(num)/32] |= 1 << (num%32); /* put the numbers on each bit number in array of 4 integers */
            MISSING_COMMA(*nextNum)
            nextNum += 1; /* we want it on the first digit of the number */
            num = atof(nextNum);
            nextNum = skipNum(nextNum + 1);

            if (!isdigit(nextNum[1]) && *nextNum!='\0') { /* the parameter may not be a number */
                MULTIPLE_CONSECUTIVE_COMMAS(nextNum[1])
                if (nextNum[1] != '-' || !isdigit(nextNum[2])) { /* check for negative number */
                    if( num == -1){
                        EXTRANEOUS_TEXT(p[0])
                    }
                    printf("Invalid parameter - not a integer\n");
                    return;
                }
            }
            if (!isdigit(nextNum[0]) && nextNum[0] != ',' && *nextNum!='\0') { /* the parameter may not be a number */
                printf("Invalid parameter - not a integer\n");
                return;
            }
            OUT_OF_RANGE(num)
        }
        NOT_TERMINATED_CORRECTLY(num)
        if(num==-1){
        	EXTRANEOUS_TEXT(nextNum[0])
        }
        read_set(whichSet(setA), num_arr);
        return;
    }
    /* All right! */

}

void stop() {
    printf("You finished using my program,\nI hope you enjoyed!\n"); /* goodbye message :) */
    exit(0);
}

int firstWord(char *p) {
    int i;
    int count = 0;

    for (i = 0; p[i] && p[i] != ' ' && p[i] != '\t' && p[i] != ',' && p[i] != '\n'; i++) {
        count++; /* we count how many characters the first word have */
    }

    for (i = 0; i < NUM_FUNC; i++) { /* we compare the first word with each of the command names */
        if (strlen(commandNames[i]) == count && !strncmp(commandNames[i], p, count)) /* equals */
            return i;
    }
    return -1; /* the command name is not good */

}

int setWord(char *p) {
    int i;
    for (i = 0; i < NUM_SET; i++) { /* we compare the first set with each of the set names */
        if (strncmp(setNames[i], p, 4)==0) /* equals */
            return i;
    }
    return -1; /* the set name is not good */

}

char *skipSpacesAndTabs(char *s) {
    int n;
    for (n = 0; s[n] != 0 && (s[n] == ' ' || s[n] == '\t'); n++) {} /* Count how many spaces there are at the beginning */
    return s + n;
}


set *whichSet(int x) {
    /* returning a pointer to the set with the same num as the int */
    if (x == 0)
        return &setA;
    if (x == 1)
        return &setB;
    if (x == 2)
        return &setC;
    if (x == 3)
        return &setD;
    if (x == 4)
        return &setE;
    if (x == 5)
        return &setF;

    return NULL; /* never reaches here */
}


int isSet(int x) {
    return x >= 0 && x <= 6; /* set name in only SETA,SETB,SETC,SETD,SETE,SETF */
}

/* Function to remove all spaces from a given string */
void removeSpaces(char *str) {
    int i;
    /* To keep track of non-space character count */
    int count = 0;

    /* Traverse the given string. If current character
     is not space, then place it at index 'count++' */
    for (i = 0; str[i]; i++) {
        if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
            str[count++] = str[i]; /* here count is incremented */
    }

    str[count] = '\0'; /* finish the string */
}

char *skipNum(char *s) {
    int i = 0;

    for (; isdigit(s[i]); i++) {
    }
    return s + i; /* return a pointer to the char after the number */

}



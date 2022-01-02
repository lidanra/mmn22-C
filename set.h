
#include <stdio.h>

/* the set number struct */
typedef struct set {
    unsigned int  bits[4];
} set;


/*A function that places values in a set variable*/
void read_set(set* a,unsigned int []);

/*A function that prints a set */
void print_set(set *a);

/*A function that receives two sets as parameters, union them and pass the result attoset c*/
void union_set(set* a, set* b, set* c);

/*A function that receives two sets as parameters, intersect them and pass the result to set c*/
void intersect_set(set* a, set* b, set* c);

/*A function that receives two sets as parameters, sub them and pass the result to set c*/
void sub_set(set* a, set* b, set* c);

/*A function that receives two sets as parameters, symdiff them and pass the result to set c*/
void symdiff_set(set* a, set* b, set* c);




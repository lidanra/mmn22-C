
#include "set.h"
#include <stdlib.h> /* for atof */

void read_set(set *a,unsigned int num[]) {
    int i =0;

    for (;i<4;i++)
    {
        a->bits[i] = num[i];
    }
}


void print_set(set *a) {
    int i = 0;
    int j = 0;
    unsigned int flag = 1;

    for(; i<4; i++)
    {
        for (; j<32; j++)
        {
            if((a->bits[i]) & flag)
            {

                printf("%d ",(i*32)+j);  /* print the number of each bit*/
            }
            flag = flag << 1;
        }
        j=0;
        flag = 1;
    }
    printf("\n");
}


void union_set(set *a, set *b,set *c) {
    unsigned int tmp[] = {0,0,0,0};
    int i = 0;
    for (; i<4; i++)
    {
        tmp[i] = a->bits[i] | b->bits[i];
    }

    read_set(c, tmp);
}


void intersect_set(set *a, set *b,set *c) {
    unsigned int tmp[] = {0,0,0,0};
    int i = 0;

    for (; i<4; i++)
    {
        tmp[i] = a->bits[i] & b->bits[i];
    }

    read_set(c, tmp);

}


void sub_set(set *a, set *b,set *c) {
    unsigned int tmp[] = {0,0,0,0};
    int i = 0;

    for (; i<4; i++)
    {
        tmp[i] = a->bits[i] & ~(b->bits[i]);
    }

    read_set(c, tmp);
}


void symdiff_set(set *a, set *b,set *c) {
    unsigned int tmp[] = {0,0,0,0};
    int i = 0;

    for (; i<4; i++)
    {
        tmp[i] = a->bits[i] ^ (b->bits[i]);
    }

    read_set(c, tmp);
}



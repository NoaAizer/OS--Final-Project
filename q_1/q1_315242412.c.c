#define _BSD_SOURCE
#include <stdio.h>
#include <stdlib.h>

char globBuf[65536];            /* 1. Uninitialized data segment (bss) */
int primes[] = { 2, 3, 5, 7 };  /* 2. Initialized data segment  */

static int
square(int x)                   /* 3. Text Segment*/
{
    int result;                 /* 4. Stack frame for square() */

    result = x * x;
    return result;              /* 5. Passed via register */
}

static void
doCalc(int val)                 /* 6. Text Segment */
{
    printf("The square of %d is %d\n", val, square(val));

    if (val < 1000) {
        int t;                  /* 7. Stack frame for doCalc() */

        t = val * val * val;
        printf("The cube of %d is %d\n", val, t);
    }
}

int
main(int argc, char* argv[])    /* Text Segment*/
{
    static int key = 9973;      /* Initialized data segment  */
    static char mbuf[10240000]; /* Uninitialized data segment (bss) */
    char* p;                    /* Stack frame for main() */


    doCalc(key);

    exit(EXIT_SUCCESS);
}
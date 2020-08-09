#define _BSD_SOURCE
#include <stdio.h>
#include <stdlib.h>

char globBuf[65536];            /* 1. Where is allocated? */
int primes[] = { 2, 3, 5, 7 };  /* 2. Where is allocated? */

static int
square(int x)                   /* 3. Where is allocated? */
{
    int result;                 /* 4. Where is allocated? */

    result = x * x;
    return result;              /* 5. How the return value is passed? */
}

static void
doCalc(int val)                 /* 6. Where is allocated? */
{
    printf("The square of %d is %d\n", val, square(val));

    if (val < 1000) {
        int t;                  /* 7. Where is allocated? */

        t = val * val * val;
        printf("The cube of %d is %d\n", val, t);
    }
}

int
main(int argc, char* argv[])    /* Where is allocated? */
{
    static int key = 9973;      /* Where is allocated? */
    static char mbuf[10240000]; /* Where is allocated? */
    char* p;                    /* Where is allocated? */


    doCalc(key);

    exit(EXIT_SUCCESS);
}
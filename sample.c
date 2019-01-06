#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define DEBUG_MESSAGE(X) {\
    printf("=== File: \"%s\" - ", __FILE__); \
    printf("Function: \"%s\" - ", __func__); \
    printf("Line: %d\n", __LINE__); \
    printf("=== %s \n", X); \
}

int main() {

    

    return 0;
}

/******************
* 0 1 0 1 0 0 1 1 *
* 0 1 0 0 0 0 0 1 *
* 0 1 0 0 1 0 0 0 *
* 0 1 0 0 0 0 0 1 *
* 0 1 0 1 0 0 1 0 *
******************/

// (c) 2019 - Radin Shayanfar
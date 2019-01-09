#ifndef DEBUG_H
#define DEBUG_H

#define DEBUG_MESSAGE(X) {\
    printf("=== File: \"%s\" - ", __FILE__); \
    printf("Function: \"%s\" - ", __func__); \
    printf("Line: %d\n", __LINE__); \
    printf("=== %s \n", X); \
}

#endif
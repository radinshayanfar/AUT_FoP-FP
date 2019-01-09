/******************
* 0 1 0 1 0 0 1 1 *
* 0 1 0 0 0 0 0 1 *
* 0 1 0 0 1 0 0 0 *
* 0 1 0 0 0 0 0 1 *
* 0 1 0 1 0 0 1 0 *
******************/

// (c) 2019 - Radin Shayanfar

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

    char file_name[10], kkp_junk;
    printf("Enter file name to save to: ");
    scanf("%s%c", file_name, &kkp_junk);
    FILE *chp = fopen(file_name, "w");
    if (chp == NULL) {
        fprintf(stderr, "Cannot open \"%s\"\n", file_name);
        exit(0);
    }
    char inputstr[200];
    printf("Enter problem text:\n");
    fgets(inputstr, 200 - 1, stdin);
    fprintf(chp, "%s", inputstr);

    printf("Enter choice 1 text:\n");
    fgets(inputstr, 200 - 1, stdin);
    fprintf(chp, "%s", inputstr);
    printf("Enter parameters (People, Court, Treasury): ");
    for(int i = 0; i < 3; i++) {
        int t;
        scanf("%d", &t);
        fprintf(chp, "%d\n", t);
    }
    scanf("%c", &kkp_junk);

    printf("Enter choice 2 text:\n");
    fgets(inputstr, 200 - 1, stdin);
    fprintf(chp, "%s", inputstr);
    printf("Enter parameters (People, Court, Treasury): ");
    for(int i = 0; i < 3; i++) {
        int t;
        scanf("%d", &t);
        fprintf(chp, "%d\n", t);
    }

    fclose(chp);

    FILE *choices = fopen("CHOICES.txt", "a");
    fprintf(choices, "%s\n", file_name);
    fclose(choices);

    return 0;
}
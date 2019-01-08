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
#include <string.h>

#include "structures/headers/user.h"
#include "structures/headers/linked_list.h"
#include "includes/headers/list.h"

#define DEBUG_MESSAGE(X) {\
    printf("=== File: \"%s\" - ", __FILE__); \
    printf("Function: \"%s\" - ", __func__); \
    printf("Line: %d\n", __LINE__); \
    printf("=== %s \n", X); \
}

// ====================================== //

struct Problem_Node *get_random_problem(struct Problem_Node *list, int problem_list_len) {
    int random = rand() % problem_list_len;
    
    for(int i = 0; i < random; i++) {
        list = list->next;
    }
    return list;
    
}

struct Problem file_to_problem(char ch_file_name[]) {

    char address[40] = "choices/";
    strcat(address, ch_file_name);
    FILE *fp = fopen(address, "r");
    if (fp == NULL) {
        fprintf(stderr, "Cannot open \"%s\"\n", address);
        exit;
    }

    struct Problem prob;
    fgets(prob.text, 200, fp);
    fgets(prob.choice1.text, 200, fp);
    fscanf(fp, "%d%d%d", &prob.choice1.effect.people, &prob.choice1.effect.court, &prob.choice1.effect.treasury);
    fgets(prob.choice2.text, 200, fp);
    fscanf(fp, "%d%d%d", &prob.choice2.effect.people, &prob.choice2.effect.court, &prob.choice2.effect.treasury);
    prob.num = 3;

    return prob;

}

void read_problems(struct Problem_Node **list, int *problem_list_len) {

    struct Problem_Node *last_node = *list;

    FILE *choices = fopen("choices/CHOICES.txt", "r");
    if (choices == NULL) {
        fprintf(stderr, "Cannot open \"CHOICES.txt\"\n");
        exit;
    }

    *problem_list_len = 0;
    char ch_file_name[10];
    while ( (fscanf(choices, "%s", ch_file_name)) != EOF ) {
        struct Problem problem = file_to_problem(ch_file_name);

        if (last_node == NULL) {
            *list = new_node(problem);
            last_node = *list;
        } else {
            last_node->next = new_node(problem);
            last_node = last_node->next;
        }

        (*problem_list_len)++;

    }

}

void printlist(struct Problem_Node *list) {

    struct Problem_Node *current = list;
    while (current != NULL) {
        printf("%s", current->problem.text);
        current = current->next;
    }

}

int main() {

    srand(time(NULL));

    struct Problem_Node *problems_list = NULL;
    int problem_list_len;
    read_problems(&problems_list, &problem_list_len);
    // printlist(problems_list);
    printf("%s", get_random_problem(problems_list, problem_list_len)->problem.choice1.text);

    return 0;
}
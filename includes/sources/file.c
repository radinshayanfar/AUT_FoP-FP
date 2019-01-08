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
#include <string.h>

#include "../headers/file.h"
#include "../headers/list.h"
#include "../../structures/headers/state.h"
#include "../../structures/headers/linked_list.h"
#include "../../structures/headers/user.h"
#include "../../structures/headers/problem.h"

void save_to_file(struct Problem_Node *list, struct User user, enum State state) {

    FILE *fp = fopen("saves/save.sgf", "wb");

    if (fp == NULL) {
        fprintf(stderr, "Cannot open \"saves,save.sgf\"\n");
        exit;
    }

    // Writing name
    int name_len = strlen(user.name) + 1;
    fwrite(&name_len, sizeof(int), 1, fp);
    fwrite(&user.name, sizeof(char), name_len, fp);

    // Writing state
    fwrite(&state, sizeof(enum State), 1, fp);

    if (state == LOST) {
        return;
    }

    // Writing problems nodes
    while (list != NULL) {
        fwrite(list, sizeof(struct Problem_Node), 1, fp);
        list = list->next;
    }

    // Writing user parameters
    fwrite(&user.user_params, sizeof(user.user_params), 1, fp);

    // Closing file
    fclose(fp);

}

enum State restore_from_file(struct Problem_Node **list, struct User *user) {

    FILE *fp = fopen("saves/save.sgf", "rb");

    if (fp == NULL) {
        return NOT_SAVED;
    }
    
    // Reading name
    int name_len;
    fread(&name_len, sizeof(int), 1, fp);
    fread(&(user->name), name_len, 1, fp);

    // Reading state
    enum State state;
    fread(&state, sizeof(enum State), 1, fp);

    if (state == LOST) {
        return state;
    }

    // Reading problems list
    struct Problem_Node *last_node = *list, t;
    do {
        fread(&t, sizeof(struct Problem_Node), 1, fp);

        if (last_node == NULL) {
            *list = new_node(t.problem);
            last_node = *list;
        } else {
            last_node->next = new_node(t.problem);
            last_node = last_node->next;
        }

    } while (t.next != NULL);

    // Reading user parameters
    fwrite(&(user->user_params), sizeof(user->user_params), 1, fp);

    // Closing file
    fclose(fp);

    return state;

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

void read_problems(struct Problem_Node **list) {

    struct Problem_Node *last_node = *list;

    FILE *choices = fopen("choices/CHOICES.txt", "r");
    if (choices == NULL) {
        fprintf(stderr, "Cannot open \"CHOICES.txt\"\n");
        exit;
    }

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
    }

}
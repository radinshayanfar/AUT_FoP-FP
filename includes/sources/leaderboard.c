/******************
* 0 1 0 1 0 0 1 1 *
* 0 1 0 0 0 0 0 1 *
* 0 1 0 0 1 0 0 0 *
* 0 1 0 0 0 0 0 1 *
* 0 1 0 1 0 0 1 0 *
******************/

// (c) 2019 - Radin Shayanfar

#include "../headers/leaderboard.h"

int user_compare(const void *u1, const void *u2) {

    struct User user1 = *( (struct User *) u1);
    struct User user2 = *( (struct User *) u2);

    if (user1.user_params.people > user2.user_params.people) {
        return -1;
    } else if (user1.user_params.people < user2.user_params.people) {
        return 1;
    }
    if (user1.user_params.court > user2.user_params.court) {
        return -1;
    } else if (user1.user_params.court < user2.user_params.court) {
        return 1;
    }
    if (user1.user_params.treasury > user2.user_params.treasury) {
        return -1;
    } else if (user1.user_params.treasury < user2.user_params.treasury) {
        return 1;
    }

    return 0;

}

void save_to_leaderboard(struct User user) {

    FILE *fp = fopen("saves/leaderboard.sgf", "r+b");
    if (fp == NULL) {
        fp = fopen("saves/leaderboard.sgf", "w+b");
        if (fp == NULL) {
            fprintf(stderr, "Cannot open \"saves/leaderboard.sgf\"\n");
            return;
        }
    }

    int i = 0, min_index = -1;
    struct User t, min;
    min.user_params.people = 100 + 1;
    while ( fread(&t, sizeof(struct User), 1, fp) == 1 ) {
        if (user_compare(&min, &t) <= 0) {
            min = t;
            min_index = i;
        }
        i++;
    }

    if (i < LEADERBOARD_SIZE) {
        fseek(fp, 0, SEEK_END);
        fwrite(&user, sizeof(struct User), 1, fp);
    } else if (user_compare(&min, &user) == 1) {
        fseek(fp, sizeof(struct User) * min_index, SEEK_SET);
        fwrite(&user, sizeof(struct User), 1, fp);
    }

    fclose(fp);

}

void print_leaderboard() {

    FILE *fp = fopen("saves/leaderboard.sgf", "rb");
    if (fp == NULL) {
        fprintf(stderr, "Nothing saved at \"saves/leaderboard.sgf\"\n");
        return;
    }

    int count = 0;
    struct User t, leaderboard[LEADERBOARD_SIZE];
    while ( fread(&t, sizeof(struct User), 1, fp) == 1 ) {
        leaderboard[count] = t;
        count++;
    }

    qsort(leaderboard, count, sizeof(struct User), user_compare);

    printf("%-20s| %-10s| %-10s| %-10s\n", "User Name", "People", "Court", "Treasury");
    for (int i = 0; i < 55; i++) printf("-"); printf("\n");
    for (int i = 0; i < count; i++) {
        printf("%-20s| %-10d| %-10d| %-10d\n", leaderboard[i].name, leaderboard[i].user_params.people, leaderboard[i].user_params.court, leaderboard[i].user_params.treasury);
    }
    for (int i = 0; i < 55; i++) printf("-"); printf("\n");

}
/******************
* 0 1 0 1 0 0 1 1 *
* 0 1 0 0 0 0 0 1 *
* 0 1 0 0 1 0 0 0 *
* 0 1 0 0 0 0 0 1 *
* 0 1 0 1 0 0 1 0 *
******************/

// (c) 2019 - Radin Shayanfar

#include "../headers/parameters.h"

struct Parameters Parameters_Parameters(int people, int court, int treasury) {
    struct Parameters params;
    params.people = people;
    params.court = court;
    params.treasury = treasury;

    return params;
}

void Parameters_change_people(struct Parameters *param, int change) {
    param->people += change;
    if (param->people < 0) {
        param->people = 0;
    }
    if (param->people > 100) {
        param->people = 100;
    }
}

void Parameters_change_court(struct Parameters *param, int change) {
    param->court += change;
    if (param->court < 0) {
        param->court = 0;
    }
    if (param->court > 100) {
        param->court = 100;
    }
}

void Parameters_change_treasury(struct Parameters *param, int change) {
    param->treasury += change;
    if (param->treasury < 0) {
        param->treasury = 0;
    }
    if (param->treasury > 100) {
        param->treasury = 100;
    }
}
float Parameters_get_average(struct Parameters param) {

    return (param.people + param.court + param.treasury) / 3.0;

}

void Parameters_print_all_params(struct Parameters param) {
    printf("People: %d, Court: %d, Treasury: %d\n", param.people, param.court, param.treasury);
}
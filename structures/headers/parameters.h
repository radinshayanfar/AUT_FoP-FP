/******************
* 0 1 0 1 0 0 1 1 *
* 0 1 0 0 0 0 0 1 *
* 0 1 0 0 1 0 0 0 *
* 0 1 0 0 0 0 0 1 *
* 0 1 0 1 0 0 1 0 *
******************/

// (c) 2019 - Radin Shayanfar

#include <stdio.h>
#include <string.h>

#include "../../includes/debug.h"

#ifndef PARAMETERS_H
#define PARAMETERS_H

struct Parameters {
    int people, court, treasury;
};

struct Parameters Parameters_Parameters(int people, int court, int treasury);
void Parameters_change_people(struct Parameters *param, int change);
void Parameters_change_court(struct Parameters *param, int change);
void Parameters_change_treasury(struct Parameters *param, int change);
float Parameters_get_average(struct Parameters param);
void Parameters_print_all_params(struct Parameters param);

#endif
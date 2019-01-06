/******************
* 0 1 0 1 0 0 1 1 *
* 0 1 0 0 0 0 0 1 *
* 0 1 0 0 1 0 0 0 *
* 0 1 0 0 0 0 0 1 *
* 0 1 0 1 0 0 1 0 *
******************/

// (c) 2019 - Radin Shayanfar

#include <string.h>
#include "../headers/parameters.h"

struct Parameters parameters(int people, int court, int treasury) {
    struct Parameters params;
    params.people = people;
    params.court = court;
    params.treasury = treasury;

    return params;
}
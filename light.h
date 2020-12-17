#ifndef TEST_LIGHT_H
#define TEST_LIGHT_H

#include "obj.h"

// light object
typedef struct LIGHT{
    VEC_T loc;
} LIGHT_T;

COLOR_T illuminate (RAY_T ray, LIGHT_T light, OBJ_T *list, OBJ_T *curr_obj, VEC_T int_pt, VEC_T normal);

static int shadow_test (LIGHT_T light, OBJ_T *list, OBJ_T *curr_obj, VEC_T int_pt);

#endif

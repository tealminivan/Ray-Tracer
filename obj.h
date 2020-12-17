#ifndef OBJ_H
#define OBJ_H

#include "sphere.h"

// object that has fields for sphere and color
typedef struct OBJ{
    SPHERE_T sphere;
    COLOR_T color;
    struct OBJ *next;
} OBJ_T;

#endif

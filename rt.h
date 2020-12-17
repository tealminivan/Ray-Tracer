#ifndef RC_H
#define RC_H

#include "vec.h"

// ray object
typedef struct RAY{
    VEC_T origin;
    VEC_T direction;
} RAY_T;

// color object
typedef struct COLOR{
    double r;
    double g;
    double b;
} COLOR_T;



#endif

#ifndef VEC_H
#define VEC_H

// vector object
typedef struct VEC{
    double x, y, z;
        }VEC_T;

// declare function, to be defined
VEC_T normalize (VEC_T v);

// declare function to be defined
double dot (VEC_T v1, VEC_T v2);

#endif

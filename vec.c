#include "vec.h"
#include <math.h>

// definition for normalize vector function
VEC_T normalize (VEC_T v){

    double mg = sqrt(v.x*v.x + v.y*v.y + v.z*v.z );
    v.x = v.x/mg;
    v.y = v.y/mg;
    v.z = v.z/mg;

    return v;

}


// definition for dot product
double dot (VEC_T v1, VEC_T v2){

    double dotprod;
    dotprod = (v1.x*v2.x)+(v1.y*v2.y)+(v1.z*v2.z);

    return dotprod;
}

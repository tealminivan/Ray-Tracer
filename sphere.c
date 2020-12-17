#include "sphere.h"
#include <math.h>

int intersect_sphere (RAY_T ray, SPHERE_T sphere, double *t, VEC_T *int_pt, VEC_T *normal){

    // variables
    VEC_T o = ray.origin;
    VEC_T d = ray.direction;
    VEC_T s = sphere.center;
    double r = sphere.radius;

    // get vector for origin - center
    VEC_T oc;
    oc.x = o.x - s.x;
    oc.y = o.y - s.y;
    oc.z = o.z - s.z;

    double a = dot(d,d);
    double b = 2.0 * (dot(oc,d));
    double c = (dot(oc,oc)) - (r*r);
    double discrim = b*b - 4*a*c;

    if (discrim < 0){
        return 0;
    }

    discrim = sqrt(discrim);
    double t1= (-b - discrim)/(2.0*a);
    double t2= (-b + discrim)/(2.0*a);

    if ((t1<0)&&(t2<0)){
        return 0;
    }

    // get only the first intersection
    if (t1 < t2){
        *t = t1;
    }
    else{
        *t = t2;
    }

    // calculate intersection point
    int_pt->x = o.x + (d.x * (*t));
    int_pt->y = o.y + (d.y * (*t));
    int_pt->z = o.z + (d.z * (*t));

    // calculate normal
    normal->x = (int_pt->x-s.x)/r;
    normal->y = (int_pt->y-s.y)/r;
    normal->z = (int_pt->z-s.z)/r;

    return 1;
}
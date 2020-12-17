#include "light.h"
#include <math.h>
#include <stdio.h>

COLOR_T illuminate (RAY_T ray, LIGHT_T light, OBJ_T *list, OBJ_T *curr_obj, VEC_T int_pt, VEC_T normal){

    VEC_T L;
    VEC_T R;
    COLOR_T color;
    double dp;
    double dp2;

    // ambient
    color.r = 0.1 * curr_obj->color.r;
    color.g = 0.1 * curr_obj->color.g;
    color.b = 0.1 * curr_obj->color.b;

    if (!shadow_test(light,list,curr_obj,int_pt)){
        // diffuse
        L.x=light.loc.x-int_pt.x;
        L.y=light.loc.y-int_pt.y;
        L.z=light.loc.z-int_pt.z;
        L = normalize(L);
        dp = dot(L,normal);
        if (dp>0){
            // add in diffuse
            color.r += dp * curr_obj->color.r;
            color.g += dp * curr_obj->color.g;
            color.b += dp * curr_obj->color.b;
            // specular
            R.x=L.x-normal.x*2*dp;
            R.y=L.y-normal.y*2*dp;
            R.z=L.z-normal.z*2*dp;
            R = normalize(R);
            dp2 = dot(R,ray.direction);
            if (dp2>0){
                // add in specular
                color.r += pow(dp2,200);
                color.g += pow(dp2,200);
                color.b += pow(dp2,200);
            }
        }
    }
    return color;
}


static int shadow_test (LIGHT_T light, OBJ_T *list, OBJ_T *curr_obj, VEC_T int_pt){

    OBJ_T *curr;
    RAY_T light_ray;
    double dummy_t;
    VEC_T dummy_n;

    //compute light ray
    light_ray.origin.x =int_pt.x;
    light_ray.origin.y =int_pt.y;
    light_ray.origin.z =int_pt.z;

    light_ray.direction.x = light.loc.x - int_pt.x;
    light_ray.direction.y = light.loc.y - int_pt.y;
    light_ray.direction.z = light.loc.z - int_pt.z;

    light_ray.direction = normalize(light_ray.direction);

    for (curr=list;curr!=NULL;curr=curr->next){
        if(curr != curr_obj){
            if(intersect_sphere(light_ray,curr->sphere,&dummy_t,&int_pt,&dummy_n)){
                return 1;
            }
        }
    }

    return 0;

}
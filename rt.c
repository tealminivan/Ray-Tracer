#include "rt.h"
#include "vec.h"
#include "obj.h"
#include "light.h"
#include "sphere.h"
#include <stdio.h>
#include <stdlib.h>


void read_objs (OBJ_T **list){

    // variables
    double x,y,z,radius,r,g,b;

    // initialize the linked list
    OBJ_T *node = NULL;
    *list = NULL;

    // scan spheres and add to linked list
    while(scanf("%lf %lf %lf %lf %lf %lf %lf", &x,&y,&z,&radius,&r,&g,&b)==7){
        // allocate memory for the nodes
        node = (struct OBJ*)malloc(sizeof(struct OBJ));

        node->sphere.center.x=x;
        node->sphere.center.y=y;
        node->sphere.center.z=z;
        node->sphere.radius=radius;
        node->color.r=r;
        node->color.g=g;
        node->color.b=b;

        // move to the next node
        node->next = *list;
        *list = node;
    }
}


COLOR_T trace (RAY_T ray, OBJ_T *list, LIGHT_T light){

    COLOR_T color;
    OBJ_T *obj;
    VEC_T int_pt;
    VEC_T normal;

    OBJ_T *closest_obj=NULL;
    VEC_T closest_int_pt;
    VEC_T closest_normal;

    double min_t = 10000;
    double t;

    color.r = 0;
    color.g = 0;
    color.b = 0;

    // go through all the spheres in the linked list
    for (obj=list; obj!=NULL;obj=obj->next){
        if(intersect_sphere(ray,obj->sphere,&t,&int_pt,&normal)){
            if(t<min_t){
                closest_obj = obj;
                closest_int_pt = int_pt;
                closest_normal = normal;
                min_t = t;
            }
        }
    }

    if (closest_obj!= NULL){
        color = illuminate(ray,light,list,closest_obj,closest_int_pt,closest_normal);
    }
    return color;
}


int main() {

    // initialize light location
    LIGHT_T light;
    light.loc.x=5;
    light.loc.y=10;
    light.loc.z=0;

    // create linked list object
    OBJ_T *list;
    // temp variable for linked list
    OBJ_T *obj;

    read_objs(&list);

    RAY_T ray;
    COLOR_T color;

    int width = 1000;
    int height = 1000;
    int y;
    int x;

    // ppm header
    printf("P6\n");
    printf("%d %d\n",width, height);
    printf("255\n");

    // loop through the pixels
    for (y=0; y<height; ++y){
        for (x=0; x<width; ++x){

            ray.origin.x=0;
            ray.origin.y=0;
            ray.origin.z=0;

            ray.direction.x = -.5 + ((float)x /1000);
            ray.direction.y = .5 - ((float)y /1000);
            ray.direction.z = 1;

            ray.direction = normalize(ray.direction);

            color = trace(ray, list, light);

            // cap color
            color.r = (color.r > 1) ? 1 : (color.r < 0) ? 0 : color.r;
            color.g = (color.g > 1) ? 1 : (color.g < 0) ? 0 : color.g;
            color.b = (color.b > 1) ? 1 : (color.b < 0) ? 0 : color.b;

            // print pixel color
            printf("%c%c%c", (unsigned int)(color.r * 255), (unsigned int)(color.g * 255), (unsigned int)(color.b * 255));
        }
    }

    // free up the linked list
    for (obj=list; obj!=NULL;obj=obj->next){
        free(obj);
    }
    return 0;
}
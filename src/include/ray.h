#ifndef RAY_H
#define RAY_H

#include "vec3.h"

typedef struct {
    const point3 origin;
    const vec3 direction;
} ray;

static inline point3 ray_origin(ray r) {
    return r.origin;
} 

static inline vec3 ray_direction(ray r) {
    return r.direction;
}

static inline point3 ray_at(ray r, double t) {
    return vec3_add(r.origin, vec3_mul_scalar(r.direction, t));
}

#endif

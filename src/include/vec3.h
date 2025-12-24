#ifndef VEC3_H
#define VEC3_H

#include <math.h>
#include <stdio.h>

typedef struct vec3 {
    double e[3];
} vec3;

typedef vec3 point3;

static inline vec3 vec3_new(double e0, double e1, double e2) {
    vec3 v;
    v.e[0] = e0;
    v.e[1] = e1;
    v.e[2] = e2;
    return v;
}

static inline double vec3_x(vec3 v) { return v.e[0]; }
static inline double vec3_y(vec3 v) { return v.e[1]; }
static inline double vec3_z(vec3 v) { return v.e[2]; }

static inline vec3 vec3_negate(vec3 v) {
    return vec3_new(-v.e[0], -v.e[1], -v.e[2]);
}

static inline double vec3_length_squared(vec3 v) {
    return v.e[0]*v.e[0] + v.e[1]*v.e[1] + v.e[2]*v.e[2];
}

static inline double vec3_length(vec3 v) {
    return sqrt(vec3_length_squared(v));
}

static inline vec3 vec3_add(vec3 u, vec3 v) {
    return vec3_new(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

static inline vec3 vec3_sub(vec3 u, vec3 v) {
    return vec3_new(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

static inline vec3 vec3_mul(vec3 u, vec3 v) {
    return vec3_new(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

static inline vec3 vec3_mul_scalar(vec3 v, double t) {
    return vec3_new(v.e[0] * t, v.e[1] * t, v.e[2] * t);
}

static inline vec3 vec3_div_scalar(vec3 v, double t) {
    return vec3_mul_scalar(v, 1.0/t);
}

static inline double vec3_dot(vec3 u, vec3 v) {
    return u.e[0] * v.e[0] + u.e[1] * v.e[1] + u.e[2] * v.e[2];
}

static inline vec3 vec3_cross(vec3 u, vec3 v) {
    return vec3_new(
        u.e[1] * v.e[2] - u.e[2] * v.e[1],
        u.e[2] * v.e[0] - u.e[0] * v.e[2],
        u.e[0] * v.e[1] - u.e[1] * v.e[0]
    );
}

static inline vec3 vec3_unit_vector(vec3 v) {
    return vec3_div_scalar(v, vec3_length(v));
}

static inline void vec3_print(vec3 v) {
    printf("%f %f %f", v.e[0], v.e[1], v.e[2]);
}

#endif

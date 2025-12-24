#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"
#include <stdio.h>

typedef vec3 color;

void write_color(const color pixel_color) {
    double r = vec3_x(pixel_color);
    double g = vec3_y(pixel_color);
    double b = vec3_z(pixel_color);

    int r_byte = (int) 255.999 * r;
    int g_byte = (int) 255.999 * g;
    int b_byte = (int) 255.999 * b;

    printf("%d %d %d\n", r_byte, g_byte, b_byte);
}

#endif

#include <stdio.h>
#include "color.h"
#include "include/ray.h"
#include "include/vec3.h"
#include "vec3.h"
#include "ray.h"

bool hit_sphere(const point3 center, double radius, const ray r) {
    vec3 oc = vec3_sub(center, ray_origin(r));
    double a = vec3_dot(ray_direction(r), ray_direction(r));
    double b = -2.0 * vec3_dot(ray_direction(r), oc);
    double c = vec3_dot(oc, oc) - radius * radius;
    double delta  = b*b - 4*a*c;
    return delta >= 0;
}

color ray_color(const ray r) {
    point3 temp_p3 = { {0,0,-1} };
    if (hit_sphere(temp_p3, 0.5, r)) {
        color ret = { {1, 0, 0} };
        return ret;
    }

    vec3 unit_direction = vec3_unit_vector(ray_direction(r));
    double a = 0.5 * vec3_y(unit_direction) + 1.0;
    color temp1 = { {1.0, 1.0, 1.0} };
    color temp2 = { {0.5, 0.7, 1.0} };
    return vec3_add(vec3_mul_scalar(temp1, (1.0-a)), vec3_mul_scalar(temp2, a));
}

int main() {
    double aspect_ratio = 16.0 / 9.0;

    int img_width = 400;
    int img_height = (int) img_width / aspect_ratio;
    img_height = (img_height < 1) ? 1 : img_height;
    
    double focal_lenght = 1.0;
    double viewport_height = 2.0;
    double viewport_width = viewport_height * ((double) img_width / img_height);
    point3 camera_center = { {0,0,0} };

    vec3 viewport_u = { {viewport_width, 0, 0} }; 
    vec3 viewport_v = { {0, -viewport_height, 0} };

    vec3 pixel_delta_u = vec3_div_scalar(viewport_u, img_width);
    vec3 pixel_delta_v = vec3_div_scalar(viewport_v, img_height);

    vec3 temp = { {0, 0, focal_lenght} };
    vec3 viewport_upper_left = vec3_sub(vec3_sub(vec3_sub(camera_center, temp), vec3_div_scalar(viewport_u, 2)), vec3_div_scalar(viewport_v, 2)); 
    vec3 pixel00_loc = vec3_add(viewport_upper_left, vec3_mul_scalar(vec3_add(pixel_delta_u, pixel_delta_v), 0.5));

    printf("P3\n%d %d\n255\n", img_width, img_height);

    for (int j = 0; j < img_height; j++) {
        for (int i = 0; i < img_width; i++) {
            vec3 pixel_center = vec3_add(vec3_add(pixel00_loc, vec3_mul_scalar(pixel_delta_u, i)), vec3_mul_scalar(pixel_delta_v, j));
            vec3 ray_dir = vec3_sub(pixel_center, camera_center);
            ray r = {camera_center, ray_dir};

            color pixel_color = ray_color(r);
            write_color(pixel_color);
        }
    }

    return 0;
}

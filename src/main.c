#include <stdio.h>
#include "color.h"
#include "vec3.h"

int main() {
    int img_width = 256;
    int img_height = 256;

    printf("P3\n%d %d\n255\n", img_width, img_height);

    for (int j = 0; j < img_height; j++) {
        for (int i = 0; i < img_width; i++) {
            color pixel_color = { { (double) i / (img_width - 1),  (double) j / (img_height - 1), 0 } };
            write_color(pixel_color);
        }
    }

    return 0;
}

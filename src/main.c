#include <stdio.h>
#include <math.h>
#include "raylib.h"

#define P2 PI / 2
#define P3 3 * PI / 2
#define DR 0.0174533

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 512

int map_x = 8;
int map_y = 8;
int map_s = 64;

int map[] = {
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 1, 0, 1,
    1, 0, 1, 0, 0, 0, 0, 1,
    1, 0, 1, 0, 0, 0, 0, 1,
    1, 0, 0, 1, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 1,
    1, 1, 1, 1, 1, 1, 1, 1,
};

float player_angle = 0;
float player_x = 300;
float player_y = 300;
float player_delta_x = 0;
float player_delta_y = 0;

float dist(float ax, float ay, float bx, float by) {
    return sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay));
}

void update_player() {
    if (IsKeyDown(KEY_A)) {
        player_angle -= 0.05f;
        if (player_angle < 0) player_angle += 2 * PI;
        player_delta_x = cos(player_angle) * 3;
        player_delta_y = sin(player_angle) * 3;
    }
    if (IsKeyDown(KEY_D)) {
        player_angle += 0.05f;
        if (player_angle > 2 * PI) player_angle -= 2 * PI;
        player_delta_x = cos(player_angle) * 3;
        player_delta_y = sin(player_angle) * 3;
    }
    if (IsKeyDown(KEY_W)) {
        player_x += player_delta_x;
        player_y += player_delta_y;
    }
    if (IsKeyDown(KEY_S)) {
        player_x -= player_delta_x;
        player_y -= player_delta_y;
    }
}

void draw_rays_3d() {
    int mx, my, mp, dof;
    float rx, ry, ra, xo, yo, dis_t;

    ra = player_angle - DR * 30;
    if (ra < 0) ra += 2 * PI;
    if (ra > 2 * PI) ra -= 2 * PI;

    for (int r = 0; r < 60; r++) {
        dof = 0;
        float dis_h = 1000000;
        float hx = player_x, hy = player_y;
        float a_tan = -1 / tan(ra);

        if (ra > PI) {
            ry = (((int)player_y >> 6) << 6) - 0.0001;
            rx = (player_y - ry) * a_tan + player_x;
            yo = -64; xo = -yo * a_tan;
        } else if (ra < PI) {
            ry = (((int)player_y >> 6) << 6) + 64;
            rx = (player_y - ry) * a_tan + player_x;
            yo = 64; xo = -yo * a_tan;
        } else {
            rx = player_x; ry = player_y; dof = 8;
        }

        while (dof < 8) {
            mx = (int)(rx) >> 6; my = (int)(ry) >> 6; mp = my * map_x + mx;
            if (mp >= 0 && mp < map_x * map_y && map[mp] == 1) {
                hx = rx; hy = ry; dis_h = dist(player_x, player_y, hx, hy);
                dof = 8;
            } else {
                rx += xo; ry += yo; dof += 1;
            }
        }

        dof = 0;
        float dis_v = 1000000;
        float vx = player_x, vy = player_y;
        float n_tan = -tan(ra);

        if (ra > P2 && ra < P3) { 
            rx = (((int)player_x >> 6) << 6) - 0.0001;
            ry = (player_x - rx) * n_tan + player_y;
            xo = -64; yo = -xo * n_tan;
        } else if (ra < P2 || ra > P3) {
            rx = (((int)player_x >> 6) << 6) + 64;
            ry = (player_x - rx) * n_tan + player_y;
            xo = 64; yo = -xo * n_tan;
        } else { 
            rx = player_x; ry = player_y; dof = 8;
        }

        while (dof < 8) {
            mx = (int)(rx) >> 6; my = (int)(ry) >> 6; mp = my * map_x + mx;
            if (mp >= 0 && mp < map_x * map_y && map[mp] == 1) {
                vx = rx; vy = ry; dis_v = dist(player_x, player_y, vx, vy);
                dof = 8;
            } else {
                rx += xo; ry += yo; dof += 1;
            }
        }

        Color wallColor = GREEN;
        if (dis_v < dis_h) {
            dis_t = dis_v;
            wallColor = ColorBrightness(GREEN, -0.2f);
        } else {
            dis_t = dis_h;
        }

        float ca = player_angle - ra;
        if (ca < 0) ca += 2 * PI;
        if (ca > 2 * PI) ca -= 2 * PI;
        dis_t = dis_t * cos(ca);

        float line_h = (map_s * WINDOW_HEIGHT) / dis_t;
        if (line_h > WINDOW_HEIGHT) line_h = WINDOW_HEIGHT;
        float line_o = (WINDOW_HEIGHT / 2) - (line_h / 2);

        int strip_w = WINDOW_WIDTH / 60;
        DrawRectangle(r * strip_w, line_o, strip_w, line_h, wallColor);

        ra += DR;
        if (ra < 0) ra += 2 * PI;
        if (ra > 2 * PI) ra -= 2 * PI;
    }
}

int main() {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Netrun 3D");
    SetTargetFPS(120);

    player_delta_x = cos(player_angle) * 3;
    player_delta_y = sin(player_angle) * 3;

    while (!WindowShouldClose()) {
        update_player();

        BeginDrawing();
        ClearBackground(BLACK);

        DrawRectangle(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT / 2, DARKGRAY);
        DrawRectangle(0, WINDOW_HEIGHT / 2, WINDOW_WIDTH, WINDOW_HEIGHT / 2, BLACK);

        draw_rays_3d();

        DrawFPS(10, 10);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}

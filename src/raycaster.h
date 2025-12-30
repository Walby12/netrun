#ifndef RAYCASTER_H
#define RAYCASTER_H

#include <math.h>
#include "raylib.h"

#define P2 PI / 2.0f
#define P3 3.0f * PI / 2.0f
#define DR 0.0174533f


typedef enum GameState {
    STATE_MENU,
    STATE_LOADING,
     STATE_PLAYING
} GameState;

GameState currentState = STATE_MENU;

bool IsMouseButtonPressedOn(Rectangle rect) {
    return CheckCollisionPointRec(GetMousePosition(), rect) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
}

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
    return sqrtf((bx - ax) * (bx - ax) + (by - ay) * (by - ay));
}

void update_player() {
    float delta_time = GetFrameTime() * 50.0f;
    float rot_speed = 0.05f;
    float move_speed = 4.0f;

    if (IsKeyDown(KEY_A)) {
        player_angle -= rot_speed * delta_time;
        if (player_angle < 0) player_angle += 2 * PI;
        player_delta_x = cosf(player_angle) * move_speed;
        player_delta_y = sinf(player_angle) * move_speed;
    }
    if (IsKeyDown(KEY_D)) {
        player_angle += rot_speed * delta_time;
        if (player_angle > 2 * PI) player_angle -= 2 * PI;
        player_delta_x = cosf(player_angle) * move_speed;
        player_delta_y = sinf(player_angle) * move_speed;
    }
    if (IsKeyDown(KEY_W)) {
        player_x += player_delta_x * delta_time;
        player_y += player_delta_y * delta_time;
    }
    if (IsKeyDown(KEY_S)) {
        player_x -= player_delta_x * delta_time;
        player_y -= player_delta_y * delta_time;
    }
}

void draw_rays_3d(int w, int h) {
    int mx, my, mp, dof;
    float rx, ry, ra, xo, yo, dis_t;
    int num_rays = 120;

    ra = player_angle - DR * 30;
    if (ra < 0) ra += 2 * PI;
    if (ra > 2 * PI) ra -= 2 * PI;

    for (int r = 0; r < num_rays; r++) {
        dof = 0;
        float dis_h = 1000000, hx = player_x, hy = player_y;
        float a_tan = -1.0f / tanf(ra);

        if (ra > PI) {
            ry = (((int)player_y >> 6) << 6) - 0.0001f;
            rx = (player_y - ry) * a_tan + player_x;
            yo = -64; xo = -yo * a_tan;
        } else if (ra < PI && ra > 0) {
            ry = (((int)player_y >> 6) << 6) + 64;
            rx = (player_y - ry) * a_tan + player_x;
            yo = 64; xo = -yo * a_tan;
        } else { rx = player_x; ry = player_y; dof = 8; }

        while (dof < 8) {
            mx = (int)(rx) >> 6; my = (int)(ry) >> 6; mp = my * map_x + mx;
            if (mp >= 0 && mp < map_x * map_y && map[mp] == 1) {
                hx = rx; hy = ry; dis_h = dist(player_x, player_y, hx, hy);
                dof = 8;
            } else { rx += xo; ry += yo; dof += 1; }
        }

        dof = 0;
        float dis_v = 1000000, vx = player_x, vy = player_y;
        float n_tan = -tanf(ra);

        if (ra > P2 && ra < P3) {
            rx = (((int)player_x >> 6) << 6) - 0.0001f;
            ry = (player_x - rx) * n_tan + player_y;
            xo = -64; yo = -xo * n_tan;
        } else if (ra < P2 || ra > P3) {
            rx = (((int)player_x >> 6) << 6) + 64;
            ry = (player_x - rx) * n_tan + player_y;
            xo = 64; yo = -xo * n_tan;
        } else { rx = player_x; ry = player_y; dof = 8; }

        while (dof < 8) {
            mx = (int)(rx) >> 6; my = (int)(ry) >> 6; mp = my * map_x + mx;
            if (mp >= 0 && mp < map_x * map_y && map[mp] == 1) {
                vx = rx; vy = ry; dis_v = dist(player_x, player_y, vx, vy);
                dof = 8;
            } else { rx += xo; ry += yo; dof += 1; }
        }

        Color c = GREEN;
        if (dis_v < dis_h) { dis_t = dis_v; c = ColorBrightness(GREEN, -0.15f); }
        else { dis_t = dis_h; }

        float ca = player_angle - ra; 
        if (ca < 0) ca += 2 * PI;
        if (ca > 2 * PI) ca -= 2 * PI;
        dis_t = dis_t * cosf(ca);

        float line_h = (map_s * h) / dis_t;
        if (line_h > h) line_h = h;
        float line_o = (h / 2.0f) - (line_h / 2.0f);

        float strip_w = (float)w / num_rays;
        DrawRectangle(r * strip_w, line_o, ceilf(strip_w), line_h, c);

        ra += (DR * 60.0f / num_rays); 
        if (ra < 0) ra += 2 * PI;
        if (ra > 2 * PI) ra -= 2 * PI;
    }
}

#endif

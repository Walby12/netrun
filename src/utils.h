
#ifndef UTILS_H
#define UTILS_H

typedef struct {
    float x, y;
    float speed;
} RainDrop;

#define MAX_DROPS 100
RainDrop drops[MAX_DROPS];

void InitRain(int sw) {
    for (int i = 0; i < MAX_DROPS; i++) {
        drops[i].x = GetRandomValue(0, sw);
        drops[i].y = GetRandomValue(-sw, 0);
        drops[i].speed = GetRandomValue(200, 500);
    }
}

void DrawMatrixRain(int sw, int sh) {
    float dt = GetFrameTime();
    for (int i = 0; i < MAX_DROPS; i++) {
        drops[i].y += drops[i].speed * dt;
        
        if (drops[i].y > sh) {
            drops[i].y = -20;
            drops[i].x = GetRandomValue(0, sw);
        }

        const char* bit = (GetRandomValue(0, 1) == 0) ? "0" : "1";
        Color rainColor = (i % 2 == 0) ? DARKGREEN : GREEN;
        DrawText(bit, drops[i].x, drops[i].y, 15, rainColor);
    }
}

void DrawGlitchText(const char* text, int x, int y, int size, Color color) {
    bool glitch = GetRandomValue(0, 100) < 5;
    int offsetX = 0;
    int offsetY = 0;

    if (glitch) {
        offsetX = GetRandomValue(-4, 4);
        offsetY = GetRandomValue(-2, 2);
        DrawText(text, x + offsetX + 2, y + offsetY, size, RED);
    }

    DrawText(text, x + offsetX, y + offsetY, size, color);
}

#endif

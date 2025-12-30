#include "raylib.h"
#include "raycaster.h"
#include "utils.h"

int main() {
    SetConfigFlags(FLAG_FULLSCREEN_MODE | FLAG_WINDOW_HIGHDPI);
    InitWindow(0, 0, "netrun");
    Texture2D logo = LoadTexture("samurai_logo.png");
    
    int sw = GetScreenWidth();
    int sh = GetScreenHeight();
    
    float loadingProgress = 0.0f;
    SetTargetFPS(60);

    InitRain(sw);
    
    while (!WindowShouldClose()) {
        switch (currentState) {
            case STATE_MENU:
                Rectangle btn = { sw/2 - 100, sh/2 + 50, 200, 50 };
                if (IsMouseButtonPressedOn(btn)) {
                    currentState = STATE_LOADING;
                }
                break;

            case STATE_LOADING:
                loadingProgress += 0.8f * GetFrameTime();
                if (loadingProgress >= 1.0f) currentState = STATE_PLAYING;
                break;

            case STATE_PLAYING:
                update_player();
                break;
        }

        BeginDrawing();
        ClearBackground(BLACK);

        if (currentState == STATE_MENU) {
            DrawMatrixRain(sw, sh);
            
            DrawGlitchText("NETRUN", sw/2 - MeasureText("NETRUN", 60)/2, sh/2 - 100, 60, GREEN);
            DrawGlitchText("v0.0.1 - SECURE CONNECTION", sw/2 - 100, sh/2 - 30, 15, DARKGREEN);

            Rectangle btn = { sw/2 - 100, sh/2 + 50, 200, 50 };
            bool hovering = CheckCollisionPointRec(GetMousePosition(), btn);
                
            DrawRectangleRec(btn, hovering ? GREEN : BLACK);
            DrawRectangleLinesEx(btn, 2, GREEN);
                
            DrawText("LOAD IN", btn.x + 50, btn.y + 15, 20, hovering ? BLACK : GREEN);
                
            ShowCursor();
        } 
        else if (currentState == STATE_LOADING) {
            float scale = (sh * 0.6f) / logo.height;
            float w = logo.width * scale;
            float h = logo.height * scale;

            
            Rectangle source = { 0, 0, (float)logo.width, (float)logo.height };
            Rectangle dest = { sw/2.0f, sh/2.0f, w, h };
            Vector2 origin = { w/2.0f, h/2.0f };

            DrawTexturePro(logo, source, dest, origin, 0.0f, Fade(RED, 0.2f));            

            DrawText("CONNECTING TO THE NET...", sw/2 - 150, sh/2 - 20, 20, GREEN);
            DrawRectangle(sw/2 - 150, sh/2 + 20, 300 * loadingProgress, 5, GREEN);
            HideCursor();
        } 
        else if (currentState == STATE_PLAYING) {
            draw_rays_3d(sw, sh);
        }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}

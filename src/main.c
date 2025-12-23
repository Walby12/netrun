#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

void render(Rectangle *render_rect, bool *show_render) {
    if (*show_render) {
        if (GuiWindowBox(*render_rect, "RENDER OUTPUT")) {
            *show_render = false;
        }
        
        Rectangle content = { 
            render_rect->x + 1, 
            render_rect->y + 25, 
            render_rect->width - 2, 
            render_rect->height - 26 
        };
        
        for (int y = content.y; y < content.y + content.height; y++) {
            for (int x = content.x; x < content.x + content.width; x++) {
                Color random_color = (Color){
                    GetRandomValue(0, 255),
                    GetRandomValue(0, 255),
                    GetRandomValue(0, 255),
                    255
                };
                DrawPixel(x, y, random_color);
            }
        }
    }
}

int main(void) {
    InitWindow(800, 800, "Netrun");
    SetTargetFPS(60);
    
    Rectangle menu_rect = { 50, 50, 250, 400 };
    Vector2 drag_offset = { 0 };
    bool is_dragging = false;
    
    Rectangle render_rect = { 350, 50, 400, 400 };
    bool show_render = false;
    
    GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt(LIME));
    GuiSetStyle(DEFAULT, TEXT_COLOR_FOCUSED, ColorToInt(GREEN));
    GuiSetStyle(DEFAULT, TEXT_COLOR_PRESSED, ColorToInt(DARKGREEN));
    
    GuiSetStyle(DEFAULT, BORDER_COLOR_NORMAL, ColorToInt(LIME));
    GuiSetStyle(DEFAULT, BASE_COLOR_NORMAL, ColorToInt(BLACK));
    
    GuiSetStyle(BUTTON, BORDER_COLOR_NORMAL, ColorToInt(LIME));
    GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, ColorToInt(BLACK));
    GuiSetStyle(BUTTON, TEXT_COLOR_NORMAL, ColorToInt(LIME));
    GuiSetStyle(BUTTON, BORDER_COLOR_FOCUSED, ColorToInt(GREEN));
    GuiSetStyle(BUTTON, BASE_COLOR_FOCUSED, ColorToInt((Color){0, 50, 0, 255}));
    GuiSetStyle(BUTTON, TEXT_COLOR_FOCUSED, ColorToInt(LIME));
    GuiSetStyle(BUTTON, BORDER_COLOR_PRESSED, ColorToInt(DARKGREEN));
    GuiSetStyle(BUTTON, BASE_COLOR_PRESSED, ColorToInt((Color){0, 80, 0, 255}));
    GuiSetStyle(BUTTON, TEXT_COLOR_PRESSED, ColorToInt(LIME));
    GuiSetStyle(BUTTON, BORDER_WIDTH, 1);
    
    GuiSetStyle(DEFAULT, BACKGROUND_COLOR, ColorToInt(BLACK));
    
    while (!WindowShouldClose()) {
        Vector2 mouse = GetMousePosition();
        
        Rectangle title_bar = { menu_rect.x, menu_rect.y, menu_rect.width, 24 };
        
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mouse, title_bar)) {
            is_dragging = true;
            drag_offset = (Vector2){ mouse.x - menu_rect.x, mouse.y - menu_rect.y };
        }
        
        if (is_dragging) {
            menu_rect.x = mouse.x - drag_offset.x;
            menu_rect.y = mouse.y - drag_offset.y;
            if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
                is_dragging = false;
            }
        }
        
        BeginDrawing();
        ClearBackground(BLACK);
            
        if (GuiWindowBox(menu_rect, "NETRUN v0.0.1")) {}
            
        if (GuiButton((Rectangle){ menu_rect.x + 50, menu_rect.y + 60, 150, 30 }, "INITIALIZE RENDER")) {
            show_render = true;
        }
            
        GuiLabel((Rectangle){ menu_rect.x + 50, menu_rect.y + 360, 150, 20 }, "[STATUS: ONLINE]");
            
        render(&render_rect, &show_render);
            
        EndDrawing();
    }
    
    CloseWindow();
    return 0;
}

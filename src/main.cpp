#include <raylib.h>
#include <string>
#include <cmath>
#include <iostream>

struct Entity {
    Vector2 pos;
    Vector2 size;
    Vector2 speed;
    void display() {
        DrawRectangleV(pos, size, BLACK);
    }
};

int
main()
{
    const int width = 1280;
    const int height = 720;
    const std::string title = "my game";

    auto player = new Entity;

    player->pos = {
        .x = static_cast<float>(width) / 2.0f,
        .y = static_cast<float>(height) / 2.0f
    };

    player->size = {
        .x = 10.0f,
        .y = 10.0f
    };

    player->speed = {
        .x = 4.0f,
        .y = 4.0f
    };

    InitWindow(width, height, title.c_str());

    SetExitKey(KEY_NULL);

    const int pause_font_size = 96;
    const int pause_font_spacing = 2;
    const Font pause_font = LoadFontEx("resources/fonts/Montserrat/static/Montserrat-Regular.ttf", pause_font_size, 0, 0);

    const int debug_font_size = 16;
    const int debug_font_spacing = 2;
    const Font debug_font = LoadFontEx("resources/fonts/Montserrat/static/Montserrat-Regular.ttf", debug_font_size, 0, 0);

    SetTargetFPS(100);

    bool pause = false;
    bool debug = false;
    bool vsync = true;

    const std::string pause_text = "Game is paused";

    Vector2 pos_x_display_size;
    Vector2 pos_y_display_size;
    int fps;

    std::string pos_x_display;
    std::string pos_y_display;
    std::string fps_display;

    while (!WindowShouldClose()) {
        if (vsync && !IsWindowState(FLAG_VSYNC_HINT)) {
            SetWindowState(FLAG_VSYNC_HINT);
        } else if (!vsync && IsWindowState(FLAG_VSYNC_HINT)) {
            ClearWindowState(FLAG_VSYNC_HINT);
        }

        if (!pause) {
            if (IsKeyDown(KEY_UP)) {
                player->pos.y = std::fmod(height + player->pos.y - player->speed.y, height);
            }

            if (IsKeyDown(KEY_DOWN)) {
                player->pos.y = std::fmod(height + player->pos.y + player->speed.y, height);
            }

            if (IsKeyDown(KEY_LEFT)) {
                player->pos.x = std::fmod(width + player->pos.x - player->speed.x, width);
            }

            if (IsKeyDown(KEY_RIGHT)) {
                player->pos.x = std::fmod(width + player->pos.x + player->speed.x, width);
            }
        }

        BeginDrawing();

        ClearBackground(WHITE);

        player->display();

        if (IsKeyPressed(KEY_D) && pause == false) {
            debug = !debug;
        }

        if (IsKeyPressed(KEY_P) && debug == false) {
            pause = !pause;
        }

        if (pause) {
            DrawTextEx(
                pause_font,
                pause_text.c_str(),
                (Vector2){ 0, 0 },
                pause_font_size,
                pause_font_spacing,
                BLACK);
        }

        if (debug) {
            fps = GetFPS();

            pos_x_display = "pos.x = " + std::to_string(player->pos.x);
            pos_y_display = "pos.y = " + std::to_string(player->pos.y);
            fps_display = "fps = " + std::to_string(fps);

            pos_x_display_size = MeasureTextEx(
                debug_font,
                pos_x_display.c_str(),
                debug_font_size,
                debug_font_spacing);

            pos_y_display_size = MeasureTextEx(
                debug_font,
                pos_y_display.c_str(),
                debug_font_size,
                debug_font_spacing);

            DrawTextEx(
                debug_font,
                pos_x_display.c_str(),
                (Vector2){ 0, 0 },
                debug_font_size,
                debug_font_spacing,
                BLACK);

            DrawTextEx(
                debug_font,
                pos_y_display.c_str(),
                (Vector2){ 0, pos_x_display_size.y + 1 },
                debug_font_size,
                debug_font_spacing,
                BLACK);

            DrawTextEx(
                debug_font,
                fps_display.c_str(),
                (Vector2){ 0, pos_x_display_size.y + pos_y_display_size.y + 1 },
                debug_font_size,
                debug_font_spacing,
                BLACK);
        }

        EndDrawing();
    }

    UnloadFont(pause_font);
    UnloadFont(debug_font);

    CloseWindow();

    delete player;

    return 0;
}

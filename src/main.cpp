#include <raylib.h>
#include <string>
#include <cmath>

struct Entity {
    Vector2 pos;
    Vector2 size;
    Vector2 speed;
    Color color;
    void display() {
        DrawRectangleV(pos, size, color);
    }
};

int
main()
{
    const int width = 1280;
    const int height = 720;
    const std::string title = "my game";

    auto player1 = new Entity;
    auto player2 = new Entity;

    player1->pos = {
            .x = static_cast<float>(width) / 3.0f,
            .y = static_cast<float>(height) / 2.0f
    };
    player2->pos = {
            .x = static_cast<float>(width) / 3.0f * 2,
            .y = static_cast<float>(height) / 2.0f
    };

    player1->size = {
            .x = 10.0f,
            .y = 10.0f
    };

    player1->speed = {
            .x = 4.0f,
            .y = 4.0f
    };

    player2->size = {
            .x = 10.0f,
            .y = 10.0f
    };

    player2->speed = {
            .x = 4.0f,
            .y = 4.0f
    };

    player1->color = {255,0,0, 255};

    player2->color = {0,255,0, 255};

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

    Vector2 pos1_x_display_size;
    Vector2 pos1_y_display_size;
    int fps;

    std::string pos1_x_display;
    std::string pos1_y_display;
    std::string pos2_x_display;
    std::string pos2_y_display;
    std::string fps_display;

    while (!WindowShouldClose()) {
        if (vsync && !IsWindowState(FLAG_VSYNC_HINT)) {
            SetWindowState(FLAG_VSYNC_HINT);
        } else if (!vsync && IsWindowState(FLAG_VSYNC_HINT)) {
            ClearWindowState(FLAG_VSYNC_HINT);
        }

        if (!pause) {
            if (IsKeyDown(KEY_W)) {
                player1->pos.y = std::fmod(height + player1->pos.y - player1->speed.y, height);
            }

            if (IsKeyDown(KEY_S)) {
                player1->pos.y = std::fmod(height + player1->pos.y + player1->speed.y, height);
            }

            if (IsKeyDown(KEY_A)) {
                player1->pos.x = std::fmod(width + player1->pos.x - player1->speed.x, width);
            }

            if (IsKeyDown(KEY_D)) {
                player1->pos.x = std::fmod(width + player1->pos.x + player1->speed.x, width);
            }

            if (IsKeyDown(KEY_UP)) {
                player2->pos.y = std::fmod(height + player2->pos.y - player2->speed.y, height);
            }

            if (IsKeyDown(KEY_DOWN)) {
                player2->pos.y = std::fmod(height + player2->pos.y + player2->speed.y, height);
            }

            if (IsKeyDown(KEY_LEFT)) {
                player2->pos.x = std::fmod(width + player2->pos.x - player2->speed.x, width);
            }

            if (IsKeyDown(KEY_RIGHT)) {
                player2->pos.x = std::fmod(width + player2->pos.x + player2->speed.x, width);
            }
        }

        BeginDrawing();

        ClearBackground(WHITE);

        player1->display();
        player2->display();

        if (IsKeyPressed(KEY_Q) && pause == false) {
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

            pos1_x_display = "pos.x = " + std::to_string(player1->pos.x);
            pos1_y_display = "pos.y = " + std::to_string(player1->pos.y);

            pos2_x_display = "pos.x = " + std::to_string(player1->pos.x);
            pos2_y_display = "pos.y = " + std::to_string(player1->pos.y);

            fps_display = "fps = " + std::to_string(fps);

            pos1_x_display_size = MeasureTextEx(
                    debug_font,
                    pos1_x_display.c_str(),
                    debug_font_size,
                    debug_font_spacing);

            pos1_y_display_size = MeasureTextEx(
                    debug_font,
                    pos1_y_display.c_str(),
                    debug_font_size,
                    debug_font_spacing);

            DrawTextEx(
                    debug_font,
                    pos1_x_display.c_str(),
                    (Vector2){ 0, 0 },
                    debug_font_size,
                    debug_font_spacing,
                    BLACK);

            DrawTextEx(
                    debug_font,
                    pos2_x_display.c_str(),
                    (Vector2){ pos1_x_display_size.x + 1, 0 },
                    debug_font_size,
                    debug_font_spacing,
                    BLACK);

            DrawTextEx(
                    debug_font,
                    pos1_y_display.c_str(),
                    (Vector2){ 0, pos1_x_display_size.y + 1 },
                    debug_font_size,
                    debug_font_spacing,
                    BLACK);

            DrawTextEx(
                    debug_font,
                    pos2_y_display.c_str(),
                    (Vector2){ pos1_x_display_size.x + 1, pos1_y_display_size.y + 1 },
                    debug_font_size,
                    debug_font_spacing,
                    BLACK);

            DrawTextEx(
                    debug_font,
                    fps_display.c_str(),
                    (Vector2){ 0, pos1_x_display_size.y + pos1_y_display_size.y + 1 },
                    debug_font_size,
                    debug_font_spacing,
                    BLACK);
        }

        EndDrawing();
    }

    UnloadFont(pause_font);
    UnloadFont(debug_font);

    CloseWindow();

    delete player1;
    delete player2;

    return 0;
}

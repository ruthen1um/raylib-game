#include <raylib.h>
#include <vector>
#include <string>
#include <cmath>

struct Entity {
    Vector2 pos;
    Vector2 size;
    Vector2 speed;
    Vector4 movement_box;
    Color color = BLACK;
    void display() {
        DrawRectangleV(pos, size, color);
    }
};

struct PlayerControls {
    int up = KEY_UP;
    int down = KEY_DOWN;
    int left = KEY_LEFT;
    int right = KEY_RIGHT;
};

struct Player : Entity {
    PlayerControls controls;
    void handle_input() {
        if (IsKeyDown(controls.up)) {
            this->pos.y = this->movement_box.y + fmodf(
                (this->movement_box.w - this->movement_box.y) + this->pos.y - this->speed.y,
                this->movement_box.w - this->movement_box.y);
        }

        if (IsKeyDown(controls.down)) {
            this->pos.y = this->movement_box.y + fmodf(
                (this->movement_box.w - this->movement_box.y) + this->pos.y + this->speed.y,
                this->movement_box.w - this->movement_box.y);
        }

        if (IsKeyDown(controls.left)) {
            this->pos.x = this->movement_box.x + fmodf(
                (this->movement_box.z - this->movement_box.x) + this->pos.x - this->speed.x,
                this->movement_box.z - this->movement_box.x);
        }

        if (IsKeyDown(controls.right)) {
            this->pos.x = this->movement_box.x + fmodf(
                (this->movement_box.z - this->movement_box.x) + this->pos.x + this->speed.x,
                this->movement_box.z - this->movement_box.x);
        }
    }
};

const Vector2 default_player_size = {
    .x = 10.0f,
    .y = 10.0f
};

const Vector2 default_player_speed = {
    .x = 4.0f,
    .y = 4.0f
};

int
main()
{
    const int width = 1280;
    const int height = 720;
    const std::string title = "my game";

    std::vector<Player *> players;

    auto player1 = new Player;
    auto player2 = new Player;

    players.push_back(player1);
    players.push_back(player2);

    player1->size = default_player_size;
    player1->speed = default_player_speed;
    player1->color = RED;

    player1->movement_box = {
        .x = 0,
        .y = 0,
        .z = width / 2.0f,
        .w = height
    };

    player1->pos = {
        .x = fabsf(player1->movement_box.x - player1->movement_box.z) / 2.0f + player1->movement_box.x,
        .y = fabsf(player1->movement_box.y - player1->movement_box.w) / 2.0f + player1->movement_box.y
    };

    player1->controls = {
        .up = KEY_W,
        .down = KEY_S,
        .left = KEY_A,
        .right = KEY_D
    };


    player2->size = default_player_size;
    player2->speed = default_player_speed;
    player2->color = GREEN;

    player2->movement_box = {
        .x = width / 2.0f,
        .y = 0,
        .z = width,
        .w = height
    };

    player2->pos = {
        .x = fabsf(player2->movement_box.x - player2->movement_box.z) / 2.0f + player2->movement_box.x,
        .y = fabsf(player2->movement_box.y - player2->movement_box.w) / 2.0f + player2->movement_box.y
    };

    player2->controls = {
        .up = KEY_UP,
        .down = KEY_DOWN,
        .left = KEY_LEFT,
        .right = KEY_RIGHT
    };

    Color bg_color = WHITE;

    InitWindow(width, height, title.c_str());

    SetExitKey(KEY_NULL);

    const int pause_font_size = 96;
    const int pause_font_spacing = 2;
    const Font pause_font = LoadFontEx("resources/fonts/Montserrat-Regular.ttf", pause_font_size, 0, 0);
    const Color pause_text_color = YELLOW;

    const int debug_font_size = 16;
    const int debug_font_spacing = 2;
    const Font debug_font = LoadFontEx("resources/fonts/Montserrat-Regular.ttf", debug_font_size, 0, 0);
    const Color debug_text_color = RED;

    bool pause = false;
    bool debug = false;
    bool vsync = true;

    const std::string pause_text = "Game is paused";

    int fps;
    std::string fps_display;
    Vector2 fps_display_size;

    std::string pos_x_display;
    std::string pos_y_display;
    Vector2 pos_x_display_size;
    Vector2 pos_y_display_size;

    Vector2 accumulator;

    while (!WindowShouldClose()) {
        if (vsync && !IsWindowState(FLAG_VSYNC_HINT)) {
            SetWindowState(FLAG_VSYNC_HINT);
        } else if (!vsync && IsWindowState(FLAG_VSYNC_HINT)) {
            ClearWindowState(FLAG_VSYNC_HINT);
        }

        if (!pause) {
            for (auto player : players) {
                player->handle_input();
            }
        }

        if (IsKeyPressed(KEY_V) && pause == false) {
            vsync = !vsync;
        }

        if (IsKeyPressed(KEY_Q) && pause == false) {
            debug = !debug;
        }

        if (IsKeyPressed(KEY_P) && debug == false) {
            pause = !pause;
        }

        BeginDrawing();

        ClearBackground(bg_color);

        for (auto player : players) {
            player->display();
        }

        if (pause) {
            DrawTextEx(
                pause_font,
                pause_text.c_str(),
                { 0, 0 },
                pause_font_size,
                pause_font_spacing,
                pause_text_color);
        }

        if (debug) {
            fps = GetFPS();
            fps_display = "fps = " + std::to_string(fps);
            fps_display_size = MeasureTextEx(
                debug_font,
                fps_display.c_str(),
                debug_font_size,
                debug_font_spacing);

            DrawTextEx(
                debug_font,
                fps_display.c_str(),
                { width - fps_display_size.x, 0 },
                debug_font_size,
                debug_font_spacing,
                debug_text_color);

            accumulator = { 0, 0 };

            for (auto player : players) {
                pos_x_display = "pos.x = " + std::to_string(player->pos.x);
                pos_x_display_size = MeasureTextEx(
                    debug_font,
                    pos_x_display.c_str(),
                    debug_font_size,
                    debug_font_spacing);

                DrawTextEx(
                    debug_font,
                    pos_x_display.c_str(),
                    { accumulator.x, accumulator.y },
                    debug_font_size,
                    debug_font_spacing,
                    player->color);

                // accumulator.x += pos_x_display_size.x;
                accumulator.y += pos_x_display_size.y;

                pos_y_display = "pos.y = " + std::to_string(player->pos.y);
                pos_y_display_size = MeasureTextEx(
                    debug_font,
                    pos_y_display.c_str(),
                    debug_font_size,
                    debug_font_spacing);

                DrawTextEx(
                    debug_font,
                    pos_y_display.c_str(),
                    { accumulator.x, accumulator.y },
                    debug_font_size,
                    debug_font_spacing,
                    player->color);

                // accumulator.x += pos_y_display_size.x;
                accumulator.y += pos_y_display_size.y;
            }

        }

        EndDrawing();
    }

    UnloadFont(pause_font);
    UnloadFont(debug_font);

    CloseWindow();

    for (auto player : players) {
        delete player;
    }

    return 0;
}

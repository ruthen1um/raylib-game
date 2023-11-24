#include <raylib.h>
#include <string>

typedef struct Button {
    Rectangle rectangle;
    Color color;
//    Rectangle shadowFirstLevel;
    Rectangle shadowOutline;
    Rectangle outline;
    Rectangle shadowSecondLevel;
    Rectangle gradientFirstLevel;
    Rectangle gradientSecondLevel;
    Color colorShadowFirstLevel;
    Color colorOutline;
    Color colorShadowOutline;
    Color colorShadowSecondLevel;
    Color colorGradientFirstLevel;
    Color colorGradientSecondLevel;
} Button;

Button button0 = {0};
bool button0Clicked = false;

void InitButton(Button *button, Rectangle rectangle, Color color) {
    button->rectangle = rectangle;
    button->outline = (Rectangle) {
        rectangle.x + rectangle.width / 15.f,
        rectangle.y + rectangle.height / 15.f,
        rectangle.width - 2 * rectangle.width / 15.f,
        rectangle.height - 2 * rectangle.height / 15.f
    };
    button->shadowOutline = (Rectangle) {
            button->outline.x - button->outline.width / 50.f,
            button->outline.y - button->outline.height / 50.f,
            button->outline.width + button->outline.width / 30.f,
            button->outline.height + button->outline.height / 30.f
    };
//    button->shadowFirstLevel = (Rectangle) {
//            rectangle.x - rectangle.width / 160.f,
//            rectangle.y + rectangle.height / 6.f,
//            rectangle.width - rectangle.width / 5.f,
//            rectangle.height - rectangle.height / 5.f
//    };
    button->shadowSecondLevel = (Rectangle) {
            button->outline.x + button->outline.width / 20.f,
            button->outline.y + button->outline.height / 20.f,
            button->outline.width - 2 * button->outline.width / 20.f,
            button->outline.height - 2 * button->outline.height / 20.f
    };
    button->gradientFirstLevel = (Rectangle) {
            button->shadowSecondLevel.x + button->shadowSecondLevel.width / 30.f,
            button->shadowSecondLevel.y + button->shadowSecondLevel.height / 30.f,
            button->shadowSecondLevel.width - 2 * button->shadowSecondLevel.width / 30.f,
            button->shadowSecondLevel.height - 2 * button->shadowSecondLevel.height / 30.f
    };
    button->gradientSecondLevel = (Rectangle) {
            button->rectangle.x + button->gradientFirstLevel.x,
            button->gradientFirstLevel.y / 2.f,
            button->gradientFirstLevel.width - 2 * abs(button->gradientFirstLevel.x - button->gradientSecondLevel.x),
            button->gradientFirstLevel.height / 2 - 2 * abs(button->gradientFirstLevel.y - button->gradientSecondLevel.y)
    };
    button->color = color;
    button->colorShadowFirstLevel = {105, 105, 105, 255};
    button->colorOutline = (Color) {
        button->colorOutline.r = button->color.r + (255 - button->color.r) * 0.25,
            button->colorOutline.g = button->color.g + (255 - button->color.g) * 0.25,
            button->colorOutline.b = button->color.b + (255 - button->color.b) * 0.25,
            button->colorOutline.a = button->color.a
    };
    button->colorShadowSecondLevel = (Color) {
            button->colorOutline.r = button->color.r * 0.75,
            button->colorOutline.g = button->color.g * 0.75,
            button->colorOutline.b = button->color.b * 0.75,
            button->colorOutline.a = button->color.a
    };
    button->colorGradientFirstLevel = button->color;
    button->colorShadowOutline = button->colorShadowSecondLevel;
    button->colorGradientSecondLevel = (Color) {
            button->colorOutline.r = button->color.r + (255 - button->color.r) * 0.5,
            button->colorOutline.g = button->color.g + (255 - button->color.g) * 0.5,
            button->colorOutline.b = button->color.b + (255 - button->color.b) * 0.5,
            button->colorOutline.a = button->color.a
    };
}

bool IsMouseOverButton(Button button) {
    return CheckCollisionPointRec(GetMousePosition(), button.rectangle);
}

int main() {
    const int screenWidth = 1280;
    const int screenHeight = 720;

    const std::string title = "menu";

    InitWindow(screenWidth, screenHeight, title.c_str());
    InitButton(&button0, (Rectangle){20, 20, 200, 200}, BLACK);

    SetTargetFPS(60);
    SetExitKey(KEY_ESCAPE);

    const int menuFontSize = 100;
    const int menuFontSpacing = 5;
    const float menuPositionX = screenWidth / 2.f - MeasureText(title.c_str(), menuFontSize) / 2;
    const int menuPositionY = screenHeight / 4 - menuFontSize / 2;
    const Font menuFont = LoadFontEx("../resources/fonts/pixel-anchor-jack_0.ttf", menuFontSize, nullptr, 0);

    while (!WindowShouldClose()) {
        if(!IsWindowState(FLAG_VSYNC_HINT))
            SetWindowState(FLAG_VSYNC_HINT);
        BeginDrawing();
        {
            if(IsMouseOverButton(button0)) {
                button0.color = RED;
            } else {
                button0.color = RED;
            }

            if(IsMouseOverButton(button0) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                button0Clicked = true;
            }

            ClearBackground(RAYWHITE);
            DrawTextEx(
                    menuFont,
                    title.c_str(),
                    (Vector2) {menuPositionX, menuPositionY},
                    menuFontSize,
                    menuFontSpacing,
                    BLACK
            );

//            DrawRectangleRec(button0.shadowFirstLevel, button0.colorShadowFirstLevel);
            DrawRectangleRec(button0.shadowOutline, button0.colorShadowOutline);
            DrawRectangleGradientV(button0.outline.x,
                                   button0.outline.y,
                                   button0.outline.width,
                                   button0.outline.height,
                                   WHITE,
                                   button0.colorOutline);
            DrawRectangleRec(button0.shadowSecondLevel, button0.colorShadowSecondLevel);
            DrawRectangleGradientV(button0.gradientFirstLevel.x,
                                   button0.gradientFirstLevel.y,
                                   button0.gradientFirstLevel.width,
                                   button0.gradientFirstLevel.height,
                                   button0.colorGradientSecondLevel,
                                   button0.colorGradientFirstLevel);
            DrawRectangleGradientV(button0.gradientSecondLevel.x,
                                   button0.gradientSecondLevel.y,
                                   button0.gradientSecondLevel.width,
                                   button0.gradientSecondLevel.height,
                                   WHITE,
                                   button0.colorGradientSecondLevel);
            DrawText(
                    "Click me",
                     button0.rectangle.x + button0.rectangle.width / 2 - MeasureText("Click me", 20) / 2,
                     button0.rectangle.y + button0.rectangle.height / 2 - 10,
                     20,
                     GREEN);

            if(button0Clicked) {
                ClearBackground(GREEN);
            }
        }
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
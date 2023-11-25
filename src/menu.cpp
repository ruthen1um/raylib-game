#include <raylib.h>
#include <string>

typedef struct Button {
    Rectangle rectangle;
    Rectangle outline;
    Rectangle shadowOutline;
    Rectangle shadowSecondLevel;
    Color color;
    Color colorOutline;
    Color colorShadowOutline;
    Color colorShadowSecondLevel;
    Color colorShadowThirdLevel;
    bool clicked = false;

    bool IsMouseOverButton() {
        return CheckCollisionPointRec(GetMousePosition(), this->rectangle);
    }

    Color ColorLight(float multiplier, Color newColor) {
        return (Color) {
                newColor.r = this->color.r + (255.f - this->color.r) * multiplier,
                newColor.g = this->color.g + (255.f - this->color.g) * multiplier,
                newColor.b = this->color.b + (255.f - this->color.b) * multiplier,
                newColor.a = this->color.a
        };
    }
    Color ColorFade(float multiplier, Color newColor) {
        return (Color) {
                newColor.r = this->color.r * multiplier,
                newColor.g = this->color.g * multiplier,
                newColor.b = this->color.b * multiplier,
                newColor.a = this->color.a
        };
    }
    Rectangle MakeDeep(float multiplier, Rectangle dependentRectangle) {
        return (Rectangle) {
                dependentRectangle.x - std::min(dependentRectangle.width, dependentRectangle.height) / multiplier,
                dependentRectangle.y - std::min(dependentRectangle.width, dependentRectangle.height) / multiplier,
                dependentRectangle.width + 2 * std::min(this->rectangle.width, this->rectangle.height) / multiplier,
                dependentRectangle.height + 2 * std::min(this->rectangle.width, this->rectangle.height) / multiplier
        };
    }
    Button MakeThreeDimensional() {
        this->outline = MakeDeep(15, this->rectangle);
        this->shadowOutline = MakeDeep(15, this->outline);
        this->shadowSecondLevel = MakeDeep(40, this->rectangle);

        this->colorOutline = ColorLight(0.75, colorOutline);
        this->colorShadowOutline = ColorFade(0.5, colorShadowOutline);
        this->colorShadowSecondLevel = ColorFade(0.5, colorShadowSecondLevel);
        this->colorShadowThirdLevel = ColorFade(0.7, colorShadowThirdLevel);
    }
} Button;

void InitButton(Button *button, Rectangle rectangle, Color color) {
    button->rectangle = rectangle;
    button->color = color;
    button->MakeThreeDimensional();
}

void DrawButton(Button button) {
    DrawRectangleRec(button.shadowOutline, button.colorShadowOutline);
    DrawRectangleGradientV(button.outline.x,
                           button.outline.y,
                           button.outline.width,
                           button.outline.height,
                           button.colorOutline,
                           button.colorShadowThirdLevel);
    DrawRectangleRec(button.shadowSecondLevel, button.colorShadowSecondLevel);
    DrawRectangleGradientV(button.rectangle.x,
                           button.rectangle.y,
                           button.rectangle.width,
                           button.rectangle.height,
                           button.color,
                           button.colorShadowThirdLevel);
}

int main() {
    const int screenWidth = 1280;
    const int screenHeight = 720;

    const std::string title = "menu";

    InitWindow(screenWidth, screenHeight, title.c_str());

    const int buttonWidth = 700;
    const int buttonHeight = 50;
    const float buttonFirstPosition = screenWidth * 0.25;

    Button button0 = {0};
    Button button1 = {0};
    Button button2 = {0};

    InitButton(&button0, (Rectangle){(screenWidth - buttonWidth) / 2.f, buttonFirstPosition, buttonWidth, buttonHeight}, GREEN);
    InitButton(&button1, (Rectangle){(screenWidth - buttonWidth) / 2.f, buttonFirstPosition + 2.f * buttonHeight, buttonWidth, buttonHeight}, YELLOW);
    InitButton(&button2, (Rectangle){(screenWidth - buttonWidth) / 2.f, buttonFirstPosition + 4.f * buttonHeight, buttonWidth, buttonHeight}, BLUE);

    SetTargetFPS(60);
    SetExitKey(KEY_ESCAPE);

    const int menuFontSize = 100;
    const int menuFontSpacing = 5;
    const float menuPositionX = screenWidth / 2.f - MeasureText(title.c_str(), menuFontSize) / 2;
    const int menuPositionY = screenHeight / 4 - menuFontSize / 2;
    const Font menuFont = LoadFontEx("../resources/fonts/Pixel_Anchor-Jack/pixel-anchor-jack_0.ttf", menuFontSize, nullptr, 0);

    while (!WindowShouldClose()) {
        if(!IsWindowState(FLAG_VSYNC_HINT))
            SetWindowState(FLAG_VSYNC_HINT);
        BeginDrawing();
        {
//            TODO ......ДОПИСАТЬ ЛОГИКУ КНОПКИ ДЛЯ ДВОЙНОГО НАЖАТИЯ И ПРОПИСАТЬ ФУНКЦИЮ......
//            if(button0.IsMouseOverButton()) {
//                button0.color = RED;
//            } else {
//                button0.color = GREEN;
//            }
//
//            if(button0.IsMouseOverButton() && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
//                button0.clicked = true;
//            }

            ClearBackground(RAYWHITE);
            DrawTextEx(
                    menuFont,
                    title.c_str(),
                    (Vector2) {menuPositionX, menuPositionY},
                    menuFontSize,
                    menuFontSpacing,
                    BLACK
            );

            DrawButton(button0);
            DrawButton(button1);
            DrawButton(button2);

            if(button0.clicked) {
                ClearBackground(GREEN);
            }
            if(button1.clicked) {
                ClearBackground(BLUE);
            }
            if(button2.clicked) {
                ClearBackground(RED);
            }
        }
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
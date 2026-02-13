#include "raylib.h"

Color green = {173, 204, 96, 255};
Color darkGreen = {43, 51, 24, 255};

int main() {
  const int screenWidth = 700;
  const int screenHeight = 700;

  InitWindow(screenWidth, screenHeight, "Snake - Raylib");
  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    BeginDrawing();
      ClearBackground(green);
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
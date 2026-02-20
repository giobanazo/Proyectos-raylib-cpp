#include <iostream>
#include <raylib.h>

using namespace std;

int main() {
  const int screen_width = 1180;
  const int screen_height = 700;

  InitWindow(screen_width, screen_height, "My Pong Game!");
  SetTargetFPS(60);

  while(!WindowShouldClose()) {


    BeginDrawing();

      DrawLine(screen_width / 2, 0, screen_width / 2, screen_height, WHITE);
      DrawCircle(screen_width / 2, screen_height / 2, 20, WHITE);

      // el 60 lo sacamos de la altura del rectangulo (120) dividido entre 2
      DrawRectangle(10, screen_height / 2 - 60 , 25, 120, WHITE);
      DrawRectangle(screen_width - 35, screen_height / 2 - 60, 25, 120, WHITE);
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
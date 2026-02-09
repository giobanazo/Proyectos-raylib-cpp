#include "raylib.h"
#include "game.h"


// Esto sirve para hacer un retardo y para 
double lastUpdateTime = 0.0; 
bool EventTriggered(double interval) {
  double currentTime = GetTime();
  if (currentTime - lastUpdateTime >= interval) {
    lastUpdateTime = currentTime;
    return true;
  }

  return false;
}

int main() {

  Color darkBlue = {44, 44, 127, 255};

  InitWindow(300, 600, "raylib Tetris");
  SetTargetFPS(60);

  Game game = Game();

  while (!WindowShouldClose()) {

    if (EventTriggered(0.2)) {
      game.MoveBlockDown();
    }

    BeginDrawing();
      game.HandleInput();
      ClearBackground(darkBlue);
      game.Draw();
    EndDrawing();

  }

  CloseWindow();
 
  return 0;
}
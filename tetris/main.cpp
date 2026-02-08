#include "raylib.h"
#include "grid.h"

int main() {

  Color darkBlue = {44, 44, 127, 255};

  InitWindow(300, 600, "raylib Tetris");
  SetTargetFPS(60);

  Grid grid = Grid();

  grid.grid[4][2] = 1;    
  grid.grid[5][2] = 1;
  grid.grid[6][2] = 1;
  grid.grid[7][2] = 1;
  grid.grid[8][2] = 1;
  grid.grid[9][2] = 1;
  grid.grid[10][2] = 1;

  grid.Print();

  while (!WindowShouldClose()) {

    BeginDrawing();
      ClearBackground(darkBlue);

      grid.Draw();

    EndDrawing();

  }

  CloseWindow();
 
  return 0;
}
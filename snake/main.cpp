#include "raylib.h"

Color green = {173, 204, 96, 255};
Color darkGreen = {43, 51, 24, 255};

int cellSize = 28;
int cellCount = 25;

class Food {
  public:
    // position.x = 5  |  position.y = 6
    Vector2 position;
    Texture2D texture;

    // Constructor
    Food() {
      Image image = LoadImage("food.png");
      /* Texture2D es un tipo de datos optimizado para el procesamiento 
      de GPU y hace una representación mas rapida */
      texture = LoadTextureFromImage(image);
      // Liberar memoria ya que la variable image ya no se va a utilizar
      UnloadImage(image);
      position = GenerateRandomPosition();
    }

    // Desconstructor
    ~Food() {
      // Liberar memoria con la variable textura
      UnloadTexture(texture);
    }

    void Draw() {
      DrawTexture(texture, position.x * cellSize, position.y * cellSize, WHITE);
    }

    Vector2 GenerateRandomPosition() {
      float x = GetRandomValue(0, cellCount - 1);
      float y = GetRandomValue(0, cellCount - 1);

      return Vector2{x, y};
    }
};

int main() {
  InitWindow(cellSize * cellCount, cellSize * cellCount, "Snake - Raylib");
  SetTargetFPS(60);

  Food food = Food();

  while (!WindowShouldClose()) {
    BeginDrawing();
      ClearBackground(green);

      food.Draw();
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
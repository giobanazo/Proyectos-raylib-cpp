#include "raylib.h"

/* deque es un tipo de dato que se puede agregar datos tanto al principio
como al final */
#include <deque>


Color green = {173, 204, 96, 255};
Color darkGreen = {43, 51, 24, 255};

int cellSize = 28;
int cellCount = 25;

class Snake {
  public:
    std::deque<Vector2> body = {Vector2{6, 9}, Vector2{5, 9}, Vector2{4, 9}};

    void Draw() {
      for (int i = 0; i < body.size(); i++) {
        float x = body[i].x;
        float y = body[i].y;
        Rectangle segment = Rectangle{x * cellSize, y * cellSize, (float)cellSize, (float)cellSize};
        DrawRectangleRounded(segment, 0.5, 6, darkGreen);
      }
    }
};

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

  Snake snake = Snake();
  Food food = Food();

  while (!WindowShouldClose()) {
    BeginDrawing();
      ClearBackground(green);

      snake.Draw();
      food.Draw();

      EndDrawing();
    }

  CloseWindow();
  return 0;
}
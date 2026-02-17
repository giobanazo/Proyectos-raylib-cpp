#include "raylib.h"
#include "raymath.h"

/* deque es un tipo de dato que se puede agregar datos tanto al principio
como al final */
#include <deque>


Color green = {173, 204, 96, 255};
Color darkGreen = {43, 51, 24, 255};

int cellSize = 28;
int cellCount = 25;

double lastUpdateTime = 0;

bool ElementInDeque(Vector2 element, std::deque<Vector2> deque) {
  for (int i = 0; i < deque.size(); i++) {
    if (Vector2Equals(deque[i], element)) {
      return true;
    }
  }
  return false;
}


bool eventTriggered(double interval) {
  double currentTime = GetTime();
  if (currentTime - lastUpdateTime >= interval) {
    lastUpdateTime = currentTime;
    return true;
  }
  return false;
}


class Snake {
  public:
    std::deque<Vector2> body = {Vector2{6, 9}, Vector2{5, 9}, Vector2{4, 9}};
    Vector2 direction = {1, 0};
    bool addSegment = false;

    void Draw() {
      for (int i = 0; i < body.size(); i++) {
        float x = body[i].x;
        float y = body[i].y;
        Rectangle segment = Rectangle{x * cellSize, y * cellSize, (float)cellSize, (float)cellSize};
        DrawRectangleRounded(segment, 0.5, 6, darkGreen);
      }
    }

    void Update() {
      // push_front agrega un elemento al inicio del deque
      body.push_front(Vector2Add(body[0], direction)); // Vector2Add suma de vectores de tipo Vector2

      if (addSegment == true) {
        addSegment = false;
      } else {
        /* pop_back() elimina el último elemento del deque */
        body.pop_back();
      }
    }

    void Reset() {
      body = {Vector2{6, 9}, Vector2{5, 9}, Vector2{4, 9}};
      direction = {1, 0};
    }
};


class Food {
  public:
    // position.x = 5  |  position.y = 6
    Vector2 position;
    Texture2D texture;

    // Constructor
    Food(std::deque<Vector2> snakeBody) {
      Image image = LoadImage("food.png");
      /* Texture2D es un tipo de datos optimizado para el procesamiento 
      de GPU y hace una representación mas rapida */
      texture = LoadTextureFromImage(image);
      // Liberar memoria ya que la variable image ya no se va a utilizar
      UnloadImage(image);
      position = GenerateRandomPosition(snakeBody);
    }

    // Desconstructor
    ~Food() {
      // Liberar memoria con la variable textura
      UnloadTexture(texture);
    }

    void Draw() {
      DrawTexture(texture, position.x * cellSize, position.y * cellSize, WHITE);
    }

    Vector2 GenerateRandomCell() {
      float x = GetRandomValue(0, cellCount - 1);
      float y = GetRandomValue(0, cellCount - 1);
      return Vector2{x, y};
    }

    Vector2 GenerateRandomPosition(std::deque<Vector2> snakeBody) {
      Vector2 position = GenerateRandomCell();

      while(ElementInDeque(position, snakeBody)) {
        position = GenerateRandomCell();
      }

      return position;
    }
};


class Game {
  public:
    Snake snake = Snake();
    Food food = Food(snake.body);
    bool running = true;

    void Draw() {
      food.Draw();
      snake.Draw();
    }

    void Update() {
      if (running) {
        snake.Update();
        CheckCollisionWithFood();
        CheckCollisionWithEdges();
        CheckCollisionWithTail();
      }
    }

    void CheckCollisionWithFood() {
      if (Vector2Equals(snake.body[0], food.position)) {
        food.position = food.GenerateRandomPosition(snake.body);
        snake.addSegment = true;
      }
    }

    void CheckCollisionWithTail() {
      std::deque<Vector2> headlessBody = snake.body;
      headlessBody.pop_front(); // Cuerpo de la serpiente sin cabeza
      if (ElementInDeque(snake.body[0], headlessBody)) {
        GameOver();
      }
    }

    void GameOver() {
      snake.Reset();
      food.position = food.GenerateRandomPosition(snake.body);
      running = false;
    }

    void CheckCollisionWithEdges() {
      if (snake.body[0].x == cellCount || snake.body[0].x == -1) {
        GameOver();
      }
      if (snake.body[0].y == cellCount || snake.body[0].y == -1) {
        GameOver();
      }
    }
};


int main() {
  InitWindow(cellSize * cellCount, cellSize * cellCount, "Snake - Raylib");
  SetTargetFPS(60);

  Game game = Game();

  while (!WindowShouldClose()) {
    BeginDrawing();
      ClearBackground(green);

      if (eventTriggered(0.2)) {
        game.Update();
      }

      if (IsKeyPressed(KEY_W) && game.snake.direction.y != 1) {
        game.snake.direction = {0, -1};
        game.running = true;
      }
      if (IsKeyPressed(KEY_S) && game.snake.direction.y != -1) {
        game.snake.direction = {0, 1};
        game.running = true;
      }
      if (IsKeyPressed(KEY_A) && game.snake.direction.x != 1) {
        game.snake.direction = {-1, 0};
        game.running = true;
      }
      if (IsKeyPressed(KEY_D) && game.snake.direction.x != -1) {
        game.snake.direction = {1, 0};
        game.running = true;
      }

      game.Draw();
      
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
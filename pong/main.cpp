#include <iostream>
#include <raylib.h>

using namespace std;

class Ball {
  public:
    float x, y;
    int speed_x, speed_y, radius;

    void Draw() {
      DrawCircle(x, y, radius, WHITE);
    }

    void Update() {
      x += speed_x;
      y += speed_y;

      if (y + radius >= GetScreenHeight() || y - radius <= 0) {
        speed_y *= -1;
      }

      if (x + radius >= GetScreenWidth() || x - radius <= 0) {
        speed_x *= -1;
      }
    }
};

class Paddle {
  public:
    float x, y, width, height;
    int speed;

    void Draw() {
      DrawRectangle(x, y, width, height, WHITE); 
    }

    void Update() {
      if (IsKeyDown(KEY_UP)) {
        y -= speed;
      }

      if (IsKeyDown(KEY_DOWN)) {
        y += speed;
      }

      if (y <= 0) {
        y = 0;
      }

      if (y + height >= GetScreenHeight()) {
        y = GetScreenHeight() - height;
      }
    }
};

Ball ball;
Paddle player;

int main() {
  const int screen_width = 1180;
  const int screen_height = 700;

  InitWindow(screen_width, screen_height, "My Pong Game!");
  SetTargetFPS(60);
  
  ball.radius = 20;
  ball.x = screen_width / 2;
  ball.y = screen_height / 2;
  ball.speed_x = 7;
  ball.speed_y = 7;

  player.width = 25;
  player.height = 120;
  player.x = screen_width - player. width - 10;
  player.y = screen_height / 2 - player.height / 2;
  player.speed = 6;

  while(!WindowShouldClose()) {
    ball.Update();
    player.Update();

    BeginDrawing();
      ClearBackground(BLACK);
      DrawLine(screen_width / 2, 0, screen_width / 2, screen_height, WHITE);
    
      ball.Draw();

      // el 60 lo sacamos de la altura del rectangulo (120) dividido entre 2
      DrawRectangle(10, screen_height / 2 - 60 , 25, 120, WHITE);
      player.Draw();
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
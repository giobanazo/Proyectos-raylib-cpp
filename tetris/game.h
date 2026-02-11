#pragma once
#include "grid.h"
#include "blocks.cpp"

class Game {
  public:
    Game();
    ~Game(); // Destructor
    Grid grid;
    bool gameOver = false;
    int score;
    Music music;

    void Draw();
    void HandleInput();
    void MoveBlockDown();

  private:
    std::vector<Block> blocks;
    Block currentBlock;
    Block nextBlock;
    Sound rotateSound;
    Sound clearSound;

    void MoveBlockLeft();
    void MoveBlockRight();
    Block GetRandomBlock();
    std::vector<Block> GetAllBlocks();
    bool IsBlockOutside();
    void RotateBlock();
    void LockBlock();
    bool BlockFits();
    void Reset();
    void UpdateScore(int linesCleared, int moveDownPoints);
};
#pragma once
#include "grid.h"
#include "blocks.cpp"

class Game {
  public:
    Game();
    Grid grid;
    Block GetRandomBlock();
    std::vector<Block> GetAllBlocks();
    bool gameOver = false;
    int score;
    void Draw();
    void HandleInput();
    void MoveBlockLeft();
    void MoveBlockRight();
    void MoveBlockDown();

  private:
    bool IsBlockOutside();
    void RotateBlock();
    void LockBlock();
    bool BlockFits();
    void Reset();
    void UpdateScore(int linesCleared, int moveDownPoints);
    std::vector<Block> blocks;
    Block currentBlock;
    Block nextBlock;
};
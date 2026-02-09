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
    std::vector<Block> blocks;
    Block currentBlock;
    Block nextBlock;
};
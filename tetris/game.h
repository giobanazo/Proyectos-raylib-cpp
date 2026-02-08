#pragma once
#include "grid.h"
#include "blocks.cpp"

class Game {
  public:
    Game();
    Grid grid;
    Block GetRandomBlock();
    std::vector<Block> GetAllBlocks();
    void Draw();
    void HandleInput();
    void MoveBlockLeft();
    void MoveBlockRight();
    void MoveBlockDown();

  private:
    bool IsBlockOutside();
    void RotateBlock();
    std::vector<Block> blocks;
    Block currentBlock;
    Block nextBlock;
};
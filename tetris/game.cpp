#include "game.h"
#include <random>

Game::Game() {
  grid = Grid();
  blocks = GetAllBlocks();
  currentBlock = GetRandomBlock();
  nextBlock = GetRandomBlock();
}

Block Game::GetRandomBlock() {
  if (blocks.empty()) {
    blocks = GetAllBlocks();
  }

  int randomIndex = rand() % blocks.size();
  Block block = blocks[randomIndex];
  /* 
    blocks = bloques que todavía no han salido
    GetRandomBlock() = saca uno al azar
    Una vez que sale, ya no debería volver a salir por blocks.erase
  */
  blocks.erase(blocks.begin() + randomIndex); 
  return block;
}

std::vector<Block> Game::GetAllBlocks() {
  return {IBlock(), JBlock(), LBlock(), OBlock(), TBlock(), ZBlock()}; 
}


void Game::Draw() {
  grid.Draw();
  currentBlock.Draw();
}


void Game::HandleInput() {
  int keyPressed = GetKeyPressed();

  switch (keyPressed) {
    case KEY_A:
      MoveBlockLeft();
      break;
    
    case KEY_D:
      MoveBlockRight();
      break;

    case KEY_S:
      MoveBlockDown();
      break;


    case KEY_W:
      MoveBlockUp();
      break;
    
    default:

      break;
  }
}

void Game::MoveBlockLeft() {
  currentBlock.Move(0, -1);
  if (IsBlockOutside()) {
    currentBlock.Move(0, 1); 
  }
}

void Game::MoveBlockRight() {
  currentBlock.Move(0, 1);
  if (IsBlockOutside()) {
    currentBlock.Move(0, -1);
  }
}

void Game::MoveBlockDown() {
  currentBlock.Move(1, 0);
  if (IsBlockOutside()) {
    currentBlock.Move(-1, 0); 
  }
}

void Game::MoveBlockUp() {
  currentBlock.Move(-1, 0);
  if (IsBlockOutside()) {
    currentBlock.Move(1, 0);
  }
}


bool Game::IsBlockOutside() {
  std::vector<Position> tiles = currentBlock.GetCellPositions();

  for (Position item: tiles) {
    if (grid.IsCellOutside(item.row, item.column)) {
      return true;
    }
  }

  return false;
}
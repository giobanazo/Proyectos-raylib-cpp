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
      RotateBlock();
      break;
  
    default:

      break;
  }
}

void Game::MoveBlockLeft() {
  currentBlock.Move(0, -1);
  /* IsBlockOutSide() Verifica si en el siguiente movimiento de la ficha no 
  se pase de los limites de la grilla */
  if (IsBlockOutside() || BlockFits() == false) {
    currentBlock.Move(0, 1); 
  }
}

void Game::MoveBlockRight() {
  currentBlock.Move(0, 1);
  if (IsBlockOutside() || BlockFits() == false) {
    currentBlock.Move(0, -1);
  }
}

void Game::MoveBlockDown() {
  currentBlock.Move(1, 0);
  if (IsBlockOutside() || BlockFits() == false) {
    currentBlock.Move(-1, 0); 
    LockBlock();
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


void Game::RotateBlock() {
  currentBlock.Rotate();
  if (IsBlockOutside() || BlockFits() == false) {
    currentBlock.UndoRotation();
  }
}

void Game::LockBlock() {
  std::vector<Position> tiles = currentBlock.GetCellPositions();

  // Actualizamos la grilla 
  for(Position item: tiles) {
    grid.grid[item.row][item.column] = currentBlock.id;
  }

  /* Cuando se termine el bucle for de arriba, se actualiza el bloque
  actual para que se pase a otro bloque y el usuario pueda jugar con 
  el siguente bloque */
  currentBlock = nextBlock;
  nextBlock = GetRandomBlock();
}


/* Verifica si en el siguiente movimiento del jugador con la ficha (W, A, S, D)
la celda esta vacia y si no esta vacia retorna falso y devuelve la ficha 
a la posición anterior del jugador */
bool Game::BlockFits() {
  std::vector<Position> tiles = currentBlock.GetCellPositions();
  for (Position item: tiles) {
    if (grid.IsCellEmpty(item.row, item.column) == false) {
      return false;
    }
  }

  return true;
}
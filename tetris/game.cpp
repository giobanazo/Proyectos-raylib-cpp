#include "game.h"
#include <random>

Game::Game() {
  grid = Grid();
  blocks = GetAllBlocks();
  currentBlock = GetRandomBlock();
  nextBlock = GetRandomBlock();
  gameOver = false;
  score = 0;
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
  currentBlock.Draw(11, 11);

  switch (nextBlock.id) {
    case 3:
      nextBlock.Draw(255, 290);
      break;
    
    case 4:
      nextBlock.Draw(255, 280);
      break;

    default:
      nextBlock.Draw(270, 270);
      break;
  }
}


void Game::HandleInput() {
  int keyPressed = GetKeyPressed();

  if (gameOver && keyPressed != 0) {
    gameOver = false;
    Reset();
  }
  switch (keyPressed) {
    case KEY_A:
      MoveBlockLeft();
      break;
    
    case KEY_D:
      MoveBlockRight();
      break;

    case KEY_S:
      MoveBlockDown();
      UpdateScore(0, 1);
      break;

    case KEY_W:
      RotateBlock();
      break;


  
    default:

      break;
  }
}

void Game::MoveBlockLeft() {
  if (!gameOver) {
    currentBlock.Move(0, -1);
    /* IsBlockOutSide() Verifica si en el siguiente movimiento de la ficha no 
    se pase de los limites de la grilla */
    if (IsBlockOutside() || BlockFits() == false) {
      currentBlock.Move(0, 1); 
    }
  } 
}

void Game::MoveBlockRight() {
  if (!gameOver) {
    currentBlock.Move(0, 1);
    if (IsBlockOutside() || BlockFits() == false) {
      currentBlock.Move(0, -1);
    }
  }
}

void Game::MoveBlockDown() {
  if (!gameOver) {
    currentBlock.Move(1, 0);
    if (IsBlockOutside() || BlockFits() == false) {
      currentBlock.Move(-1, 0); 
      LockBlock();
    }
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
  if (!gameOver) {
    currentBlock.Rotate();
    if (IsBlockOutside() || BlockFits() == false) {
      currentBlock.UndoRotation();
    }
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
  if (BlockFits() == false) {
    gameOver = true;
  }

  nextBlock = GetRandomBlock();
  int rowsCleared = grid.ClearFullRows();
  UpdateScore(rowsCleared, 0);
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

void Game::Reset() {
  grid.Initialize();
  blocks = GetAllBlocks();
  currentBlock = GetRandomBlock();
  nextBlock = GetRandomBlock();
  score = 0;
}


void Game::UpdateScore(int linesCleared, int moveDownPoints) {
  switch (linesCleared) {
    case 1:
      score += 100;
      break;

    case 2:
      score += 300;
      break;
    
    case 3: 
      score += 600;
      break;
      
    default:
      break;
  }

  score += moveDownPoints;
}
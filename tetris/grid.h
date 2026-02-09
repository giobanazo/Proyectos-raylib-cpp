/* 
  Para que solo se incluya una vez en tiempo de compilación 
  para evitar definiciones duplicadas
*/
#pragma once
#include <vector>
#include <raylib.h>

class Grid {
  public:
    Grid(); // Meotodo constructor
    void Initialize();
    void Print();
    void Draw();
    bool IsCellOutside(int row, int column);
    bool IsCellEmpty(int row, int column);
    int grid[20][10]; // 20 = filas  |  10 = columnas


  private:
    int numRows;
    int numCols;
    int cellSize;
    std::vector<Color> colors;
};
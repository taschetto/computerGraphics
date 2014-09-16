#pragma once

#include <vector>
#include "Cell.h"
#include "Direction.h"

class Maze
{
private:
  size_t level;
  size_t width;
  size_t height;
  Cell** grid;
  Cell* initial;
  Cell* goal;
  std::vector<Direction> Directions(Cell cell);
  std::vector<Cell*> Batteries;

public:
  Maze(size_t);
  virtual ~Maze();

  size_t GetWidth();
  size_t GetHeight();
  std::vector<Cell*> Cells();
  Cell* At(size_t x, size_t y);
  Cell* GetInitial();
  Cell* GetGoal();
  std::vector<Cell*> GetBatteries()
  {
    return Batteries;
  }
  
  void Generate();
};


#pragma once

#include <map>
#include <vector>
#include "Direction.h"
#include "Cell.h"

class Maze
{
private:
  size_t width;
  size_t height;
  Cell** grid;

  Cell* initial;
  Cell* final;

  std::vector<Direction> Directions(Cell cell);

public:
  Maze(size_t, size_t);
  virtual ~Maze();

  size_t GetWidth();
  size_t GetHeight();
  void Generate();
  Cell* At(size_t x, size_t y);
  std::vector<Cell*> Cells();

  void Dump();
};


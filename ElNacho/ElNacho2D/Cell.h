#pragma once

#include <set>
#include "Direction.h"

class Cell
{
private:
  size_t x;
  size_t y;
  std::set<Direction> walls;
  bool visited;

public:
  Cell();
  ~Cell();

  void SetX(size_t);
  void SetY(size_t);
  size_t GetX();
  size_t GetY();
  std::set<Direction> GetWalls();

  bool IsVisited();
  void Visit();
  void Carve(Direction);
  bool HasWall(Direction);
};


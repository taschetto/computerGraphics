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
  int order;
  Cell();
  ~Cell();

  void SetY(size_t);
  void SetX(size_t);
  size_t GetY();
  size_t GetX();
  std::set<Direction> GetWalls();

  bool IsVisited();
  void Visit();
  void Carve(Direction);
  bool HasWall(Direction);
};


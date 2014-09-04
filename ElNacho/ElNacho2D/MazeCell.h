#pragma once

#include <set>
#include "Direction.h"

class MazeCell
{
private:
  size_t x;
  size_t y;
  std::set<Direction> walls;
  bool visited;

public:
  MazeCell();
  ~MazeCell();

  void SetY(size_t);
  void SetX(size_t);
  size_t GetY();
  size_t GetX();
  std::set<Direction> GetWalls();

  bool IsVisited();
  void Visit();
  void Carve(Direction);
};


#pragma once

#include <map>
#include "Direction.h"
#include "MazeCell.h"

class Maze
{
private:
  size_t width;
  size_t height;
  MazeCell** grid;

  std::map<Direction, size_t> Dx;
  std::map<Direction, size_t> Dy;
  std::map<Direction, Direction> Oposite;
public:
  Maze(size_t, size_t);
  virtual ~Maze();

  void Generate();
  void Print();
};


#pragma once

#include <map>
#include <vector>
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

  std::vector<Direction> Directions(MazeCell mazeCell);

public:
  Maze(size_t, size_t);
  virtual ~Maze();

  size_t GetWidth();
  size_t GetHeight();
  void Generate();
  std::vector<MazeCell*> Cells();

  void Dump();
};


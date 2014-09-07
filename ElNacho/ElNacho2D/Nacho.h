#pragma once

#include "Maze.h"
#include "Direction.h"

class Nacho
{
private:
  Maze* maze;
  size_t x;
  size_t y;

public:
  Nacho(Maze*);
  virtual ~Nacho();

  size_t GetX();
  size_t GetY();

  void Walk(Direction);
};


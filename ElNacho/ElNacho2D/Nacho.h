#pragma once

#include "Maze.h"
#include "Direction.h"

class Nacho
{
private:
  Maze* maze;
  size_t x;
  size_t y;

  size_t oldx;
  size_t oldy;
  float radius;

  void SetX(size_t);
  void SetY(size_t);

public:
  Nacho(Maze*);
  virtual ~Nacho();

  size_t GetX();
  size_t GetY();
  size_t GetOldX();
  size_t GetOldY();

  bool Walk(Direction);

  float GetRadius()
  {
    return radius;
  }

  void SetRadius(float nradius)
  {
    radius = nradius;
  }
};

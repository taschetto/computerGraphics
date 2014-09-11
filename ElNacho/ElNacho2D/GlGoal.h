#pragma once
#include "GlCell.h"

class GlGoal :  public GlCell
{
public:
  GlGoal(Maze* maze, Cell* cell);
  virtual ~GlGoal();

  void Draw();
};

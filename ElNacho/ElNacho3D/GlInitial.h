#pragma once
#include "GlCell.h"
class GlInitial :
  public GlCell
{
public:
  GlInitial(Maze* maze, Cell* cell);
  virtual ~GlInitial();

  void Draw();
};


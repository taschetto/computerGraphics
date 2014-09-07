#pragma once
#include "GlCell.h"
class GlSpecialCell :
  public GlCell
{
public:
  GlSpecialCell(Maze* maze, Cell* cell);
  virtual ~GlSpecialCell();

  void Draw();
};


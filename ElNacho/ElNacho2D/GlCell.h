#pragma once

#include "IDrawable.h"
#include "Maze.h"

class GlCell : public IDrawable
{
private:
  Maze* maze;
  Cell* cell;
  float GetTx();
  float GetTy();

public:
  GlCell(Maze* maze, Cell* cell);
  virtual ~GlCell();

  void Scale();
  void Translate();
  virtual void Draw();
};


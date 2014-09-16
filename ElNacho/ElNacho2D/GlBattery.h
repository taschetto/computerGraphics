#pragma once

#include "IDrawable.h"
#include "Maze.h"
#include "Cell.h"

class GlBattery : public IDrawable
{
private:
  Maze* maze;
  Cell* cell;

  float GetTx();
  float GetTy();

public:
  GlBattery(Maze* maze, Cell* cell);
  ~GlBattery();

  void Scale();
  void Translate();
  virtual void Draw();
};


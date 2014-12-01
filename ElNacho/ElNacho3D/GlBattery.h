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

  float size = 0;
  float gain = 0.01f;

public:
  GlBattery(Maze* maze, Cell* cell);
  ~GlBattery();

  void Scale();
  void Translate();
  virtual void Draw();
};


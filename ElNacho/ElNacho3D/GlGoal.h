#pragma once
#include "GlCell.h"

class GlGoal :  public GlCell
{
public:
  GlGoal(Maze* maze, Cell* cell);
  virtual ~GlGoal();

  void Translate();
  void Draw();

private:
  float GetTx();
  float GetTy();

  float faces = 8;
  int count = 0;
  float inc = 1;
};

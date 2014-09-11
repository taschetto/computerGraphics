#pragma once
#include "IDrawable.h"
#include "Nacho.h"

class GlNacho : public IDrawable
{
private:
  Maze* maze;
  Nacho* nacho;
  float left, right, bottom, top;
  float GetTx();
  float GetTy();

public:
  GlNacho(Maze*, Nacho*, float, float, float, float);
  virtual ~GlNacho();

  void Scale();
  void Translate();
  void Draw();
};


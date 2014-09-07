#pragma once
#include "IDrawable.h"
#include "Nacho.h"

class GlNacho : public IDrawable
{
private:
  Maze* maze;
  Nacho* nacho;
  float GetTx();
  float GetTy();

public:
  GlNacho(Maze*, Nacho*);
  virtual ~GlNacho();

  void Scale();
  void Translate();
  void Draw();
};


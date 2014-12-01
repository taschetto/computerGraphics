#pragma once
#include "IDrawable.h"
#include "Nacho.h"

class GlNacho : public IDrawable
{
private:
  Maze* maze;
  Nacho* nacho;
  float left, right, bottom, top;
  float GetTx(size_t);
  float GetTy(size_t);

public:
  GlNacho(Maze*, Nacho*);
  virtual ~GlNacho();

  void Scale();
  void Translate();
  void Draw();
};


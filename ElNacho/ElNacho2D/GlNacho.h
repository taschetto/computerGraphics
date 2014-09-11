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
  void DrawArc(float, float, float, float, float, int);
  void DrawCircle(float, float, float, int);

public:
  GlNacho(Maze*, Nacho*);
  virtual ~GlNacho();

  void Scale();
  void Translate();
  void Draw();
};


#pragma once

#include "Maze.h"
#include "Nacho.h"
#include "IDrawable.h"

class Engine
{
private:
  Maze* maze;
  Nacho* nacho;

  void InitRender();

public:
  Engine();
  ~Engine();

  bool InitGL();
  void Display();
  void Keyboard(unsigned char, int, int);
  void SpecialFunc(int, int, int);

  void Draw(IDrawable*);
};


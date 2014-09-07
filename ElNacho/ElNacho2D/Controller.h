#pragma once

#include "Maze.h"
#include "Nacho.h"

class Controller
{
private:
  Maze* maze;
  Nacho* nacho;

  void InitRender();

public:
  Controller();
  ~Controller();

  bool InitGL();
  void Display();
  void Keyboard(unsigned char, int, int);
  void SpecialFunc(int, int, int);
};


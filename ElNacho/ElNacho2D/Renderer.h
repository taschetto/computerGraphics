#pragma once

#include "Maze.h"

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 500;

class Renderer
{
private:
  Maze* maze;

public:
  Renderer();
  ~Renderer();

  bool InitGL();
  void Update();
  void Render();
};


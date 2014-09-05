#pragma once

#include "Maze.h"

class GLMazeCell
{
private:
  Maze* maze;
  MazeCell* mazeCell;

public:
  GLMazeCell(Maze* maze, MazeCell* mazeCell);
  virtual ~GLMazeCell();
  
  float GetTx();
  float GetTy();
  void Translate();
  void Draw();
};


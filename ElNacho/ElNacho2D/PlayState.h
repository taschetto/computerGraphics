#pragma once

#include "IGameState.h"
#include "Maze.h"
#include "Nacho.h"
#include "IDrawable.h"

class PlayState : public IGameState
{
private:
  PlayState()
  {}

  static PlayState* instance;
  
  Maze* maze;
  Nacho* nacho;

  void InitRender();

public:
  void Init();
  void Cleanup();

  void Pause();
  void Resume();

  void Draw();
  void Keyboard(unsigned char, int, int);
  void SpecialFunc(int, int, int);

  static PlayState* Instance()
  {
    if (instance == nullptr)
      instance = new PlayState();

    return instance;
  }
};


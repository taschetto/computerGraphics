#pragma once

#include "GameEngine.h"
#include "GameState.h"
#include "Maze.h"
#include "Nacho.h"
#include "IDrawable.h"

class PlayState : public GameState
{
private:
  PlayState() {}

  static PlayState* instance;
  
  size_t level = 6;
  Maze* maze;
  Nacho* nacho;

public:
  void Init();
  void Cleanup();

  void Pause();
  void Resume();

  void HandleEvents(GameEngine*);
  void Draw();
  void Keyboard(GameEngine*, unsigned char, int, int);
  void SpecialFunc(GameEngine*, int, int, int);

  static PlayState* Instance()
  {
    if (instance == nullptr)
      instance = new PlayState();

    return instance;
  }
};


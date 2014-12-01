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
  
  size_t level = 1;
  Maze* maze;
  Nacho* nacho;

  std::vector<IDrawable*> drawables;
  std::vector<IDrawable*> batteries;

  float walkFromX, walkFromY;

  GLfloat rotX, rotY, rotX_ini, rotY_ini;
  GLfloat obsX, obsY, obsZ = 20, obsX_ini, obsY_ini, obsZ_ini;
  GLfloat fAspect = 1, angle = 45;
  int x_ini, y_ini, bot;
  int view_option = 0;
  void SetObserverPosition();
  void SetVisualizationParams();
  void SetLights();

public:
  void Init();
  void Cleanup();

  void Pause();
  void Resume();

  void HandleEvents(GameEngine*);
  void Draw();
  void Keyboard(GameEngine*, unsigned char, int, int);
  void SpecialFunc(GameEngine*, int, int, int);
  void ReshapeFunc(GameEngine*, GLsizei, GLsizei);
  void MotionFunc(GameEngine*, int, int);
  void MouseFunc(GameEngine*, int, int, int, int);

  static PlayState* Instance()
  {
    if (instance == nullptr)
      instance = new PlayState();

    return instance;
  }

  float posX, posY, posZ;
};


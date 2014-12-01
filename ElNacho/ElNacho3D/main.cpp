#include <iostream>
#include "OpenGL.h"
#include "GameEngine.h"
#include "InitialState.h"

namespace
{
  const int ScreenWidth = 1024;
  const int ScreenHeight = 725;
  const int ScreenFps = 60;
  const char* WindowTitle = "El Nacho: a game by Guilherme Taschetto";

  void doDisplay(void);
  void doKeyboard(unsigned char, int, int);
  void doSpecialFunc(int, int, int);
  void doReshapeFunc(GLsizei, GLsizei);
  void doMotionFunc(int, int);
  void doMouseFunc(int, int, int, int);
  void runMainLoop(int);

  GameEngine engine;
}

int main(int argc, char** argv)
{
  engine.Init(argc, argv, ::ScreenWidth, ::ScreenHeight, ::WindowTitle);

  if (!engine.InitGL())
  {
    std::cerr << "ElNacho error: Unable to initialize graphics library!" << std::endl;
    return 1;
  }

  engine.ChangeState(InitialState::Instance());

  ::glutDisplayFunc(::doDisplay);
  ::glutKeyboardFunc(::doKeyboard);
  ::glutSpecialFunc(::doSpecialFunc);
  ::glutTimerFunc(1000 / ScreenFps, ::runMainLoop, 0);
  ::glutReshapeFunc(::doReshapeFunc);
  ::glutMotionFunc(::doMotionFunc);
  ::glutMouseFunc(::doMouseFunc);
  ::glutMainLoop();

  return 0;
}

void ::runMainLoop(int ms)
{
  glutPostRedisplay();
  ::glutTimerFunc(ms, ::runMainLoop, ms);
}

void ::doDisplay(void)
{
  engine.Draw();
}

void ::doKeyboard(unsigned char key, int x, int y)
{
  engine.Keyboard(key, x, y);
}

void ::doSpecialFunc(int key, int x, int y)
{
  engine.SpecialFunc(key, x, y);
}

void ::doReshapeFunc(GLsizei width, GLsizei height)
{
  engine.ReshapeFunc(width, height);
}

void ::doMotionFunc(int x, int y)
{
  engine.MotionFunc(x, y);
}

void ::doMouseFunc(int button, int state, int x, int y)
{
  engine.MouseFunc(button, state, x, y);
}
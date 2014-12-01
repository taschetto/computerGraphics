#include "WinState.h"
#include "OpenGL.h"
#include "PlayState.h"
#include "TextureManager.h"
#include "GameEngine.h"

WinState *WinState::instance = 0;

void WinState::Init()
{
}

void WinState::Cleanup()
{
}

void WinState::Pause()
{
}

void WinState::Resume()
{
}

void WinState::HandleEvents(GameEngine*)
{
}

void WinState::Draw()
{
}

void WinState::Keyboard(GameEngine* engine, unsigned char, int, int)
{
  SpecialFunc(engine, 0, 0, 0);
}

void WinState::SpecialFunc(GameEngine* engine, int, int, int)
{
  engine->ChangeState(PlayState::Instance());
  glutPostRedisplay();
}

void WinState::ReshapeFunc(GameEngine*, GLsizei width, GLsizei height)
{
}

void WinState::MotionFunc(GameEngine*, int x, int y)
{
}

void WinState::MouseFunc(GameEngine*, int button, int state, int x, int y)
{
}
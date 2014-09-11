#include "InitialState.h"
#include "OpenGL.h"
#include "GameEngine.h"
#include "PlayState.h"

InitialState *InitialState::instance = 0;

void InitialState::Init()
{
}

void InitialState::Cleanup()
{
}

void InitialState::Pause()
{
}

void InitialState::Resume()
{
}

void InitialState::HandleEvents(GameEngine*)
{
}

void InitialState::Draw()
{
}

void InitialState::Keyboard(GameEngine* engine, unsigned char, int, int)
{
  SpecialFunc(engine, 0, 0, 0);
}

void InitialState::SpecialFunc(GameEngine* engine, int, int, int)
{
  engine->ChangeState(PlayState::Instance());
  ::glutPostRedisplay();
}
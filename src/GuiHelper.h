#ifndef KORTSPEL_GUI_HELPER
#define KORTSPEL_GUI_HELPER

#include "raylib.h"

enum class MouseState {NO, OVER, CLICKED};

struct Button
{
  Rectangle   pos;
  MouseState  state = MouseState::NO;
  int clickState = 0;
};

void PaintButton(const Button& button);
bool CheckButton(const Vector2& p, Button& button);

#endif

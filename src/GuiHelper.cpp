#include "GuiHelper.h"

#include <cstring>
#include <algorithm>

void PaintButton(const Button& button)
{
  //Button
  switch(button.state)
  {
   case MouseState::NO:
     DrawRectangleRec(button.pos, LIME);
     break;
   case MouseState::CLICKED:
     DrawRectangleRec(button.pos, GOLD);
     break;
   case MouseState::OVER:
     DrawRectangleRec(button.pos, GRAY);
     break;
  }
  if(button.clickState == 1)
  {
    DrawRectangleRec(button.pos, BLUE);
    DrawCircle(button.pos.x+button.pos.width/2, button.pos.y+button.pos.height/2, std::min(button.pos.width, button.pos.height)/2-4, BLACK);
    DrawCircle(button.pos.x+button.pos.width/2, button.pos.y+button.pos.height/2, std::min(button.pos.width, button.pos.height)/2-8, BLUE);
  }
  if(button.clickState == 2)
  {
    DrawRectangleRec(button.pos, RED);
    DrawLineEx({button.pos.x, button.pos.y}, {button.pos.x+button.pos.width, button.pos.y+button.pos.height}, 2, BLACK);
    DrawLineEx({button.pos.x+button.pos.width, button.pos.y}, {button.pos.x, button.pos.y+button.pos.height}, 2, BLACK);
  }
 }

bool CheckButton(const Vector2& p, Button& button)
{
  if (CheckCollisionPointRec(p, button.pos))
  {
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
    {
      button.state = MouseState::CLICKED;
    }
    else
    {
      button.state = MouseState::OVER;
    }
    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
    {
      return true;
    }
  }
  else
  {
    button.state = MouseState::NO;
  }
  return false;
}

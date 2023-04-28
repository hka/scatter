#include "raylib.h"
#include "screens.h"

#include <memory>
#include <stdio.h>
#include <string>

constexpr const char* PROGRAM_NAME = "raylib-sample";

namespace
{
void UpdatePaintFrame();
void ChangeToScreen(Screen::GameScreen screen);
}

int main(void)
{
  InitWindow(options.screenWidth, options.screenHeight, PROGRAM_NAME);

  currentScreen = std::make_unique<TitleScreen>();

  SetTargetFPS(options.fps);

  // Main game loop
  while (!WindowShouldClose())    // Detect window close button or ESC key
  {
    UpdatePaintFrame();
  }
  CloseWindow();
  return 0;
}

namespace
{
void ChangeToScreen(Screen::GameScreen screen)
{
  if(screen == currentScreen->GetEnum())
  {
    return;
  }

  switch(screen)
  {
   case Screen::GameScreen::TITLE:
     currentScreen = std::make_unique<TitleScreen>();
     break;
   case Screen::GameScreen::NOSCREEN:
     currentScreen = nullptr;
     break;
   default:
     break;
  }
}

void UpdatePaintFrame(void)
{
  currentScreen->Update();
  ChangeToScreen(currentScreen->Finish());

  if(currentScreen == nullptr){ return; }

  BeginDrawing();

  ClearBackground(RAYWHITE);

  currentScreen->Paint();

  EndDrawing();

}
} //anonymous namespace

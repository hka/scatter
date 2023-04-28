#ifndef KORTSPEL_SCREENS_H
#define KORTSPEL_SCREENS_H

#include "raylib.h"

#include <stdlib.h>
#include <string>
#include <memory>
#include <vector>
#include <random>

#include "GuiHelper.h"

struct GameOptions
{
  int screenWidth = 1280;
  int screenHeight = 720;
  int fps = 30;
};

class Screen
{
 public:
  enum class GameScreen { TITLE,
                          NOSCREEN };
  virtual void Update() = 0;
  virtual void Paint() = 0;
  virtual GameScreen Finish() = 0;
  virtual GameScreen GetEnum() = 0;
};

struct Data
{
  double x;
  double y;
};

class TitleScreen : public Screen
{
 public:
  TitleScreen();
  ~TitleScreen();
  void Update();
  void Paint();
  GameScreen Finish();
  GameScreen GetEnum(){return Screen::GameScreen::TITLE;}
 private:
  GameScreen m_finishScreen;
  std::vector<Button> m_buttons;
  Image m_screenImage;
  Texture m_screenTexture;
  int m_plotWidth;
  int m_plotHeight;
  std::vector<Color> m_pixels;
  std::vector<size_t> m_bins;
  std::vector<Data> m_data;
  double m_xlim[2];
  double m_ylim[2];

  std::mt19937 m_rng;
  std::normal_distribution<double> m_ndist;
  int m_triesSinceLastUpdate;
};

// Globals
extern std::unique_ptr<Screen> currentScreen;
extern GameOptions options;
#endif

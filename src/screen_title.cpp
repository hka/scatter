#include "screens.h"

#include "GuiHelper.h"

TitleScreen::TitleScreen()
{
  m_finishScreen = Screen::GameScreen::TITLE;

  m_rng = std::mt19937(4);
  m_ndist = std::normal_distribution<double>(0.0,2.0);

  m_plotWidth = 640;
  m_plotHeight = 640;
  m_pixels.resize(m_plotWidth*m_plotHeight);
  m_bins.resize(m_pixels.size());

  m_screenImage = { .data = m_pixels.data(), .width = m_plotWidth, .height = m_plotHeight, .mipmaps = 1, .format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8 };
  m_screenTexture = LoadTextureFromImage(m_screenImage);

  m_data.resize(1000000);
  m_xlim[0] = -10;
  m_xlim[1] = 10;
  m_ylim[0] = -10;
  m_ylim[1] = 10;
  double xc = 0;
  double yx = 0;
  for(size_t ii = 0; ii < m_data.size(); ++ii)
  {
    m_data[ii] = {m_ndist(m_rng), m_ndist(m_rng)};
  }
  m_triesSinceLastUpdate = 0;
}

TitleScreen::~TitleScreen()
{
}

void TitleScreen::Update()
{
  Vector2 mousePoint = GetMousePosition();
  int scroll = (int)GetMouseWheelMove();
  if(scroll)
  {
    if(scroll > 0)
    {
      m_xlim[0] += 0.2;
      m_xlim[1] -= 0.2;
      m_ylim[0] += 0.2;
      m_ylim[1] -= 0.2;
      if(m_xlim[0] > m_xlim[1])
      {
        m_xlim[0] = -0.1;
        m_xlim[1] = 0.1;
      }
      if(m_ylim[0] > m_ylim[1])
      {
        m_ylim[0] = -0.1;
        m_ylim[1] = 0.1;
      }
    }
    else
    {
      m_xlim[0] -= 0.2;
      m_xlim[1] += 0.2;
      m_ylim[0] -= 0.2;
      m_ylim[1] += 0.2;
    }
    double binWidth = (m_xlim[1]-m_xlim[0])/m_plotWidth;
    double binHeight = (m_ylim[1]-m_ylim[0])/m_plotHeight;

    int fps = GetFPS();
    if(fps < 30)
    {
      ++m_triesSinceLastUpdate;
      if(m_triesSinceLastUpdate < 5)
      {
        return;
      }
    }

    m_triesSinceLastUpdate = 0;
    //clear bins
    for(size_t ii = 0; ii < m_bins.size(); ++ii)
    {
      m_bins[ii] = 0;
    }
    size_t maxBinIx = 0;
    for(size_t ii = 0; ii < m_data.size(); ++ii)
    {
      int x = std::round((m_data[ii].x - m_xlim[0])/binWidth);
      int y = std::round((m_data[ii].y - m_ylim[0])/binHeight);
      if(x < 0 || y < 0 || x >= m_plotWidth || y >= m_plotHeight)
      {
        continue;
      }
      ++m_bins[y*m_plotWidth + x];
      maxBinIx = m_bins[y*m_plotWidth + x] > m_bins[maxBinIx] ? y*m_plotWidth + x : maxBinIx;
    }
    double scaleValue = 255./m_bins[maxBinIx];
    for(size_t ii = 0; ii < m_pixels.size(); ++ii)
    {
      m_pixels[ii].a = std::round(m_bins[ii]*scaleValue);
    }
    UpdateTexture(m_screenTexture, m_pixels.data());
  }
}

void TitleScreen::Paint()
{
  DrawRectangle(0, 0, options.screenWidth, options.screenHeight, GREEN);

  DrawFPS(5, 5);
  DrawTexture(m_screenTexture, (options.screenWidth-m_plotWidth)/2, (options.screenHeight-m_plotHeight)/2, WHITE);
}

Screen::GameScreen TitleScreen::Finish()
{
  return m_finishScreen;
}

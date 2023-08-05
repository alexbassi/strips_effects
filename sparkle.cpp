#include "sparkle.h"
namespace glitter
{
#define RISE  0
#define FALL  1
#define WAIT  2
#define COMPLETED 3

Sparkle::Sparkle()
{
  m_Brightness = 0;
  m_Step = RISE;  
}
/////////////////////////////////////////
void Sparkle::Setup(int Index, neoPixel *Strip)
{
  m_Strip = Strip;
  m_LedIndex = Index;
  m_Speed = 40;//random(10, 30);  
  m_StartTime = millis();
}
////////////////////////////////////////
bool Sparkle:: Render()
{
  if(millis()<(m_StartTime+m_Speed)) return false;
  switch(m_Step)
  {
    case RISE:
      Rise();
      break;
    case FALL:
      Fall();
      break;
    case WAIT:
      Wait();
      break;
    default:
    case COMPLETED:
      //
      break;    
  }
  return true;
}
////////////////////////////////////////
bool Sparkle::Completed()
{
  return m_Step == COMPLETED;
}
////////////////////////////////////////
void  Sparkle::Rise()
{
  m_Brightness+=3;

  if(m_Brightness >= m_MaxBrightness)
  {
    m_Brightness = m_MaxBrightness;
    m_Step = FALL;
  }
  Apply();
}
void Sparkle::Apply()
{
  colorObj tempColor;
  tempColor.setColor(0, 128, 255);
  tempColor.blend(&black, 100-m_Brightness);
  m_Strip->setPixelColor(m_LedIndex, &tempColor);   
  m_StartTime = millis();
}
void  Sparkle::Fall()
{
  m_Brightness--;
  if(m_Brightness <= m_OffLevel)
  {
    m_Brightness = m_OffLevel;
    m_Step = WAIT;
    m_Speed = 1000; // 1 sec pause
  }
  Apply();  
}
void  Sparkle::Wait()
{
  m_Step = COMPLETED;
}
}
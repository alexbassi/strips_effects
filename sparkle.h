#ifndef sparkleH
#define sparkleH

#include "neoPixel.h"
namespace glitter
{
  
class Sparkle
{
  protected:
    int m_LedIndex;
    int m_Brightness;   
    int m_MaxBrightness;
    int m_OffLevel;
    int m_Step;
    unsigned long m_StartTime;
    int m_Speed;
    neoPixel * m_Strip;
    void Rise();
    void Fall();
    void Wait();
    void Apply();
  public:
    Sparkle();
    void Setup(int Index, neoPixel *Strip);
    void LightSettings(int MaxBrightness, int OffLevel) {       
       m_OffLevel = OffLevel;
       m_MaxBrightness = random(5, MaxBrightness);       
    }
    bool Render();
    bool Completed();
    int MyIndex() {
      return m_LedIndex;
    }
};
}
#endif
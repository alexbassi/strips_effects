#ifndef ring_bounceH
#define ring_bounceH

#include "strips_effects.h"

#define LED_COLOR   0,128,255
namespace ring
{


class RingBounce : public effects::Effect
{  
  private:
  colorObj  fadeColor;
  int value;
	unsigned long startTime;
	int m_PulseSpeed;
	int m_NumLeds;	
  neoPixel *m_pixels;
  int m_Step;
	void DrawRise();
	void DrawFade();
	void DrawWait();
public:
  RingBounce(int LedsCount, neoPixel * NeoPixel){  
    m_pixels = NeoPixel;
    m_NumLeds = LedsCount; 
		value = 100;
    fadeColor.setColor(LED_COLOR);
    fadeColor.blend(&black, 0);
		m_Step = 0;// STEP _RISE
  }
	void Setup(int Speed);
  void SetAllLeds();
  void Draw();  
	void Clear() {
		m_pixels->clear();
		m_pixels->show();
	}
};
}//namepsace ring
#endif
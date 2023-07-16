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
  
public:
  RingBounce(int LedsCount, neoPixel * NeoPixel){  
    m_pixels = NeoPixel;
    m_NumLeds = LedsCount; 
		value = 0;
    fadeColor.setColor(LED_COLOR);
    fadeColor.blend(&black, 0);
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
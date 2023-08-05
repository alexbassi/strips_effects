#ifndef waves_effectH
#define waves_effectH
#include "strips_effects.h"

// to be removed
#include <colorObj.h>
#include <neoPixel.h>
//
namespace waves
{
class WavesEffect : public effects::Effect
{
	protected:
		neoPixel	*m_Pixels;
		int m_LedsCount;
		unsigned long m_startTime;
	int m_PulseSpeed;
	int m_CurrentValue;
	int m_MaxValue;
	int m_Direction;
  int m_EmptyPulses;
	void Rise();
	void Fade();
  void Stay();
  void applyColor();
	public:
		WavesEffect(neoPixel * Strip, int LedsCount) {
			m_Pixels = Strip;
			m_LedsCount = LedsCount;		
			Setup();			
		}
		void Setup();
		void Draw();
		void Clear();		
};
}
#endif
#ifndef strips_effectsH
#define strips_effectsH
#include "effects_modes_type.h"
//#include <functional>
#include <colorObj.h>
#include <neoPixel.h>

//typedef std::function<void()> TOnEvent;

namespace effects
{

class Effect
{
	/*private:
		void NullEvent() {};
	protected:
		TOnEvent m_OnBegin;
		TOnEvent m_OnEnd;
		*/
  public:  
		/*TEffect() {
			m_OnBegin = NullEvent;
			m_OnEnd = NullEvent;
		}*/
		virtual ~Effect(){};
		virtual void Draw() = 0;
		virtual void Clear() = 0;		
		
};

class Factory
{
	public:
		static Effect * CreateEffect(int Mode, neoPixel * NeoPixel, int LedsCount);
};
	
}
#endif
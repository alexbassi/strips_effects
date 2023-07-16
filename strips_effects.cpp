#include "strips_effects.h"
#include "effects_modes_type.h"
#include "ring_bounce.h"
#include "async_strips.h"
namespace effects
{
Effect * Factory::CreateEffect(int Mode, neoPixel * NeoPixel, int LedsCount)
{
	Effect * temp;
	switch(Mode)
	{
		case EnumEffectsModes::BOUNCE: 
		{
			ring::RingBounce * bounce = new ring::RingBounce(LedsCount, NeoPixel);
			bounce->Setup(25);
			temp = bounce;
		}break;
		case EnumEffectsModes::ASYNC_STRIPS:
		{
			strips::TAsyncStrips * asyncStrips = new strips::TAsyncStrips(NeoPixel, LedsCount);
			temp = asyncStrips;
		}
	}
	return temp;
}
}
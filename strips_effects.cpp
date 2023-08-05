#include "strips_effects.h"
#include "effects_modes_type.h"
#include "ring_bounce.h"
#include "async_strips.h"
#include "waves_effect.h"
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
		}break;
		case EnumEffectsModes::WAVES:
		{
			waves::WavesEffect * wavesEffect = new waves::WavesEffect(NeoPixel, LedsCount);
			temp = wavesEffect;
		}break;
	}
	return temp;
}
}
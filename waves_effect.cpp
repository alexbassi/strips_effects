#include "waves_effect.h"
//#include "strips_effects.h"
//#include "effects_modes_type.h"
#define SPEED 	40
#define MIN_VAL	1
#define MAX_VAL 10
#define EMPTY   30

#define DIR_RISE	0
#define DIR_FADE 	1
#define DIR_STAY  2

namespace waves{
void WavesEffect::Setup()
{
  m_EmptyPulses = 0;
	m_PulseSpeed = SPEED;
	m_startTime = millis();
	randomSeed(analogRead(0));
	m_CurrentValue = 0;
	m_MaxValue = random(MIN_VAL+5, MAX_VAL);
	m_Direction = DIR_RISE;
}
void WavesEffect::Draw()
{
	if(millis()<(m_startTime+m_PulseSpeed)) return;
	switch(m_Direction)
	{
		case DIR_RISE: Rise(); break;
		case DIR_FADE: Fade(); break;
    case DIR_STAY: Stay(); break;
	}
	/*
	 case rise: increase value
	 if value == max change to decrease mode
	*/
	
	/*
	case fade decrease value
	if value == min generate new MAX and switch to increase
	*/
	m_startTime = millis();	
}
void WavesEffect::Rise()
{
	m_CurrentValue+=3;
  if(m_CurrentValue>=m_MaxValue)
  {
    m_Direction = DIR_FADE;
    m_CurrentValue =m_MaxValue;
  } 
  applyColor();
}
void WavesEffect::Stay()
{
  m_CurrentValue = MIN_VAL;
  applyColor();
  m_EmptyPulses++;
  if(m_EmptyPulses == EMPTY) {
    m_EmptyPulses = 0;
    m_Direction = DIR_RISE;
    m_MaxValue = random(MIN_VAL, MAX_VAL);
  }
}
void WavesEffect::applyColor()
{ 
	colorObj col;
	col.setColor(0, m_CurrentValue, m_CurrentValue);
	col.blend(&black, 0);//100-m_CurrentValue);
	m_Pixels->shiftPixels(false);
  m_Pixels->setPixelColor(m_LedsCount-1, &col);
  m_Pixels->show();
}
void WavesEffect::Fade()
{
  m_CurrentValue-=1;
  if(m_CurrentValue <= MIN_VAL)
  {
    m_CurrentValue = MIN_VAL;
    m_Direction = DIR_STAY;
  }
  applyColor();
}
void WavesEffect::Clear()
{
  m_Pixels->clear();
}
}
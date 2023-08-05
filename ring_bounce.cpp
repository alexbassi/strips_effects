#include "ring_bounce.h"
#define GLOBAL_BRIGHTNESS	100

#define MIN_VALUE	5
#define MAX_VALUE 50

#define STEP_RISE 0
#define STEP_FADE 1
#define STEP_WAIT 2
namespace ring{

//----------------------------
void RingBounce::Setup(int Speed)  
{
	m_pixels->begin();    
	startTime = millis();
	m_PulseSpeed = Speed;
	m_pixels->setBrightness(GLOBAL_BRIGHTNESS);	
}
//--------------------------------------
/*void RingBounce::TurnOffAll() 
{
	for(int i=0;i<m_NumLeds;i++)
	{      
		m_pixels->clear();     
		m_pixels->show();  
	}
}*/
//----------------------------------
void RingBounce::SetAllLeds()
{
	for(int i=0;i<m_NumLeds;i++) 
	{      
	  m_pixels->setPixelColor(i, &fadeColor);
	}
	m_pixels->show();
}
//----------------------------------
void RingBounce::Draw()
{
		switch(m_Step)
		{
			case STEP_RISE:	DrawRise(); break;
			
			case STEP_FADE: DrawFade();	break;
				
			case STEP_WAIT: DrawWait();	break;
		}
}
void RingBounce::DrawRise()
{
	if(millis()<(startTime+m_PulseSpeed)) return;

	value-=3;
	// rise complete. set for next step.
	if(value<=(100-MAX_VALUE)) {
		m_Step = STEP_FADE;		
		value = 100 - MAX_VALUE;
	}	
	
	fadeColor.setColor(0, 128, 255);
	fadeColor.blend(&black, value);      
	SetAllLeds();
	startTime = millis();	
}
void RingBounce::DrawFade()
{
	if(millis()<(startTime+m_PulseSpeed)) return;

	value++;
	fadeColor.setColor(0, 128, 255);
	fadeColor.blend(&black, value);      
	SetAllLeds();
	startTime = millis();
	if(value == (100-MIN_VALUE)) {
		m_Step = STEP_WAIT;
	}
}
void RingBounce::DrawWait()
{
	if(millis()<(startTime+1200)) return;	
	m_Step = STEP_RISE;
	value = 100-MIN_VALUE;
	startTime = millis();
}
/*void RingBounce::SyncFlash(bool Enabled)
{
	if(Enabled == true)
	{
		value = 0;
		Flash();
	}
}*/
} // namespace ring
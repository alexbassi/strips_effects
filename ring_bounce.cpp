#include "ring_bounce.h"
namespace ring{

//----------------------------
void RingBounce::Setup(int Speed)  
{
	m_pixels->begin();    
	startTime = millis();
	m_PulseSpeed = Speed;
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
	if(millis()<(startTime+m_PulseSpeed)) return;

	if(value==100) value = 0;
	else
	  value++;
	fadeColor.setColor(0, 128, 255);
	fadeColor.blend(&black, value);      
	SetAllLeds();
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
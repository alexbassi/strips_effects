#include "async_strips.h"

unsigned char brightness_values[PULSE_STEPS] = {3,10,20,35,30,15,5,0};

namespace strips
{
void PulseLedClass::DrawMyself(int LedIndex)
{
	Serial.print("DrawMyself(");
	Serial.print(LedIndex);
	Serial.println(")\n---------");
	// if required to draw myself before the beginning of the stripe...
	if(LedIndex < 0) return;

	// if required to draw myself after the end of the stripe...
	if(LedIndex > (m_totalLeds-1)) return;
	
  // The led index is inverted
	m_mainStripe->setPixelColor(m_totalLeds - LedIndex -1, m_colorObj);      

}
//--------------------------------------------------
void PulseLedClass::DrawNextPulse(int NextLedIndex)
{
	PulseLedClass * nextPulse = (PulseLedClass*)next;
	if(next)
		nextPulse->DrawPulse(NextLedIndex);       
}	

void FirstPulseLedClass::Log()
{
	Serial.print("SetDelay = ");
	Serial.print(m_timeDelay);
	Serial.println(" mS");           
	Serial.print("StartLedIndex = ");
	Serial.print(currentLedIndex);
	Serial.println("");
}    
void FirstPulseLedClass::DrawPulse(int LedIndex)
{    
	//Log();          
	if(millis() < (lastTime + m_timeDelay)) return ;
	Serial.print("FirstPulseLedClass::DrawPulse(");
	Serial.print(currentLedIndex);
	Serial.println(") then DrawNextPulse(currentLedIndex-1)");
	
	DrawMyself(currentLedIndex);
	DrawNextPulse(currentLedIndex-1);
		
	lastTime = millis();  
	currentLedIndex++;     
	m_mainStripe->show();      
}

void NextPulseLedClass::DrawPulse(int LedIndex) 
{
		DrawMyself(LedIndex);
		DrawNextPulse(LedIndex -1);        
}

void LastPulseLedClass::DrawPulse(int LedIndex) 
{
	DrawMyself(LedIndex);
	//notify if I am the last pixel of the pulse 
	// and the last pixel on the whole stripe 
	if(LedIndex == (m_totalLeds-1) ) 
			m_Owner->DrawingCompleted();
			
	DrawNextPulse(LedIndex -1);        
}

void MainStripClass::Setup(colorObj *ledColor)
{
	m_DrawingComplete = false;
	
	for(int i=0;i<PULSE_STEPS;i++)
	{
		pulseArray[i].setColor(ledColor);//0, 255, 255);
		pulseArray[i].blend(&black, 100-brightness_values[i]);
		linkListObj *listObj;
		if(i==0)
		{
			FirstPulseLedClass * fp = new FirstPulseLedClass(m_mainStripe);
			fp->SetDelay(m_SpeedDelay);
			fp->SetTotalLeds(m_LedsCount);
			fp->SetColorObj(&(pulseArray[i]));
			fp->SetOwner(this);          
			fp->SetStartLedIndex(0);
			listObj = fp;
		}
		else if(i == (PULSE_STEPS-1))
		{
			LastPulseLedClass *lp = new LastPulseLedClass(m_mainStripe);
			lp->SetTotalLeds(m_LedsCount);
			lp->SetColorObj(&(pulseArray[i]));      
			lp->SetOwner(this);
			listObj = lp;
		}
		else
		{
			NextPulseLedClass * np = new NextPulseLedClass(m_mainStripe);      
			np->SetTotalLeds(m_LedsCount);
			np->SetColorObj(&(pulseArray[i]));      
			np->SetOwner(this);
			listObj = np;
		}
		this->addToEnd(listObj);
			
	}
	//m_mainStripe->setBrightness(GLOBAL_BRIGHTNESS);
	m_mainStripe->clear();
	m_mainStripe->show();
}
bool MainStripClass::Run()
{
	bool notifyCompleted = false;
	FirstPulseLedClass * pulseLed = (FirstPulseLedClass *)this->getFirst();
	
	pulseLed->DrawPulse(0);      
	if(m_DrawingComplete == true)
	{        
		if(m_waitClass.Wait(m_RestartDelay) == true)
		{
			m_DrawingComplete = false;
			notifyCompleted = true;
			pulseLed->SetStartLedIndex(0);        
		}        
	}  
	return notifyCompleted;
}

#define STRIPE_DELAY 25

TAsyncStrips::TAsyncStrips(neoPixel * Strip, int LedsCount)
{
	m_mainEffect = new strips::MainStripClass(Strip, STRIPE_DELAY, 200, LedsCount);
	m_secondEffect = new strips::MainStripClass(Strip, STRIPE_DELAY, 500, LedsCount);
	m_thirdEffect = new strips::MainStripClass(Strip, STRIPE_DELAY, 780, LedsCount);
	
	colorObj color1(0,255,255);
	colorObj color2(64,255,64);
	colorObj color3(255,0,255);
	
	m_mainEffect->Setup(&color1);
  m_secondEffect->Setup(&color2);
  m_thirdEffect->Setup(&color3);
}
TAsyncStrips::~TAsyncStrips()
{
	delete m_mainEffect;
	delete m_secondEffect;
	delete m_thirdEffect;
}
		
void TAsyncStrips::Draw()
{
		bool bCompleted = m_mainEffect->Run();
		bCompleted |= m_secondEffect->Run();
		bCompleted |= m_thirdEffect->Run();
		//return bCompleted;
		/*
		will link m_OnEnd();
		*/
}
void TAsyncStrips::Clear()
{
	m_Strip->clear();
	m_Strip->show();
}
}
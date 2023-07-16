#ifndef async_stripsH
#define async_stripsH
#include <colorObj.h>
#include <neoPixel.h>
#include <lists.h>
#include "strips_effects.h"
#define PULSE_STEPS 8
namespace strips
{
class IPulseOwner
{
  public:
    virtual void DrawingCompleted() = 0;
};

class PulseLedClass : public linkListObj
{
  protected:
  int m_totalLeds;
  colorObj  *m_colorObj;  //int m_myLed;
  IPulseOwner *m_Owner;
  neoPixel * m_mainStripe;
  
  public:
    PulseLedClass(neoPixel *NeoPixelStripe){
      m_mainStripe = NeoPixelStripe;      
    };
    void SetTotalLeds(int TotalLeds){
      m_totalLeds = TotalLeds;      
    }
    void SetColorObj(colorObj *colorObjItem){
      m_colorObj = colorObjItem;
    }
		
    virtual void DrawPulse(int LedIndex) = 0;
		
    void DrawMyself(int LedIndex);
    void DrawNextPulse(int NextLedIndex);
    void SetOwner(IPulseOwner * Owner) {
      m_Owner = Owner;
    }
    
} ;

class FirstPulseLedClass :public PulseLedClass
{
  protected:
    int currentLedIndex;
    unsigned long m_timeDelay;
    unsigned long lastTime;  
    unsigned long lastTimeWait;
  public:
    FirstPulseLedClass(neoPixel * NeoPixel) : PulseLedClass(NeoPixel)
    {
      lastTime = millis();      
      Serial.println("FirstPulseLedClass creation");    
    }
    void SetDelay(unsigned long TimeDelay){
       m_timeDelay = TimeDelay;
    }
    void SetStartLedIndex(int LedIndex){
        currentLedIndex = LedIndex;          
    }

    void Log();    
    void DrawPulse(int LedIndex);
    void Reset(){
      currentLedIndex = 0;  
      Serial.println("Reset currentLedIndex");
    }

};
class NextPulseLedClass : public PulseLedClass
{
  public:
    NextPulseLedClass (neoPixel * NeoPixel) : PulseLedClass(NeoPixel){};
    void DrawPulse(int LedIndex);
};
class LastPulseLedClass : public PulseLedClass
{
  
  public:   
    LastPulseLedClass(neoPixel * NeoPixel) : PulseLedClass(NeoPixel) {};
    void DrawPulse(int LedIndex);
};

class WaitClass
{
    protected:
    unsigned long lastTimeWait;

    public:
    WaitClass()
    {
      lastTimeWait = 0;
    }

    bool Wait(unsigned long timeToWait)
    {        
        if(lastTimeWait == 0) 
          lastTimeWait = millis();
        if(millis() > (lastTimeWait + timeToWait)) 
        {
          lastTimeWait = 0;  
          return true;
        }
        return false;
    }
};
//------------------------------------------------------


class MainStripClass : public linkList, public IPulseOwner
{
  protected:
    colorObj pulseArray[PULSE_STEPS];
    neoPixel * m_mainStripe;
    bool m_DrawingComplete;
    WaitClass m_waitClass;
    unsigned long m_SpeedDelay;
    unsigned long m_RestartDelay;
    int m_LedsCount;
  public:
    MainStripClass(neoPixel *pixelObjs, unsigned long SpeedDelay, unsigned long RestartDelay, int LedsCount)
    
    {
      m_DrawingComplete = false;  
      m_mainStripe = pixelObjs;
      m_RestartDelay = RestartDelay;
      m_SpeedDelay = SpeedDelay;
      m_LedsCount = LedsCount;
    }
    void DrawingCompleted(){
      m_DrawingComplete = true;
    }
    void Setup(colorObj *ledColor);
    bool Run();
    
};


class TAsyncStrips : public effects::Effect
{
	protected:
	neoPixel *m_Strip;
	MainStripClass * m_mainEffect;
	MainStripClass * m_secondEffect;
	MainStripClass * m_thirdEffect;
	public:
		TAsyncStrips(neoPixel * Strip, int LedsCount);
		~TAsyncStrips();
		
		void Draw();
		void Clear();
};
}
#endif
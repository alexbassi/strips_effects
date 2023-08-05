#ifndef glitter_effectH
#define glitter_effectH
#include <colorObj.h>
#include <neoPixel.h>
#include "sparkle.h"
#include "strips_effects.h"
#include <list>
namespace glitter
{

typedef std::list<Sparkle> SparklesList;
class GlitterEffect: public effects::Effect 
{
  protected:

    int m_LedsCount;
    neoPixel *m_Strip;
    void Feed();
    void Render();
    SparklesList m_SparklesList;
    int m_MaxBrightness, m_MaxSparkles, m_OffLevel;

  public:
    GlitterEffect(neoPixel *Strip, int LedsCount );
    void Draw();
		void Clear();
    void Setup(int MaxSparkles, int MaxBrightness, int OffLevel) {
      m_MaxSparkles = MaxSparkles;
      m_MaxBrightness = MaxBrightness;
      m_OffLevel = OffLevel;
    }	
};

}
#endif
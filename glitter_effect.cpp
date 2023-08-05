#include "glitter_effect.h"
#include "led_index_generator.h"
#include <vector>



namespace glitter
{
GlitterEffect::GlitterEffect(neoPixel *Strip, int LedsCount) 
{
      m_Strip = Strip;
      m_LedsCount = LedsCount;
}
void GlitterEffect::Draw()
{
  Feed();
  Render();
}
//////////////////////////
void GlitterEffect::Clear()
{
  m_Strip->clear();
  for(int i=0;i<m_LedsCount;i++)
  {
    colorObj tempColor;
    tempColor.setColor(0, 128, 255);
    tempColor.blend(&black, 100-m_OffLevel);  
    m_Strip->setPixelColor(i, &tempColor);    
  }
  m_Strip->show();

}
//////////////////////////
void GlitterEffect::Feed()
{
  std::vector<int> exclusionList;
  SparklesList::iterator sparkleItem = m_SparklesList.begin();
  SparklesList::iterator endOfList = m_SparklesList.end();
  
  // first get all currently busy leds
  for(auto &item : m_SparklesList)
  {
    exclusionList.push_back(item.MyIndex());
  }

  // then feed the list
  while(sparkleItem != endOfList)
  {
    if(sparkleItem->Completed()==true)
    {
      sparkleItem = m_SparklesList.erase(sparkleItem);  
    }
    else
      sparkleItem++;
  }
  if(m_SparklesList.size() < m_MaxSparkles)
  {
    Sparkle newSparkle;
    ledgen::generator generator(m_LedsCount);

    newSparkle.Setup(generator.get(exclusionList), m_Strip);
    newSparkle.LightSettings(m_MaxBrightness, m_OffLevel );
    m_SparklesList.push_back(newSparkle);
  }
}
//////////////////////////
void GlitterEffect::Render()
{
    bool updateAvailable = false;
    for (auto & sparkle : m_SparklesList)
    {
      updateAvailable |= sparkle.Render();
    }
    if(updateAvailable == true)
      m_Strip->show();

}

}
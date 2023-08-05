#ifndef led_index_generatorH
#define led_index_generatorH
#include <vector>
#define SECTORS   3
namespace ledgen
{
class generator
{
  protected:
    int m_totalLeds;
  public:
    generator(int TotalLeds){
      m_totalLeds = TotalLeds;
      randomSeed(analogRead(0));      
    }
    int get(){
        return random(0,m_totalLeds);
    }

    int get(std::vector<int> &ExclusionList) {
      int item = -1;
      do{
        item = get();
        for(auto index : ExclusionList){
          if(index == item){
            item = -1;
            break;
          }
        }
      }while(item == -1);
      return item; 
    }
};
}
#endif
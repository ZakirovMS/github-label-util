#ifndef LABELSETTER_HPP
#define LABELSETTER_HPP
#include <string>
#include <list>

class labelSetter
{
  void setLabelByName(std::string name, std::string label);
  std::list< std::string > checkLabelByName(std::string name);
};

#endif

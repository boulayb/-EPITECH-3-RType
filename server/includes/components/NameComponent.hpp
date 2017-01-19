//
// Created by coodie_d on 12/23/16.
//

#ifndef RTYPE_NAMECOMPONENT_HH
#define RTYPE_NAMECOMPONENT_HH

# include<string>

# include "Component.hpp"

class NameComponent: public Component
{
private:
  std::string _name;

public:
  NameComponent(std::string const &id, std::string const &name = nullptr)
  : Component(id), _name(name)
  {

  }
  ~NameComponent()
  {

  }

  std::string const       &getConstName(void) const
  {
    return _name;
  }

  std::string             &getName(void)
  {
    return _name;
  }

  void                    setName(std::string const &name)
  {
    _name = name;
  }

};

#endif //RTYPE_NAMECOMPONENT_HH

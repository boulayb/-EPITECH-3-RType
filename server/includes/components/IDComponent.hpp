//
// Created by coodie_d on 12/23/16.
//

#ifndef RTYPE_IDCOMPONENT_HPP
#define RTYPE_IDCOMPONENT_HPP

# include "Component.hpp"

class IDComponent: public Component
{
private:
  int               _componentID;

public:
  IDComponent(std::string const &idName, int const id = 0)
  : Component(idName), _componentID(id)
  {

  }
  ~IDComponent()
  {

  }

  int               getComponentID(void) const
  {
    return _componentID;
  }

  int               &getComponentID(void)
  {
    return _componentID;
  }

  void              setComponentID(int componentID)
  {
    _componentID = componentID;
  }
};

#endif //RTYPE_IDCOMPONENT_HPP

//
// Created by coodie_d on 12/26/16.
//

#ifndef RTYPE_CONNECTEDCOMPONENT_HPP
#define RTYPE_CONNECTEDCOMPONENT_HPP

# include "Component.hpp"

class ConnectedComponent: public Component
{
private:
  bool      _connected;
public:
  ConnectedComponent(std::string const &id)
  : Component(id), _connected(false)
  {
  }

  ~ConnectedComponent()
  {

  }

  void        setConnected(bool connected)
  {
    _connected = connected;
  }

  bool        isConnected(void) const
  {
    return (_connected);
  }
};

#endif //RTYPE_CONNECTEDCOMPONENT_HPP

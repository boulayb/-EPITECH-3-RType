//
// Created by coodie_d on 12/26/16.
//

#ifndef RTYPE_HOSTCOMPONENT_HPP
#define RTYPE_HOSTCOMPONENT_HPP

# include "Component.hpp"

class HostComponent: public Component
{
private:
  int           _clientID;
  std::string   &_name;

public:
  HostComponent(std::string const &id, int const clientID, std::string &name)
  : Component(id), _clientID(clientID), _name(name)
  {

  }

  ~HostComponent()
  {

  }

  int         getClientID(void) const
  {
    return (_clientID);
  }

  std::string &getName(void) const
  {
    return (_name);
  }
};

#endif //RTYPE_HOSTCOMPONENT_HPP

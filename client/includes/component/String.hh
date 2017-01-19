//
// Created by salnik_a on 27/12/16.
//

#ifndef RTYPE_STRING_HH
#define RTYPE_STRING_HH

#include "../../../ecs/Component.hpp"

class String : public Component
{
public:
  String(const std::string &id);

  std::string     &getString();
  void    setString(const std::string &s);

private:
  std::string _string;
};


#endif //RTYPE_STRING_HH

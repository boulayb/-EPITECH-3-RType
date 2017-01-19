#ifndef WHEELS_HPP_
# define WHEELS_HPP_

# include <string>
# include "Component.hpp"

class                   Wheels : public Component
{
  int                   _wheels;

 public:
  Wheels(const std::string& id, int wheels = 4) :
    Component(id), _wheels(wheels)
  {
  }

  ~Wheels()
  {
  }

  inline void           setWheels(int wheels)
  {
    _wheels = wheels;
  }

  inline int            getWheels(void) const
  {
    return (_wheels);
  }
};

#endif /* !WHEELS_HPP_ */

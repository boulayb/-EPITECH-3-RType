#ifndef DELAY_HPP_
# define DELAY_HPP_

# include <string>
# include "Component.hpp"

class                           Delay : public Component
{
  int                           _delay;

 public:
  Delay(const std::string& id, int delay = 1) :
    Component(id), _delay(delay)
  {
  }

  ~Delay()
  {
  }

  inline void                   setDelay(int delay)
  {
    _delay = delay;
  }

  inline int                    getDelay(void) const
  {
    return (_delay);
  }
};

#endif /* !DELAY_HPP_ */

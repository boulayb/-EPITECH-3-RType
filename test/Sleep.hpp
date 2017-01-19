#ifndef SLEEP_HPP_
# define SLEEP_HPP_

# include <iostream>
# include <unistd.h>
# include "Delay.hpp"
# include "Engine.hpp"
# include "System.hpp"
# include "Entity.hpp"

class                   Sleep : public System
{
 public:
  Sleep() :
    System("Sleep")
  {
  }

  virtual ~Sleep()
  {
  }

  virtual bool          doAction(Entity& entity)
  {
    int                 delay;
    try
      {
        delay = entity.getComponents().getObject<Delay>("Delay").getDelay();
      }
    catch (const std::out_of_range& err)
      {
        return (false);
      }
    std::cout << "Sleeping for " << delay << " second" << std::endl;
    sleep(delay);
    return (true);
  }
};

#endif /* !SLEEP_HPP_ */

#ifndef DRIVE_HPP_
# define DRIVE_HPP_

# include <iostream>
# include "Name.hpp"
# include "Color.hpp"
# include "Engine.hpp"
# include "System.hpp"
# include "Wheels.hpp"
# include "Entity.hpp"

class                   Drive : public System
{
 public:
  Drive() :
    System("Drive")
  {
  }

  virtual ~Drive()
  {
  }

  virtual bool          doAction(Entity& entity)
  {
    ECSMap<Component> &components = entity.getComponents();
    try
      {
        std::cout << "I am driving a "
          << components.getObject<Color>("Color").getColor() << " "
          << components.getObject<Name>("Name").getName() << " on "
          << components.getObject<Wheels>("Wheels").getWheels()
          << " wheels!" << std::endl;
      }
    catch (const std::out_of_range& err)
      {
        return (false);
      }
    return (true);
  }
};

#endif /* !DRIVE_HPP_ */

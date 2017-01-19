#ifndef PRESENT_HPP_
# define PRESENT_HPP_

# include <iostream>
# include "Age.hpp"
# include "Name.hpp"
# include "Engine.hpp"
# include "System.hpp"
# include "Entity.hpp"

class                   Present : public System
{
 public:
  Present() :
    System("Present")
  {
  }

  virtual ~Present()
  {
  }

  virtual bool          doAction(Entity& entity)
  {
    ECSMap<Component> &components = entity.getComponents();
    try
      {
        Name &name = components.getObject<Name>("Name");
        Age &age = components.getObject<Age>("Age");
        age.setAge(age.getAge() + 1);
        if (age.getAge() >= 30)
          {
            std::cout << "Oh no! " << name.getName()
                      << " is dying!" << std::endl;
            engine::Instance().deleteEntity(entity);
            // makeDomotro(engine::Instance(), "Damatra");
          }
        else
          {
            std::cout << "My name is "
                      << name.getName() << " and I am "
                      << age.getAge() << " years old!"
                      << std::endl;
          }
      }
    catch (const std::out_of_range& err)
      {
        return (false);
      }
    return (true);
  }
};

#endif /* !PRESENT_HPP_ */

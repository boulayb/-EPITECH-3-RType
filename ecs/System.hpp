#ifndef SYSTEM_HPP_
# define SYSTEM_HPP_

# include <string>
# include "Id.hpp"
# include "Engine.hpp"
# include "Entity.hpp"
# include "ECSVector.hpp"

class                                   Engine;

class                                   System : public Id,
                                                 public ECSVector<Entity>
{
 public:
  System(const std::string& id) :
    Id(id), ECSVector()
  {
  }

  System(const std::string& id, const ECSVector::vector& groups) :
    Id(id), ECSVector(groups)
  {
  }

  virtual ~System()
  {
  }

  bool                                  run()
  {
    for (Entity* entity : this->getVector())
      this->doAction(*entity);
    return (true);
  }

  virtual bool                          doAction(Entity& entity) = 0;
};

#endif /* !SYSTEM_HPP_ */

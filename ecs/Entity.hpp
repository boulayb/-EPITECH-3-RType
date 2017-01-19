#ifndef ENTITY_HPP_
# define ENTITY_HPP_

# include <string>
# include <iostream>
# include "Id.hpp"
# include "ECSMap.hpp"
# include "Entity.hpp"
# include "System.hpp"
# include "Component.hpp"
# include "ECSVector.hpp"
# include "ECSVector.hpp"
# include "ECSMultiMap.hpp"

class                                   System;

class                                   Entity : public Id
{
  ECSMap<Component>                     _components;
  ECSMap<System>                        _systems;
  ECSVector<Entity>                     _parents;
  ECSMultiMap<Entity>                   _childs;

 public:
  Entity(const std::string& id,
         const ECSMap<Component>::map& components = ECSMap<Component>::map(),
         const ECSMap<System>::map& systems = ECSMap<System>::map(),
         const ECSVector<Entity>::vector& parents =
         ECSVector<Entity>::vector(),
         const ECSMultiMap<Entity>::map& childs =
         ECSMultiMap<Entity>::map()) :
    Id(id), _components(components), _systems(systems),
    _parents(parents), _childs(childs)
  {
  }

  ~Entity()
  {
  }

  inline ECSMap<Component>&             getComponents(void)
  {
    return (_components);
  }

  inline ECSMap<System>&                getSystems(void)
  {
    return (_systems);
  }

  inline ECSVector<Entity>&             getParents(void)
  {
    return (_parents);
  }

  inline ECSMultiMap<Entity>&           getChilds(void)
  {
    return (_childs);
  }
};

#endif /* !ENTITY_HPP_ */

#ifndef ENGINE_HPP_
# define ENGINE_HPP_

# include <string>
# include <chrono>
# include "System.hpp"
# include "Entity.hpp"
# include "ECSMap.hpp"
# include "ECSVector.hpp"
# include "Component.hpp"
# include "Singleton.hpp"
# include "EntityAPI.hpp"
# include "ObjectsPool.hpp"

class                                   System;

using frame_period = std::chrono::duration<long long, std::ratio<1, 120>>;

class                                   Engine : public ECSVector<System>
{
 public:
  typedef ObjectsPool<Entity>           EntityPool;
  typedef ObjectsPool<Component>        ComponentPool;

 private:
  bool                                  _running;
  EntityPool                            _entities;
  ComponentPool                         _components;
  ECSMap<EntityAPI>                     _librairies;

 public:
  Engine();
  ~Engine();

  bool                                  run(void);
  void                                  updateLibrairies(void);
  void                                  deleteEntity(Entity& entity);
  Entity&                               getEntity(const std::string& id);
  Entity&                               getUsedEntity(const std::string& id);
  Entity&                               createEntity(const std::string& name);
  bool                                  addToSystem(Entity& entity,
                                                    const std::string& id);
  bool                                  removeFromSystem(const Entity& entity,
                                                         const std::string& id);

  inline bool                           isRunning(void) const
  {
    return (_running);
  }

  inline void                           setRunning(bool running)
  {
    _running = running;
  }

  inline EntityPool&                    getEntities(void)
  {
    return (_entities);
  }

  inline ComponentPool&                 getComponents(void)
  {
    return (_components);
  }

  template<typename T>
  T&                                    getComponent(const std::string& id)
  {
    return (_components.getObjects<T>(id));
  }
};

typedef Singleton<Engine> engine;

#endif /* !ENGINE_HPP_ */

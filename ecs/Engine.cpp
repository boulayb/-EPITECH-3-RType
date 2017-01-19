#include <string>
#include <chrono>
#include "Engine.hpp"
#include "System.hpp"
#include "Entity.hpp"
#include "ECSMap.hpp"
#include "DLLoader.hpp"
#include "EntityAPI.hpp"
#include "ECSVector.hpp"
#include "Singleton.hpp"

Engine::Engine() :
  ECSVector(), _running(true)
{
  this->updateLibrairies();
}

Engine::~Engine()
{
  _librairies.empty();
}

bool                    Engine::run(void)
{
  auto prev = std::chrono::high_resolution_clock::now();
  auto current = prev;
  auto difference = current-prev;

  while (_running == true)
    {

      while (difference < frame_period{1})
        {
          current = std::chrono::high_resolution_clock::now();
          difference = current-prev;
        }


        for (System* sys : this->getVector())
        {
          try
            {
              sys->run();
            }
          catch (std::exception &e)
            {
              return (false);
            }
        }
      using hr_duration = std::chrono::high_resolution_clock::duration;
      prev = std::chrono::time_point_cast<hr_duration>(prev + frame_period{1});
      difference = current-prev;
    }
  return (true);
}

bool                    Engine::addToSystem(Entity& entity,
                                            const std::string& id)
{
  if (this->idExist(id) == true)
    {
      if (this->getObject(id).addObject(entity) == false)
        return (false);
      return (entity.getSystems().addObject(this->getObject(id)));
    }
  return (false);
}

void                    Engine::deleteEntity(Entity& entity)
{
  for (const ECSMap<System>::pair& pair : entity.getSystems().getMap())
    pair.second->removeObject(entity);
  ECSVector<Entity>& parents = entity.getParents();
  for (Entity* parent : parents.getVector())
    {
      parent->getChilds().removeObject(entity);
    }
  parents.empty();
  ECSMultiMap<Entity>& childs = entity.getChilds();
  for (ECSMultiMap<Entity>::pair child : childs.getMap())
    {
      child.second->getParents().removeObject(*child.second);
    }
  childs.empty();
}

bool                    Engine::removeFromSystem(const Entity& entity,
                                                 const std::string& id)
{
  return (this->getObject(id).removeObject(entity));
}

Entity&                 Engine::getEntity(const std::string& id)
{
  return (_entities.getObjects<Entity>(id));
}

Entity&                 Engine::getUsedEntity(const std::string& id)
{
  return (_entities.getUsedObjects<Entity>(id));
}


Entity&                 Engine::createEntity(const std::string& name)
{
  return (_librairies.getObject<EntityAPI>(name).createEntity());
}

void                    Engine::updateLibrairies(void)
{
  DLLoader<EntityAPI>   loader;

  _librairies.setMap(loader.getEntitiesByName());
}

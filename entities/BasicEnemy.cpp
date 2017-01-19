//
// Created by dimitri on 12/27/16.
//

#include <string>
#include "Graphics.hh"
#include "Position.hh"
#include "Engine.hpp"
#include "Entity.hpp"
#include "EntityAPI.hpp"

void                    functionPattern(PositionComponent &, PositionComponent const&)
{
}

Entity&                 EntityAPI::createEntity(void)
{

  Engine& engine = engine::Instance();
  int sizeX = 92;
  int sizeY = 125;

  PositionComponent& pos = engine.getComponent<PositionComponent>("Position");
  pos.setX(0);
  pos.setY(180);
  PositionComponent& posOriginal = engine.getComponent<PositionComponent>("OriginalPosition");
  posOriginal.setX(0);
  posOriginal.setY(0);
  SpriteComponent& sprite = engine.getComponent<SpriteComponent>("Sprite");
  sprite.setSprite("ressources/images/dat.png", 0, 0, sizeX, sizeY);
  Size& size = engine.getComponent<Size>("Size");
  size.setX(sizeX);
  size.setY(sizeY);
  Speed& VSpeed = engine.getComponent<Speed>("VerticalSpeed");
  VSpeed.setSpeed(0);
  Speed& HSpeed = engine.getComponent<Speed>("HorizontalSpeed");
  HSpeed.setSpeed(-2);
  Entity& mob = engine.getEntity("Mob");
  MobPattern& pattern = engine.getComponent<MobPattern>("MobPattern");
  std::function<void(PositionComponent&, PositionComponent const&)> function = functionPattern;
  pattern.setPattern(function);

  mob.getComponents().addObject({&pos, &sprite, &HSpeed, &VSpeed, &size, &pattern, &posOriginal});

  return (mob);
}

extern "C"
EntityAPI               *entryPoint()
{
  return (new EntityAPI);
}

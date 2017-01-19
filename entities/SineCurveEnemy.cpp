#include <string>
#include "Graphics.hh"
#include <cmath>
#include "Engine.hpp"
#include "Entity.hpp"
#include "EntityAPI.hpp"

void                    functionPattern(PositionComponent &current, PositionComponent const &origin)
{
  float amplitude = 50.0;
  float delta = origin.getY() - current.getY();

  if (delta <= - amplitude)
    current.setDirection(false);
  else if (delta >= amplitude)
    current.setDirection(true);
  if (current.getDirection())
    current.setY(current.getY() + 1.2);
  else if (!current.getDirection())
    current.setY(current.getY() - 1.2);
}

Entity&                 EntityAPI::createEntity(void)
{
  int sizeX = 144;
  int sizeY = 250;

  Engine& engine = engine::Instance();
  PositionComponent& pos = engine.getComponent<PositionComponent>("Position");
  pos.setX(0);
  pos.setY(180);
  PositionComponent& posOriginal = engine.getComponent<PositionComponent>("OriginalPosition");
  posOriginal.setX(0);
  posOriginal.setY(0);
  SpriteComponent& sprite = engine.getComponent<SpriteComponent>("Sprite");
  sprite.setSprite("ressources/images/theboss.png", 0, 0, sizeX, sizeY);
  Size& size = engine.getComponent<Size>("Size");
  size.setX(sizeX);
  size.setY(sizeY);
  Speed& VSpeed = engine.getComponent<Speed>("VerticalSpeed");
  VSpeed.setSpeed(0);
  Speed& HSpeed = engine.getComponent<Speed>("HorizontalSpeed");
  HSpeed.setSpeed(-0.5);
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

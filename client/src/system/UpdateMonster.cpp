//
// Created by salnik_a on 27/12/16.
//

#include <component/Speed.hh>
#include <Graphics.hh>
#include <SystemFactory.hh>
#include "../../includes/system/UpdateMonster.hh"


void UpdateMonster::shot(Entity& entity)
{
  ECSMap<Component> &components = entity.getComponents();
  PositionComponent& pos = engine::Instance().getComponent<PositionComponent>("Position");
  pos.setX(components.getObject<PositionComponent>("Position").getX());
  pos.setY(components.getObject<PositionComponent>("Position").getY() + components.getObject<Size>("Size").getY() / 2);
  SpriteComponent& sprite = engine::Instance().getComponent<SpriteComponent>("Sprite");
  sprite.setSprite("ressources/images/bullet.png", 0, 0, 75, 75);
  Size& size = engine::Instance().getComponent<Size>("Size");
  size.setX(25);
  size.setY(25);
  Loop& loop = engine::Instance().getComponent<Loop>("Loop");
  loop.setLoop(false);
  Speed& VSpeed = engine::Instance().getComponent<Speed>("VerticalSpeed");
  VSpeed.setSpeed(0);
  Speed& HSpeed = engine::Instance().getComponent<Speed>("HorizontalSpeed");
  HSpeed.setSpeed(-3);
  Entity& bullet = engine::Instance().getEntity("Bullet");
  bullet.getComponents().addObject({&pos, &sprite, Singleton<SystemFactory>::Instance().getWin(), &HSpeed, &VSpeed, &size, &loop});
  engine::Instance().addToSystem(bullet, "Move");
  engine::Instance().addToSystem(bullet, "Draw");
}

bool  UpdateMonster::doAction(Entity &entity)
{
  static int time = 0;
  ECSMap<Component> &components = entity.getComponents();
  try
  {
    Speed &Hspeed = components.getObject<Speed>("HorizontalSpeed");
    PositionComponent &pos = components.getObject<PositionComponent>("Position");
    PositionComponent &Opos = components.getObject<PositionComponent>("OriginalPosition");
    MobPattern& patter = components.getObject<MobPattern>("MobPattern");
    Collide& collide = components.getObject<Collide>("Collide");
    patter.getPatternResult(pos, Opos);
    pos.setX(pos.getX() + Hspeed.getSpeed());
    if (time > 160)
    {
      this->shot(entity);
      time = 0;
    }
    time++;
    if (pos.getX() < 0 || collide.isCollided() == true)
    {
      engine::Instance().removeFromSystem(entity, "UpdateMonster");
      engine::Instance().removeFromSystem(entity, "Draw");
      engine::Instance().deleteEntity(entity);
    }
  }
  catch (const std::out_of_range& err)
  {
    return false;
  }
  return true;
}

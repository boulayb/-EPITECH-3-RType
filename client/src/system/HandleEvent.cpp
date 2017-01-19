//
// Created by salnik_a on 25/12/16.
//

#include <SystemFactory.hh>

void HandleEvent::Shot(Entity& entity)
{
  ECSMap<Component> &components = entity.getComponents();
  PositionComponent& pos = engine::Instance().getComponent<PositionComponent>("Position");
  pos.setX(components.getObject<PositionComponent>("Position").getX() + 80);
  pos.setY(components.getObject<PositionComponent>("Position").getY() + 0);
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
  HSpeed.setSpeed(10);
  Entity& bullet = engine::Instance().getEntity("Bullet");

  bullet.getComponents().addObject({&pos, &sprite, &components.getObject<WindowComponent>("Window"), &HSpeed, &VSpeed, &size, &loop});

  engine::Instance().addToSystem(bullet, "Move");
  engine::Instance().addToSystem(bullet, "Collider");
  engine::Instance().addToSystem(bullet, "Draw");
}

bool    HandleEvent::doAction(Entity &entity)
{
  static bool canShoot = true;

  ECSMap<Component> &components = entity.getComponents();
  try
    {
      WindowComponent& win = components.getObject<WindowComponent>("Window");
      Event& event = components.getObject<Event>("Event");

      while(win.get_win()->pollEvent(event.getEvent()))
        {
          if (event.getEvent().type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
              win.get_win()->close();
              engine::Instance().setRunning(false);
            }
          if (event.getEvent().type == sf::Event::KeyPressed)
            {
              if (event.getEvent().key.code == sf::Keyboard::Space && canShoot)
                {
                  canShoot = !canShoot;
                  if (engine::Instance().getEntities().isKey("Player"))
                    {
                      Entity& entit = engine::Instance().getEntities().getUsedObjects<Entity>("Player");
                      this->Shot(entit);
                    }
                }
            }
          if (event.getEvent().type == sf::Event::KeyReleased)
            {
              if (event.getEvent().key.code == sf::Keyboard::Space)
                canShoot = !canShoot;
            }
        }
  //    if (engine::Instance().getEntities().isKey("Player"))
     // {
       // Entity& entit = engine::Instance().getEntities().getUsedObjects<Entity>("Player");
//        Collide& collide = entit.getComponents().getObject<Collide>("Collide");
        /*if (collide.isCollided() == true)
          engine::Instance().setRunning(false);*/
      //}
    }
  catch (const std::out_of_range& err)
    {
      return false;
    }
  return true;

}

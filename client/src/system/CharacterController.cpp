//
// Created by salnik_a on 25/12/16.
//

#include <iostream>
#include <Graphics.hh>
#include <system/TaskManager.hh>
#include "../../includes/system/CharacterController.hh"

bool CharacterController::doAction(Entity &entity)
{
  ECSMap<Component> &components = entity.getComponents();
  try
  {
    Speed &Vspeed = components.getObject<Speed>("VerticalSpeed");
    Speed &Hspeed = components.getObject<Speed>("HorizontalSpeed");
    PositionComponent &pos = components.getObject<PositionComponent>("Position");
    Size &size = components.getObject<Size>("Size");

    Vspeed.setSpeed(0);
    Hspeed.setSpeed(0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && pos.getY() > 0)
      Vspeed.setSpeed(-4);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && pos.getY() < HEIGHT - size.getY())
      Vspeed.setSpeed(4);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && pos.getX() > 0)
      Hspeed.setSpeed(-4);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && pos.getX() < WIDTH - size.getX())
      Hspeed.setSpeed(4);
    else
    {
      return true;
    }
    TaskManager &taskManager = reinterpret_cast<TaskManager &>(engine::Instance().getObject("TaskManager"));
    taskManager.updateEntityToServer(entity, Protocol::PlayerAction::MOVE_UP);
  }
  catch (const std::out_of_range& err)
  {
    return false;
  }
  return (true);
}

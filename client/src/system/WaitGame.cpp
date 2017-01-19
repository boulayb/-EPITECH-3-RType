//
// Created by salnik_a on 28/12/16.
//

#include <system/TaskManager.hh>
#include "../../includes/system/WaitGame.hh"

bool WaitGame::doAction(Entity &entity)
{
  ECSMap<Component> &components = entity.getComponents();
  try
  {

    WindowComponent& win = components.getObject<WindowComponent>("Window");
    Event& event = components.getObject<Event>("Event");
      while (win.get_win()->pollEvent(event.getEvent()))
      {
        if (event.getEvent().type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
          win.get_win()->close();
          engine::Instance().setRunning(false);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !_alreadyPressed)
        {
          TaskManager &taskManager = reinterpret_cast<TaskManager &>(engine::Instance().getObject("TaskManager"));
          taskManager.requestStartGame();
          _alreadyPressed = true;
          return true;
        }
      }
  }
  catch (const std::out_of_range& err)
  {
    return false;
  }
  return true;
}

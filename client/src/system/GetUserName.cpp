//
// Created by salnik_a on 26/12/16.
//

#include <component/Window.hh>
#include <component/Event.hh>
#include <component/Text.hh>
#include <Graphics.hh>
#include <SystemFactory.hh>
#include <system/TaskManager.hh>
#include "system/GetUserName.hh"

bool GetUserName::doAction(Entity &entity)
{
  ECSMap<Component> &components = entity.getComponents();
  try
  {
    WindowComponent& win = components.getObject<WindowComponent>("Window");
    Event& event = components.getObject<Event>("Event");
    if (engine::Instance().getEntities().isKey("PlayerInfo"))
    {
      Entity& entity = engine::Instance().getEntities().getUsedObjects<Entity>("PlayerInfo");
      Text& text = entity.getComponents().getObject<Text>("Text");
      std::string name = text.getString();
      while (win.get_win()->pollEvent(event.getEvent()))
      {
        if (event.getEvent().type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
          win.get_win()->close();
          engine::Instance().setRunning(false);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && name.length() > 2)
        {
          String& string = engine::Instance().getComponent<String>("Username");
          string.setString(name);
          entity.getComponents().addObject(&string);
          while (win.get_win()->pollEvent(event.getEvent()));
          text.setString(name);
          Game::getIp(entity);
          return true;
        }
        else if (event.getEvent().type == sf::Event::TextEntered)
        {
          if ((event.getEvent().text.unicode > 47  &&  event.getEvent().text.unicode < 91) || (event.getEvent().text.unicode > 96  &&  event.getEvent().text.unicode < 123) || sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
          {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace) && name.length() > 0)
            {
              name = name.substr(0, name.size()-1);
            }
            else if (name.length() < 11)
              name += static_cast<char>(event.getEvent().text.unicode);
            text.setString(name);
          }
        }
      }
    }
  }
  catch (const std::out_of_range& err)
  {
    return false;
  }
  return true;
}
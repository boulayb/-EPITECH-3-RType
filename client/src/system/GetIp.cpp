//
// Created by salnik_a on 27/12/16.
//

//
// Created by salnik_a on 26/12/16.
//

#include <component/Window.hh>
#include <component/Event.hh>
#include <component/Text.hh>
#include <Graphics.hh>
#include <SystemFactory.hh>
#include "system/GetIp.hh"

bool GetIp::doAction(Entity &entity)
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
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
        {
          String& ip = engine::Instance().getComponent<String>("Ip");
          ip.setString(name);
          entity.getComponents().addObject(&ip);
          while (win.get_win()->pollEvent(event.getEvent()));
          Game::startWaitRoom(entity);
          return true;
        }
        else if (event.getEvent().type == sf::Event::TextEntered)
        {
          if ((event.getEvent().text.unicode >= '0'  &&  event.getEvent().text.unicode <= '9')
              || sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)
              || event.getEvent().text.unicode == '.'
              || event.getEvent().text.unicode == ':')
          {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace) && name.length() > 0)
            {
              name = name.substr(0, name.size()-1);
            }
            else if (name.length() < 23)
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
//
// Created by dimitri on 12/24/16.
//

#include <system/CharacterController.hh>
#include <system/TaskManager.hh>
#include <system/UpdateMonster.hh>
#include <system/Collider.hh>
#include <system/WaitGame.hh>
#include "SystemFactory.hh"
#include "Game.hh"

SystemFactory::SystemFactory()
{

}

SystemFactory::~SystemFactory()
{

}

void SystemFactory::createText(const std::string& fontFile, const std::string& str, int size, int x, int y, int r, int g, int b, const std::string& id)
{
  Entity& textEnt = engine::Instance().getEntity(id);
  Font& font = engine::Instance().getComponent<Font>("Font");
  font.setFont(fontFile);
  Text& text = engine::Instance().getComponent<Text>("Text");
  text.setText(size, str, font);
  text.setColor(r, g, b);
  PositionComponent &pos = engine::Instance().getComponent<PositionComponent>("Position");
  pos.setX(x);
  pos.setY(y);
  engine::Instance().addToSystem(textEnt, "DrawText");
  textEnt.getComponents().addObject({&text, &pos, _win});
}

bool SystemFactory::createGraphics(std::string const &windowName, int sizeX, int sizeY)
{
  engine::Instance().addObject({new HandleEvent(), new SystemClearScreen(), new DrawSystem(), new DrawText(),  new GetUserName(), new GetIp(), new WaitGame(),new RenderSystem(),new Move(), new CharacterController(), new UpdateMonster(), new Collider()});
  WindowComponent &win = engine::Instance().getComponent<WindowComponent>("Window");
  Event &event = engine::Instance().getComponent<Event>("Event");
  _win = &win;
  try
  {
    _win->CreateWindow(windowName, sizeX, sizeY);
  }
  catch (std::exception &e)
  {
    throw e;
  }
  Entity& window = engine::Instance().getEntity("Window");
  window.getComponents().addObject({_win, &event});
  engine::Instance().addToSystem(window, "Render");
  engine::Instance().addToSystem(window, "Clear");
  return true;
}

void    SystemFactory::createBack(const std::string &filePath, int x, int y, int sizeX, int sizeY, float speed, bool loo, const std::string &loopType)
{
  PositionComponent& pos = engine::Instance().getComponent<PositionComponent>("Position");
  pos.setX(x);
  pos.setY(y);
  PositionComponent& Opos = engine::Instance().getComponent<PositionComponent>("OriginalPosition");
  Opos.setX(x);
  Opos.setY(y);
  SpriteComponent& sprite = engine::Instance().getComponent<SpriteComponent>("Sprite");
  sprite.setSprite(filePath, 0,0,sizeX,sizeY);
  Size& size = engine::Instance().getComponent<Size>("Size");
  size.setX(sizeX);
  size.setY(sizeY);
  Loop& loop = engine::Instance().getComponent<Loop>(loopType);
  loop.setLoop(loo);
  Speed& VSpeed = engine::Instance().getComponent<Speed>("VerticalSpeed");
  VSpeed.setSpeed(0);
  Speed& HSpeed = engine::Instance().getComponent<Speed>("HorizontalSpeed");
  HSpeed.setSpeed(speed);
  Entity& spriteEnt = engine::Instance().getEntity("Sprite");
  spriteEnt.getComponents().addObject({&pos, &sprite, _win, &HSpeed, &VSpeed, &size, &loop, &Opos});
  engine::Instance().addToSystem(spriteEnt, "Move");
  engine::Instance().addToSystem(spriteEnt, "Draw");
}

void    SystemFactory::createPlayer(const std::string &filePath, int x, int y, int sizeX, int sizeY)
{
  PositionComponent& pos = engine::Instance().getComponent<PositionComponent>("Position");
  pos.setX(x);
  pos.setY(y);
  SpriteComponent& sprite = engine::Instance().getComponent<SpriteComponent>("Sprite");
  sprite.setSprite(filePath, 0,0,sizeX,sizeY);
  Size& size = engine::Instance().getComponent<Size>("Size");
  size.setX(sizeX);
  size.setY(sizeY);
  Speed& VSpeed = engine::Instance().getComponent<Speed>("VerticalSpeed");
  VSpeed.setSpeed(0);
  Speed& HSpeed = engine::Instance().getComponent<Speed>("HorizontalSpeed");
  HSpeed.setSpeed(0);
  Collide& collide = engine::Instance().getComponent<Collide>("Collide");
  Entity& player = engine::Instance().getEntity("Player");
  player.getComponents().addObject({&pos, &sprite, _win, &HSpeed, &VSpeed, &size, &collide});

  engine::Instance().addToSystem(player, "CharacterController");
  engine::Instance().addToSystem(player, "Collider");
  engine::Instance().addToSystem(player, "Move");
  engine::Instance().addToSystem(player, "Draw");
}

void    SystemFactory::createOtherPlayer(int color, int x, int y, const std::string &id)
{
  (void)color;
  PositionComponent& pos = engine::Instance().getComponent<PositionComponent>("Position");
  pos.setX(x);
  pos.setY(y);
  SpriteComponent& sprite = engine::Instance().getComponent<SpriteComponent>("Sprite");
  sprite.setSprite("ressources/images/pepe.png", 0,0,128,128);
  Size& size = engine::Instance().getComponent<Size>("Size");
  size.setX(128);
  size.setY(128);
  Speed& VSpeed = engine::Instance().getComponent<Speed>("VerticalSpeed");
  VSpeed.setSpeed(0);
  Speed& HSpeed = engine::Instance().getComponent<Speed>("HorizontalSpeed");
  HSpeed.setSpeed(0);
  Collide& collide = engine::Instance().getComponent<Collide>("Collide");
  Entity& player = engine::Instance().getEntity(id);
  player.getComponents().addObject({&pos, &sprite, _win, &HSpeed, &VSpeed, &size, &collide});

  engine::Instance().addToSystem(player, "Move");
  engine::Instance().addToSystem(player, "Draw");
}


bool SystemFactory::createNetwork(std::string const &ip, unsigned short port, std::string const &name)
{
  engine::Instance().addObject({new Network(ip, port, name), new TaskManager()});

  Entity& socket = engine::Instance().getEntity("Socket");
  engine::Instance().addToSystem(socket, "Network");
  return true;
}

void SystemFactory::createMonster(const std::string & mob, int y)
{
  try
    {
      Entity& sentity = engine::Instance().createEntity(mob);
      sentity.getComponents().getObject<PositionComponent>("Position").setX(WIDTH);
      sentity.getComponents().getObject<PositionComponent>("Position").setY(y);
      sentity.getComponents().getObject<PositionComponent>("OriginalPosition").setY(y);
      Collide& collide = engine::Instance().getComponent<Collide>("Collide");
      sentity.getComponents().addObject(&collide);
      engine::Instance().addToSystem(sentity, "Draw");
      engine::Instance().addToSystem(sentity, "UpdateMonster");
      engine::Instance().addToSystem(sentity, "Collider");
    }
  catch (std::out_of_range &e)
    {
      std::cerr << "error: no entity named " << mob << " loaded." << std::endl;
    }
}

WindowComponent  *SystemFactory::getWin()
{
  return _win;
}

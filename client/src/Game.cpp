//
// Created by salnik_a on 27/12/16.
//

#include "Game.hh"
#include <system/Network.hh>
#include <system/TaskManager.hh>

void  Game::initGame()
{
  SystemFactory &factory = Singleton<SystemFactory>::Instance();
  factory.createBack("ressources/images/planet_1.png", 600, 450, 300, 300, -0.5, true, "ElemLoop");
  factory.createBack("ressources/images/planet_2.png", 300, 200, 175, 175, -0.25, true, "ElemLoop");
  factory.createBack("ressources/images/starfield.png", 0, 0, 1550, 1163, -2, true);
  factory.createBack("ressources/images/starfield.png", 1550, 0, 1550, 1163, -2, true);
  factory.createText("ressources/font.ttf", "", 40, WIDTH / 2, HEIGHT / 2 - 20, 255, 215, 0, "PlayerInfo");
  factory.createText("ressources/font.ttf", "Username:", 40, WIDTH / 2 - 240, HEIGHT / 2 - 20, 255, 0, 0, "GetUserName");
  engine::Instance().addToSystem(engine::Instance().getEntities().getUsedObjects<Entity>("Window"), "GetUserName");
}

void  Game::getIp(Entity &entity)
{
  SystemFactory &factory = Singleton<SystemFactory>::Instance();
  Entity& textInfo = engine::Instance().getEntities().getUsedObjects<Entity>("GetUserName");
  engine::Instance().removeFromSystem(engine::Instance().getEntities().getUsedObjects<Entity>("Window"), "GetUserName");
  engine::Instance().removeFromSystem(textInfo, "DrawText");
  entity.getComponents().getObject<Text>("Text").setString("127.0.0.1:4005");
  factory.createText("ressources/font.ttf", "host ip and Port:", 40, WIDTH / 2 - 400, HEIGHT / 2 - 20, 255, 0, 0, "GetUserIp");
  factory.createText("ressources/font.ttf", "format : 127.0.0.1:PORT", 25, WIDTH / 2 - 400, HEIGHT / 2 + 20, 255, 128, 0, "GetUserIp2");
  engine::Instance().addToSystem(engine::Instance().getEntities().getUsedObjects<Entity>("Window"), "GetIp");
}

void Game::startWaitRoom(Entity &entity)
{
  SystemFactory &factory = Singleton<SystemFactory>::Instance();
  Entity& textInfo = engine::Instance().getEntities().getUsedObjects<Entity>("GetUserIp");
  Entity& textInfo2 = engine::Instance().getEntities().getUsedObjects<Entity>("GetUserIp2");
  engine::Instance().removeFromSystem(entity, "DrawText");
  engine::Instance().removeFromSystem(textInfo, "DrawText");
  engine::Instance().removeFromSystem(textInfo2, "DrawText");
  engine::Instance().removeFromSystem(engine::Instance().getEntities().getUsedObjects<Entity>("Window"), "GetIp");
  factory.createText("ressources/font.ttf", "Connecting to server ...", 25, WIDTH / 2 - 400, HEIGHT / 2, 255, 128, 0, "Wait");
  Entity &playerInfo = engine::Instance().getEntities().getUsedObjects<Entity>("PlayerInfo");
  std::string &userName = playerInfo.getComponents().getObject<String>("Username").getString();
  std::string &ipData = playerInfo.getComponents().getObject<String>("Ip").getString();

  try
  {
    unsigned long i = ipData.find(":");
    std::string ip = ipData.substr(0, i);
    int port = std::stoi(ipData.substr(i + 1));
    factory.createNetwork(ip, port, userName);
  }
  catch (std::exception &e)
  {

  }
  }

void Game::waitPlay()
{
  SystemFactory &factory = Singleton<SystemFactory>::Instance();
  engine::Instance().removeFromSystem(engine::Instance().getEntities().getUsedObjects<Entity>("Wait"), "DrawText");
  engine::Instance().addToSystem(engine::Instance().getEntities().getUsedObjects<Entity>("Window"), "WaitGame");
  factory.createText("ressources/font.ttf", "Press SPACEBAR to play", 25, WIDTH / 2 - 400, HEIGHT / 2, 255, 128, 0, "Play");
}


void Game::startGame()
{
  engine::Instance().removeFromSystem(engine::Instance().getEntities().getUsedObjects<Entity>("Window"), "WaitGame");
  engine::Instance().addToSystem(engine::Instance().getEntities().getUsedObjects<Entity>("Window"), "Event");
  engine::Instance().removeFromSystem(engine::Instance().getEntities().getUsedObjects<Entity>("Play"), "DrawText");
  Singleton<SystemFactory>::Instance().createPlayer("ressources/images/pepe.png", 0, 350, 128, 128);
  //Singleton<SystemFactory>::Instance().createOtherPlayer(1, 50, 50, "Player_01");
}
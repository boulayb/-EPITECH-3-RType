//
// Created by salnik_a on 27/12/16.
//

#ifndef RTYPE_GAME_HH_HH
#define RTYPE_GAME_HH_HH

#include "SystemFactory.hh"
#include "system/GetUserName.hh"
#include "system/GetIp.hh"

class Game
{
public:
  static void initGame();
  static void getIp(Entity& entity);
  static void startWaitRoom(Entity& entity);
  static void waitPlay();
  static void startGame();
private:
  Game() {};
};

#endif //RTYPE_GAME_HH_HH

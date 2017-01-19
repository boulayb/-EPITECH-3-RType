//
// Created by coodie_d on 12/24/16.
//

#ifndef RTYPE_TASKSSYSTEM_HH
#define RTYPE_TASKSSYSTEM_HH

# include <iostream>
# include "Engine.hpp"
# include "Protocol.hpp"
# include "NetworkSystem.hh"
# include "ThreadPool.hpp"
# include "components/PacketComponent.hh"
# include "components/IDComponent.hpp"
# include "components/NameComponent.hpp"
# include "components/HostComponent.hpp"
# include "components/ConnectedComponent.hpp"
# include "components/GameLaunchedComponent.hpp"
# include "systems/StageManager.hh"

class TasksSystem: public System
{
public:
  typedef struct  Task
  {
    Protocol::rtypePacket *packet;
    int           clientID;
  }               Task;

  typedef Protocol::rtypePacket* (TasksSystem::*taskFunctions)(Task const
                                                               &task);

private:
  ThreadPool<Task>     *_threadPool;
  std::map<Protocol::Code, taskFunctions> _tasks =
          {{Protocol::Code::HANDSHAKE, &TasksSystem::handShakeTask},
           {Protocol::Code::HANDSHAKE_SUCCESS,
                                       &TasksSystem::handShakeSuccessTask},
           {Protocol::Code::CONNECTION, &TasksSystem::connectionTask},
           {Protocol::Code::DISCONNECTION, &TasksSystem::disconnectionTask},
           {Protocol::Code::START_GAME, &TasksSystem::startGameTask},
           {Protocol::Code::PLAYER_POSITION, &TasksSystem::playerPositionTask}};
  std::vector<Entity*>  _players;
  std::vector<Entity*>  _rooms;

public:
  TasksSystem() : System("EventManager")
  {
    unsigned int nbCoresAvailable = std::thread::hardware_concurrency();
    if (nbCoresAvailable == 0)
    {
      nbCoresAvailable = 4;
    }
    _threadPool = new ThreadPool<Task>(nbCoresAvailable);
  }

  ~TasksSystem()
  {

  }

  static Task          &createTask(unsigned char *data, int clientId)
  {
    Task *task = new Task;

    task->packet = reinterpret_cast<Protocol::rtypePacket *>(data);
    task->clientID = clientId;
    return *task;
  }

  void          addTask(Task &task)
  {

    _threadPool->putTaskInQueue(std::bind(&TasksSystem::assignTask, this, task),
                                task);
  }

  bool          doAction(Entity &entity)
  {
    try
    {
      auto &packet = entity.getComponents().getObject<PacketComponent &>("PacketComponent");
      TasksSystem::Task &newTask = this->createTask(reinterpret_cast<unsigned char *>
                                                    (packet.getPacket()),
                                                    packet.getClientId());
      if (newTask.packet->request == Protocol::Code::START_GAME)
      {
        std::cout << "Start Game" << std::endl;
      }

      this->addTask(newTask);
      engine::Instance().removeFromSystem(entity, "EventManager");
      return (true);
    }
    catch (std::exception &e)
    {
      return true;
    }
  }

  Entity*       findInPlayers(int clientID)
  {
    auto it = std::find_if(_players.begin(), _players.end(),
    [clientID](Entity *player)
    {
      if (player->getComponents().getObject<IDComponent>("ID").getComponentID
              () == clientID)
      {
        return (true);
      }
      else
      {
        return (false);
      }
    });
    if (it != _players.end())
    {
      return (*it);
    }
    else
    {
      return (nullptr);
    }
  }

  Entity*       findAvailableRoom()
  {
    auto it = std::find_if(_rooms.begin(), _rooms.end(),
    [](Entity *room)
    {
      if ((room->getChilds().getMap().size() > 0 && room->getChilds().getMap
              ().size() < 4
           && room->getComponents().
              getObject<GameLaunchedComponent>("Game").
              isGameLaunched() == false) || (room->getComponents().getMap()
                                                                .size() == 0))
      {
        return (true);
      }
      else
      {
        return (false);
      }
    });
    if (it != _rooms.end())
    {
      return (*it);
    }
    else
    {
      return (nullptr);
    }
  }

  Entity*       findHostInRoom(int const clientID)
  {
    auto  it = std::find_if(_rooms.begin(), _rooms.end(),
    [clientID](Entity *room)
    {
      if (room->getComponents().getObject<HostComponent>("Host").getClientID() ==
              clientID)
      {
        return (true);
      }
      else
      {
        return (false);
      }
    });

    if (it != _rooms.end())
    {
      return (*it);
    }
    else
    {
      return (nullptr);
    }
  }

  void          assignTask(Task const &task)
  {
    Engine &engine = engine::Instance();
    NetworkSystem &network = reinterpret_cast<NetworkSystem&>
    (engine.getObject("Network"));
    Protocol::rtypePacket* packet;
    if (task.packet->magicNbr == MAGIC_NUMBER)
    {
      auto it = _tasks.find(task.packet->request);
      if (it != _tasks.end())
      {
        Entity  *player = findInPlayers(task.clientID);

        if (player != nullptr)
        {
          if (task.packet->request != Protocol::Code::HANDSHAKE_SUCCESS &&
                  (player->getComponents().getObject<ConnectedComponent>
                          ("Connected").isConnected() == false))
          {
            packet = Protocol::Protocol::createPacket
                    (Protocol::Code::NOT_CONNECTED, nullptr,
                     Protocol::DataType::NONE, 0);
            network.pushTCPMessage(packet, task.clientID);
            return;
          }
        }

        packet = (this->*(it->second))(task);
        if (packet != nullptr)
        {
          network.pushTCPMessage<Protocol::rtypePacket>(packet, task.clientID);
        }
      }
      else
      {
        packet = Protocol::Protocol::createPacket
                (Protocol::Code::UNKNOWN_REQUEST, nullptr,
                 Protocol::DataType::NONE, 0);
        network.pushTCPMessage(packet, task.clientID);
      }
    }
  }

  Protocol::rtypePacket*          handShakeTask(Task const &task)
  {
    Engine &engine = engine::Instance();
    Protocol::rtypePacket   *packet = Protocol::Protocol::createPacket
            (Protocol::Code::HANDSHAKE,
             nullptr, Protocol::DataType::NONE, 0);

    Entity &player = engine.getEntity("player");
    player.getComponents().addObject(
            {new IDComponent("ID", task.clientID),
             new NameComponent("Name", "pepe"),
             new ConnectedComponent("Connected")});
    _players.push_back(&player);
    return (packet);
  }

  Protocol::rtypePacket*          handShakeSuccessTask(Task const &task)
  {
    try
    {
      Entity  *player = this->findInPlayers(task.clientID);
      player->getComponents().getObject<ConnectedComponent>("Connected")
              .setConnected
                      (true);
    }
    catch (std::exception &e)
    {
    }
    return (nullptr);
  }

  Protocol::rtypePacket*          connectionTask(Task const &task)
  {
    Engine &engine = engine::Instance();
    Protocol::rtypePacket *packet;
    try
    {
      Entity *room;

      if ((room = this->findAvailableRoom()) == nullptr)
      {
        room = &engine.getEntity("room");
        _rooms.push_back(room);
      }

      Entity  *player = this->findInPlayers(task.clientID);
      if (room->getComponents().getMap().size() == 0)
      {
        std::string *name = new std::string(reinterpret_cast<char *>(task.packet->data));
        player->getComponents().getObject<NameComponent>("Name")
                .setName(*name);
        room->getComponents().addObject(
                {new HostComponent("Host", task.clientID,
                                   player->getComponents()
                                           .getObject<NameComponent>("Name")
                                           .getName()),
                 new IDComponent("ID", 1),
                 new GameLaunchedComponent("Game")});
      }
      if (room->getChilds().getMap().size() < 4)
      {
        room->getChilds().addObject(player);
        player->getParents().addObject(room);
        packet = Protocol::Protocol::createPacket
                (Protocol::Code::CONNECTION_SUCCESS, nullptr,
                 Protocol::DataType::NONE, 0);
      }
      else
      {
        packet = Protocol::Protocol::createPacket
                (Protocol::Code::CONNECTION_ERROR, nullptr,
                 Protocol::DataType::NONE, 0);
      }
      return (packet);
    }
    catch (std::exception e)
    {
      packet = Protocol::Protocol::createPacket
              (Protocol::Code::CONNECTION_ERROR, nullptr,
               Protocol::DataType::NONE, 0);
      return (packet);
    }
  }

  Protocol::rtypePacket*          disconnectionTask(Task const &task)
  {
    (void)task;
    Protocol::rtypePacket *packet = Protocol::Protocol::createPacket
            (Protocol::Code::DISCONNECTION_SUCCESS, nullptr,
    Protocol::DataType::NONE, 0);
    return (packet);
  }

  void                             spawnEntity(std::string const &entity, int posY)
  {
    Engine &engine = engine::Instance();

    for (Entity *player : _players)
    {
      IDComponent &component = player->getComponents().getObject<IDComponent>("ID");
      Protocol::EntityLoad *load = new Protocol::EntityLoad();

      ::strcpy(load->entityName, entity.c_str());
      load->posY = posY;
      Protocol::rtypePacket *packet = Protocol::Protocol::createPacket
              (Protocol::Code::SPAWN_ENTITY, reinterpret_cast<unsigned char *>(load),
               Protocol::DataType::ENTITY_POP, sizeof(Protocol::EntityLoad));

      NetworkSystem &network = reinterpret_cast<NetworkSystem&>
      (engine.getObject("Network"));

      network.pushTCPMessage<Protocol::rtypePacket>(packet, component.getComponentID());
    }
  }

  void                            spawnPlayers(int clientId)
  {
    Engine &engine = engine::Instance();
    NetworkSystem &network = reinterpret_cast<NetworkSystem&>
    (engine.getObject("Network"));
          std::string playerName;

    for (auto &player : _players)
    {

      IDComponent &component = player->getComponents().getObject<IDComponent>("ID");
      if (component.getComponentID() != clientId)
      {
        playerName = "Player_" + std::to_string(component.getComponentID());
        Protocol::rtypePacket *packet = Protocol::Protocol::createPacket
                (Protocol::Code::SPAWN_PLAYER, reinterpret_cast<const unsigned char *>(playerName.c_str()),
                 Protocol::DataType::ENTITY_INFORMATION, playerName.size());
        network.pushTCPMessage(packet, clientId);
      }
    }
  }

  Protocol::rtypePacket*          startGameTask(Task const &task)
  {
    Protocol::rtypePacket *packet;
    Engine &engine = engine::Instance();
    NetworkSystem &network = reinterpret_cast<NetworkSystem&>
    (engine.getObject("Network"));
    Entity *room;
    Entity *player = this->findInPlayers(task.clientID);

    if (player != nullptr)
    {
      room = &player->getParents().getObject("room");
      if (room->getComponents().getObject<HostComponent>("Host").getClientID
              () == task.clientID)
      {
        packet = Protocol::Protocol::createPacket
                (Protocol::Code::GAME_STARTED, nullptr,
                 Protocol::DataType::NONE, 0);
        std::vector<Entity*> players;
        room->getChilds().getObjects<Entity>("player", players);
        for (auto all: players)
        {
          int clientID = all->getComponents().getObject<IDComponent>("ID")
                  .getComponentID();
          network.pushTCPMessage(packet, clientID);
        }
        room->getComponents().getObject<GameLaunchedComponent>("Game")
                .setGameLaunched(true);
        for (auto &player : _players)
        {
          IDComponent &component = player->getComponents().getObject<IDComponent>("ID");
          this->spawnPlayers(component.getComponentID());
        }
        reinterpret_cast<StageManager&>(engine::Instance().getObject("StageManager")).start();
        return (nullptr);
      }
      else
      {
        packet = Protocol::Protocol::createPacket
                (Protocol::Code::WAITING_FOR_HOST, nullptr,
                 Protocol::DataType::NONE, 0);
      }
    }
    return (packet);
  }

  Protocol::rtypePacket*          playerPositionTask(Task const &task)
  {
    Engine &engine = engine::Instance();
    NetworkSystem &network = reinterpret_cast<NetworkSystem&>
    (engine.getObject("Network"));
    Protocol::rtypePacket *recvPacket = reinterpret_cast<Protocol::rtypePacket*>
    (task.packet);

    Protocol::EntityInformation *copy = reinterpret_cast<Protocol::EntityInformation*>(recvPacket->data);

    std::string id = reinterpret_cast<const char *>(copy->entityType);
    id += '_' +  std::to_string(task.clientID);
    std::strcpy(reinterpret_cast<char *>(copy->entityType), id.c_str());
    for (auto &player : _players)
    {
      IDComponent &component = player->getComponents().getObject<IDComponent>("ID");

      if (task.clientID != component.getComponentID())
      {
        Protocol::rtypePacket *packet = Protocol::Protocol::createPacket
                (Protocol::Code::PLAYER_POSITION, recvPacket->data,
                 Protocol::DataType::ENTITY_INFORMATION, recvPacket->size);
        network.pushTCPMessage(packet, component.getComponentID());
      }
    }
    return (nullptr);
  }
};


#endif //RTYPE_TASKSSYSTEM_HH

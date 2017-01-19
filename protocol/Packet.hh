#ifndef PACKET_HH_
# define PACKET_HH_
# define MAGIC_NUMBER   0xDEAD
# define PACKET_SIZE    512

namespace Protocol
{
  enum class  Code : unsigned int
  {
    // Client to server
    HANDSHAKE = 0,
    CONNECTION = 1,
    DISCONNECTION = 2,

    // Game requets
    START_GAME = 3,
    SPAWN_ENTITY = 4,
    UPDATE_ENTITY = 5,
    PLAYER_POSITION = 6,
    SPAWN_PLAYER = 7,

    // Success answer
    HANDSHAKE_SUCCESS = 100,
    CONNECTION_SUCCESS = 101,
    DISCONNECTION_SUCCESS = 102,
    ENTITIES = 103,
    GAME_STARTED = 104,

    // Error answer
    NOT_CONNECTED = 200,
    CONNECTION_ERROR = 201,
    DISCONNECTION_ERROR = 202,
    WAITING_FOR_HOST = 203,

    // Unknown request
    UNKNOWN_REQUEST = 300,
  };

  enum class DataType
  {
    NONE = 0,
    CHARACTER = 1,
    ENTITY_INFORMATION = 2,
    PLAYER_EVENTS = 3,
    ENTITY_POP = 4,
  };

  struct  EntityLoad
  {
    char    entityName[50];
    int     posY;
  };

  enum class PlayerAction
  {
    MOVE_UP = 0,
    MOVE_LEFT = 1,
    MOVE_DOWN = 2,
    MOVE_RIGHT = 3,
    SHOOT = 4
  };

  struct  EntityInformation
  {
    unsigned char entityType[50];
    unsigned int  entityId;
    PlayerAction  action;
    float         posX;
    float         posY;
  };

  struct  CollisionVerification
  {
    unsigned char entity1ID[20];
    int           entity1Nbr;
    unsigned char entity2ID[20];
    int           entity2Nbr;
  };

  struct  rtypePacket
  {
    int           magicNbr;
    Code          request;
    DataType      type;
    unsigned int  size;
    unsigned char data[512];
  };
}

#endif /* !PACKET_HH_ */

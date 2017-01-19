cmake_minimum_required(VERSION 3.4)
project(rtype)

option(BUILD_CLIENT "Build Client" ON)
option(BUILD_SERVER "Build Server" ON)

set(CLIENT_NAME "rtype_client")
set(SERVER_NAME "rtype_server")

set(CLIENT_SRCDIR "client/src/")
set(SERVER_SRCDIR "server/src/")

set(INC_DIR_CLIENT "client/includes")
set(INC_DIR_SERVER "server/includes")
set(INC_DIR_DLLOADER "DLLoader/")
set(INC_DIR_ECS "ecs/")
set(INC_DIR_PROTOCOL "protocol/")
set(INC_DIR_COMPONENT "client/includes/component")

set(LIB_LINKS "-ldl -lpthread")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set (COMPONENT_SRC
	${CLIENT_SRCDIR}component/Position.cpp
		${CLIENT_SRCDIR}component/Sprite.cpp
		${CLIENT_SRCDIR}component/Speed.cpp
		${CLIENT_SRCDIR}component/Size.cpp
		${CLIENT_SRCDIR}component/MobPattern.cpp)

set(CLIENT_SOURCE_FILES
	${INC_DIR_ECS}Engine.cpp
	${CLIENT_SRCDIR}main.cpp
	${CLIENT_SRCDIR}SystemFactory.cpp
	${CLIENT_SRCDIR}component/PacketComponent.cpp
	${CLIENT_SRCDIR}component/Position.cpp
	${CLIENT_SRCDIR}component/MobPattern.cpp
	${CLIENT_SRCDIR}component/Sprite.cpp
	${CLIENT_SRCDIR}component/Window.cpp
	${CLIENT_SRCDIR}component/Loop.cpp
	${CLIENT_SRCDIR}component/Speed.cpp
	${CLIENT_SRCDIR}component/Size.cpp
	${CLIENT_SRCDIR}component/Text.cpp
	${CLIENT_SRCDIR}component/String.cpp
	${CLIENT_SRCDIR}component/Font.cpp
	${CLIENT_SRCDIR}component/Event.cpp
	${CLIENT_SRCDIR}component/Collide.cpp
	${CLIENT_SRCDIR}system/TaskManager.cpp
	${CLIENT_SRCDIR}system/ClearScreen.cpp
	${CLIENT_SRCDIR}system/GetUserName.cpp
	${CLIENT_SRCDIR}system/GetIp.cpp
	${CLIENT_SRCDIR}system/CharacterController.cpp
	${CLIENT_SRCDIR}system/HandleEvent.cpp
	${CLIENT_SRCDIR}system/Draw.cpp
	${CLIENT_SRCDIR}system/Collider.cpp
	${CLIENT_SRCDIR}system/DrawText.cpp
	${CLIENT_SRCDIR}system/Render.cpp
	${CLIENT_SRCDIR}system/Network.cpp
	${CLIENT_SRCDIR}system/Move.cpp
	${CLIENT_SRCDIR}system/UpdateMonster.cpp
	${CLIENT_SRCDIR}system/WaitGame.cpp
	${CLIENT_SRCDIR}Game.cpp)

set(SERVER_SOURCE_FILES
	${INC_DIR_ECS}Engine.cpp
	${SERVER_SRCDIR}main.cpp
	${SERVER_SRCDIR}ServerSystemFactory.cpp
	${SERVER_SRCDIR}systems/NetworkSystem.cpp
	${SERVER_SRCDIR}systems/StageManager.cpp
	${SERVER_SRCDIR}components/PacketComponent.cpp
	${SERVER_SRCDIR}ATCPMonitor.cpp
	${SERVER_SRCDIR}AUDPMonitor.cpp)

set(SERVER_SOURCE_FILES_LINUX
	${SERVER_SRCDIR}linux/TCPSocket.cpp
	${SERVER_SRCDIR}linux/TCPMonitor.cpp
	${SERVER_SRCDIR}linux/UDPSocket.cpp
	${SERVER_SRCDIR}linux/UDPMonitor.cpp)

set(SERVER_SOURCE_FILES_WIN
	${SERVER_SRCDIR}windows/TCPSocket.cpp
	${SERVER_SRCDIR}windows/TCPMonitor.cpp
	${SERVER_SRCDIR}windows/UDPSocket.cpp
	${SERVER_SRCDIR}windows/UDPMonitor.cpp)

set(SERVER_SOURCE_FILES_SYSTEMS)

add_library(BasicEnemy SHARED entities/BasicEnemy.cpp ecs/Engine.cpp ${COMPONENT_SRC})
add_library(SineCurveEnemy SHARED entities/SineCurveEnemy.cpp ecs/Engine.cpp ${COMPONENT_SRC})

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
if(WIN32)
    set(SFML_ROOT "dependancies/windows/SFML-2.3.2/lib")
	set(SFML_INCLUDE_DIR "dependancies/windows/SFML-2.3.2/include")
elseif(UNIX)
    set(SFML_ROOT "dependancies/linux/SFML-2.3.2/lib")
	set(SFML_INCLUDE_DIR "dependancies/linux/SFML-2.3.2/include")
endif()
find_package(SFML 2 REQUIRED system window graphics network audio)

target_link_libraries (BasicEnemy ${SFML_LIBRARIES})
target_link_libraries (SineCurveEnemy ${SFML_LIBRARIES})

install(TARGETS ${EXECUTABLE_NAME} DESTINATION bin)

if(WIN32)
	include_directories(${INC_DIR_DLLOADER}/win)
	set_target_properties(BasicEnemy SineCurveEnemy PROPERTIES
			LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/entities/windows"
			)
elseif(UNIX)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
	include_directories(${INC_DIR_DLLOADER}/linux)
	set_target_properties(BasicEnemy SineCurveEnemy PROPERTIES
			LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/entities/linux"
			)
endif()

include_directories(${SFML_INCLUDE_DIR})
include_directories(${INC_DIR_CLIENT})
include_directories(${INC_DIR_SERVER})
include_directories(${INC_DIR_ECS})
include_directories(${INC_DIR_PROTOCOL})
include_directories(${INC_DIR_COMPONENT})

if(BUILD_CLIENT)
  add_executable(${CLIENT_NAME} ${CLIENT_SOURCE_FILES})
  target_link_libraries(${CLIENT_NAME} ${SFML_LIBRARIES} ${LIB_LINKS})
endif()

if(BUILD_SERVER)
    if(WIN32)
	add_executable(${SERVER_NAME} ${SERVER_SOURCE_FILES}
		${SERVER_SOURCE_FILES_SYSTEMS} ${SERVER_SOURCE_FILES_WIN})
	target_link_libraries(${SERVER_NAME} -lws2_32)

    elseif(UNIX)
	add_executable(${SERVER_NAME} ${SERVER_SOURCE_FILES}
		${SERVER_SOURCE_FILES_SYSTEMS} ${SERVER_SOURCE_FILES_LINUX})
	target_link_libraries(${SERVER_NAME} ${LIB_LINKS})
    endif()
endif()

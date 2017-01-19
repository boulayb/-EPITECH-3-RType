/*
 * RenderSystem : System de gestion de la fenetre
 *
 */

#ifndef TESTSFML_RENDERSYSTEM_HH
#define TESTSFML_RENDERSYSTEM_HH


#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include "../../ecs/Component.hpp"
#include "../component/Window.hh"
#include "../../ecs/Engine.hpp"

class RenderSystem : public System
{
public:
    RenderSystem() :
        System("Render")
    {

    }

public:
    bool    doAction(Entity& entity);
};


#endif //TESTSFML_RENDERSYSTEM_HH

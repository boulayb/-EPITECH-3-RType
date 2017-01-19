#ifndef TESTSFML_SPRITECOMPONENT_HH
#define TESTSFML_SPRITECOMPONENT_HH

#include <SFML/Graphics.hpp>
#include "../../ecs/Component.hpp"
#include <iostream>

class SpriteComponent : public Component
{
public:
    SpriteComponent(const std::string &id);

    sf::Sprite  &getSprite();
    void        setSprite(const std::string &filename, int sx, int sy, int ex, int ey);
private:
    sf::Sprite  _sprite;
    sf::Texture _texture;
    void loadSprite(const std::string &filename, int sx, int sy, int ex, int ey);
};


#endif //TESTSFML_SPRITECOMPONENT_HH

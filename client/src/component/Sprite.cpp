#include "../../includes/component/Sprite.hh"

SpriteComponent::SpriteComponent(const std::string &id) : Component(id)
{

}

sf::Sprite  &SpriteComponent::getSprite()
{
    return _sprite;
}

void        SpriteComponent::setSprite(const std::string &filename, int sx, int sy, int ex, int ey)
{
    loadSprite(filename, sx, sy, ex, ey);
}

void        SpriteComponent::loadSprite(const std::string &filename, int sx, int sy, int ex, int ey)
{

    if (!_texture.loadFromFile(filename, sf::IntRect(sx, sy, ex, ey)))
    {
        std::cerr << "Cannot load " << filename << std::endl;
        return;
    }
    _sprite.setTexture(_texture);
}

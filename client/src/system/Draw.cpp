#include <SystemFactory.hh>
#include "../../includes/system/Draw.hh"

bool    DrawSystem::doAction(Entity &entity)
{
    ECSMap<Component> &components = entity.getComponents();
    try
    {
        WindowComponent *win = Singleton<SystemFactory>::Instance().getWin();
        SpriteComponent &sprite = components.getObject<SpriteComponent>("Sprite");
        PositionComponent &pos = components.getObject<PositionComponent>("Position");
        sprite.getSprite().setPosition(pos.getX(), pos.getY());
        win->get_win()->draw(sprite.getSprite());
    }
    catch (const std::out_of_range& err)
    {
        return (false);
    }
    return (true);
}

#include <iostream>
#include "../../includes/system/Render.hh"


bool    RenderSystem::doAction(Entity& entity)
{
    ECSMap<Component> &components = entity.getComponents();
    try
    {
        WindowComponent &win = components.getObject<WindowComponent>("Window");
        win.get_win()->display();
    }
    catch (const std::out_of_range& err)
    {
        return (false);
    }
    return (true);
}

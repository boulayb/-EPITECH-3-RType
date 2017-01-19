//
// Created by salnik_a on 23/12/16.
//

#include "../../includes/system/DrawText.hh"

bool DrawText::doAction(Entity &entity)
{
    ECSMap<Component> &components = entity.getComponents();
    try
    {
        WindowComponent &win = components.getObject<WindowComponent>("Window");
        Text &text = components.getObject<Text>("Text");
        PositionComponent &pos = components.getObject<PositionComponent>("Position");
        text.getText().setPosition(pos.getX(), pos.getY());
        win.get_win()->draw(text.getText());
    }
    catch (const std::out_of_range& err)
    {
        return (false);
    }
    return (true);
}

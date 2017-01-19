//
// Created by salnik_a on 25/12/16.
//

#include "Graphics.hh"

bool Move::doAction(Entity &entity)
{
    ECSMap<Component> &components = entity.getComponents();
    try
    {
        PositionComponent &pos = components.getObject<PositionComponent>("Position");

        Speed &VerticalSpeed = components.getObject<Speed>("VerticalSpeed");
        Speed &HorizontalSpeed = components.getObject<Speed>("HorizontalSpeed");

        if (components.keyExist("BackgroundLoop"))
        {
            Loop &loop = components.getObject<Loop>("BackgroundLoop");
            if (loop.getLoop() == true)
            {
                Size &size = components.getObject<Size>("Size");

                if (pos.getX() <= 0 - (int)size.getX())
                    pos.setX((int)size.getX());
            }
        }
        if (components.keyExist("ElemLoop"))
        {
            Loop &loop = components.getObject<Loop>("ElemLoop");
            if (loop.getLoop() == true)
            {
                Size &size = components.getObject<Size>("Size");
                if (HorizontalSpeed.getSpeed() < 0)
                {
                    if (pos.getX() <= 0 - (int)size.getX())
                        pos.setX(WIDTH + (int)size.getX());
                }
                else
                {
                    if (pos.getX() > HEIGHT)
                        pos.setX(0 - (int)size.getX());
                }
            }
        }

        pos.setX(pos.getX() + HorizontalSpeed.getSpeed());
        pos.setY(pos.getY() + VerticalSpeed.getSpeed());
      if (entity.getId() == "Bullet" && (pos.getX() > WIDTH || pos.getX() < 0))
      {
        engine::Instance().removeFromSystem(entity, "Move");
        engine::Instance().removeFromSystem(entity, "Draw");
        engine::Instance().deleteEntity(entity);
      }
    }
    catch (const std::out_of_range& err)
    {
        return (false);
    }
    return (true);
}
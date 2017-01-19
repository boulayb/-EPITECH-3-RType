//
// Created by salnik_a on 28/12/16.
//


#include "../../includes/system/Collider.hh"

bool  Collider::doAction(Entity& entity)
{
  ECSMap<Component> &components = entity.getComponents();
  try
  {
    PositionComponent& pos = components.getObject<PositionComponent>("Position");
    Size& size = components.getObject<Size>("Size");

    for (Entity* it : this->getVector())
    {
      if (it != &entity)
      {
        PositionComponent& targetPos = it->getComponents().getObject<PositionComponent>("Position");
        Size& targetSize = it->getComponents().getObject<Size>("Size");
        if (pos.getX() < targetPos.getX() + targetSize.getX() &&
            pos.getX() + size.getX() > targetPos.getX() &&
            pos.getY() < targetPos.getY() + targetSize.getY() &&
            size.getY() + pos.getY() > targetPos.getY())
        {
          components.getObject<Collide>("Collide").setCollide(true);
        }
        else
          components.getObject<Collide>("Collide").setCollide(false);
      }

    }

  }
  catch (const std::out_of_range& err)
  {
    return false;
  }
  return true;
}
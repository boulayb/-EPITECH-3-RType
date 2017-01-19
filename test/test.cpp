#include <list>
#include "Age.hpp"
#include "Name.hpp"
#include "Color.hpp"
#include "Drive.hpp"
#include "Sleep.hpp"
#include "Present.hpp"
#include "Delay.hpp"
#include "Engine.hpp"
#include "Wheels.hpp"
#include "Entity.hpp"
#include "Component.hpp"

static void     makeCar(Engine& engine, const std::string& brand,
                        const std::string& color, int wheels)
{
  Name& carBrand = engine.getComponent<Name>("Name");
  Color& carColor = engine.getComponent<Color>("Color");
  Wheels& carWheels = engine.getComponent<Wheels>("Wheels");

  carColor.setColor(color);
  carBrand.setName(brand);
  carWheels.setWheels(wheels);

  Entity& car = engine.getEntity("Car");

  car.getComponents().addObject({&carColor, &carBrand, &carWheels});

  engine.addToSystem(car, "Drive");
}

static void     makeDelay(Engine& engine, int delay)
{
  Delay& timerDelay = engine.getComponent<Delay>("Delay");

  timerDelay.setDelay(delay);

  Entity& timer = engine.getEntity("Timer");

  timer.getComponents().addObject(&timerDelay);

  engine.addToSystem(timer, "Sleep");
}

int                     main(void)
{
  Engine                engine;

  engine.addObject({new Drive(), new Present()});
  engine.addObjectAt(1, new Sleep());
  makeCar(engine, "Lada", "Red", 4);
  makeDelay(engine, 1);

  try
    {
      Entity &domotro = engine.createEntity("domotro");
      engine.addToSystem(domotro, "Present");
    }
  catch (std::out_of_range &e)
    {
      std::cerr << "error: no entity named domotro loaded." << std::endl;
    }

  return (engine.run());
}

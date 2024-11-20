#include "system.h"
#include "random.h"
#include "constants.h"
#include <iostream>
#include <vector>

System::System()
{
    set_info();
}

void System::set_info()
{
}

void System::Step(int command)
{
    _g.Step(command);
}

// draw graph here

void System::Draw(sf::RenderWindow &window)
{

    _g.Draw(window);
}

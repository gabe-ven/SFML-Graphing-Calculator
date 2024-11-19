#include "system.h"
#include "random.h"
#include "constants.h"
#include <iostream>
#include <vector>

System::System()
{
    Random r;

    // the shape of the object, along with its velocity, acceleration,
    // position, etc. should be part of the individual object.

    for (int i = 0; i < 20; i++)
    {
        int type = r.Next(0, 4);

        int xpos = r.Next(0, 1000);
        int ypos = r.Next(0, 1000);

        sf::Vector2f pos(xpos, ypos);
        sf::Vector2f vel(r.Next(-5, 50), r.Next(-5, 50));
        sf::Color color(r.Next(0, 255), r.Next(0, 255), r.Next(0, 255));

        sf::Shape *shape;
        int rotationSpeed = 0;

        if (type == 0)
        {
            shape = new sf::CircleShape(r.Next(5, 50));
            rotationSpeed = 2;
        }
        else if (type == 1)
        {
            shape = new sf::CircleShape(r.Next(5, 50), 3);
            rotationSpeed = 5;
        }
        else if (type == 2)
        {
            shape = new sf::CircleShape(r.Next(5, 50), 4);
            rotationSpeed = 3;
        }
        else
        {
            shape = new sf::CircleShape(r.Next(5, 50), 8);
            rotationSpeed = 1;
        }

        if (shape)
        {
            shape->setPosition(pos);
            shape->setFillColor(color);
            shapes.push_back(shape);
            velocities.push_back(vel);
            rotationSpeeds.push_back(rotationSpeed);
        }
    }
}

//------------------------------------------------------------------
//------------------------------------------------------------------

void System::Step(int command)
{

    // all this is the responsibility of the
    //  individual object:
    for (int i = 0; i < shapes.size(); ++i)
    {
        shapes[i]->move(velocities[i]);
        shapes[i]->rotate(rotationSpeeds[i]);
        sf::Vector2f pos = shapes[i]->getPosition();

        if ((pos.x) >= WORK_PANEL - 20)
            velocities[i] = sf::Vector2f(-1 * velocities[i].x, 1 * velocities[i].y);
        if (pos.x <= 0)
            velocities[i] = sf::Vector2f(-1 * velocities[i].x, 1 * velocities[i].y);
        if ((pos.y) >= SCREEN_HEIGHT - 20)
            velocities[i] = sf::Vector2f(1 * velocities[i].x, -1 * velocities[i].y);
        if (pos.y <= 0)
            velocities[i] = sf::Vector2f(1 * velocities[i].x, -1 * velocities[i].y);
    }
}

void System::Draw(sf::RenderWindow &window)
{
    window.clear();

    for (int i = 0; i < shapes.size(); ++i)
    {
        window.draw(*shapes[i]);
    }
}

#pragma once

#include <SFML/Graphics.hpp>

class Entities
{
public:
    virtual void update() = 0;
    virtual void render(sf::RenderTarget& target) = 0;
    virtual sf::FloatRect boundsGetter() = 0;
    virtual int bonusGetter() = 0;
};
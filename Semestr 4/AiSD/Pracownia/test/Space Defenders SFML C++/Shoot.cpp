#include "Shoot.hpp"
#include <iostream>

Shoot::Shoot(sf::Texture* texture, float pos_x, float pos_y, float speed, sf::Vector2f direction)
{
    this->initVariables(speed, direction);
    this->initSprite(texture, pos_x, pos_y);
}

Shoot::~Shoot() {}

void Shoot::initSprite(sf::Texture* texture, float pos_x, float pos_y)
{
    this->sprite.setTexture(*texture);
    this->sprite.setPosition(pos_x, pos_y);
}

void Shoot::initVariables(float speed, sf::Vector2f direction)
{
    this->speed = speed;
    this->direction_x = direction.x;
    this->direction_y = direction.y;
}

sf::FloatRect Shoot::boundGetter()
{
    return sprite.getGlobalBounds();
}

void Shoot::update()
{
    this->sprite.move(this->speed * this->direction_x, this->speed * this->direction_y);
}

void Shoot::render(sf::RenderTarget* target)
{
    target->draw(sprite);
}
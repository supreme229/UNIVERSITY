#include "Battery.hpp"

Battery::Battery(sf::Texture* texture, sf::Vector2f position)
{
    this->initSprite(texture, position);
    this->initVariables();
}

Battery::~Battery() {}

void Battery::initSprite(sf::Texture* texture, sf::Vector2f position)
{
    this->sprite.setTexture(*texture);
    this->sprite.setPosition(position);
    this->sprite.scale((float)0.05, (float)0.05);
}

void Battery::initVariables()
{
    this->speed = 10;
    this->recovery = 15;
}


int Battery::bonusGetter()
{
    return this->recovery;
}

sf::FloatRect Battery::boundsGetter()
{
    return this->sprite.getGlobalBounds();
}

void Battery::update()
{
    sprite.move(sf::Vector2f(speed * 0.f, speed * 1.f));
}

void Battery::render(sf::RenderTarget& target)
{
    target.draw(sprite);
}
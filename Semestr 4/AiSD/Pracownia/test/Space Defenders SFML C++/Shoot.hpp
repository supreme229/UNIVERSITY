#pragma once

#include <SFML/Graphics.hpp>

class Shoot
{
private:
    float speed;
    float direction_x;
    float direction_y;

private:
    sf::Sprite sprite;

private:
    void initSprite(sf::Texture *texture, float pos_x, float pos_y);
    void initVariables(float speed, sf::Vector2f direction);

public:
    void update();
    void render(sf::RenderTarget* target);
    sf::FloatRect boundGetter();

    Shoot(sf::Texture* texture, float pos_x, float pos_y, float speed, sf::Vector2f direction);
    ~Shoot();
};
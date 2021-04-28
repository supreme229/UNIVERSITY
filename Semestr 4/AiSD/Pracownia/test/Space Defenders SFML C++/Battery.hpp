#pragma once

#include <SFML/Graphics.hpp>
#include "Entities.hpp"

class Battery : public Entities
{
private:
    sf::Sprite sprite;
    int speed;
    int recovery;

private:
    void initSprite(sf::Texture* texture, sf::Vector2f position);
    void initVariables();

public:
    Battery(sf::Texture* texture, sf::Vector2f position);
    ~Battery();
    int bonusGetter() override;
    sf::FloatRect boundsGetter() override;
    void update() override;
    void render(sf::RenderTarget& target) override;
};
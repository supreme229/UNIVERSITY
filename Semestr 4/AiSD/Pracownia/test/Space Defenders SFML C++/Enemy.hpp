#pragma once

#include <SFML/Graphics.hpp>
#include "Entities.hpp"

class Enemy : public Entities
{
private:
    sf::CircleShape shape;
    int hp;
    int pointCount;
    int speed;
    int hpMax;
    int damage;
    int points;

private:
    void initVariables(int level);
    void initShape(sf::Vector2f position);

public:
    Enemy(sf::Vector2f position, int level);
    ~Enemy();
    void enemyDecreaseHP();
    int damageGetter();
    bool isAlive();
    int bonusGetter() override;
    sf::FloatRect boundsGetter() override;
    void update() override;
    void render(sf::RenderTarget& target) override;
};
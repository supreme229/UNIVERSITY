#pragma once

#include <SFML/Graphics.hpp>
#include "Properties.hpp"

class Player
{
private:
    int hp;
    int speed;
    float Cooldown;
    float CooldownLimit;
    Properties properties;
    sf::Sprite sprite;
    sf::Texture texture;

private:
    void initSprite();
    void initTexture();
    void initVariables();

public:
    Player();
    ~Player();
    sf::FloatRect boundsGetter();
    sf::Vector2f posGetter();
    void setPosition(float x, float y);
    bool ifCooldown();
    void decreaseHP(int damage);
    void increaseHP();
    void updatePlayer();
    void updateAttack();
    float hpGetter();
    void move(float dx, float dy);
    void renderPlayer(sf::RenderTarget& target);
};
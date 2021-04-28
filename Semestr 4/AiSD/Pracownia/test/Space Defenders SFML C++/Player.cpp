#include "Player.hpp"
#include <iostream>

Player::Player() : properties()
{
    this->initVariables();
    this->initTexture();
    this->initSprite();
}

Player::~Player() {}

void Player::initSprite()
{
    sprite.setTexture(texture); //* Setting player texture *//
    sprite.scale(0.08, 0.08);
    sprite.setPosition(properties.window_size_x / 2, properties.window_size_y);
}

void Player::initTexture()
{
    this->texture.loadFromFile("photos/spaceship_lvl_1.png");
}

void Player::initVariables()
{
    hp = 100;
    speed = 20;
    Cooldown = 7.5;
    CooldownLimit = 7.5;
}

void Player::move(float dx, float dy)
{
    this->sprite.move(sf::Vector2f(this->speed * dx, this->speed * dy));
}

void Player::decreaseHP(int damage)
{
    if (this->hp >= damage)
    {
        this->hp -= damage;
    }
    else
        this->hp = 0;
}

void Player::increaseHP()
{
    if (this->hp <= 90)
    {
        this->hp += 10;
    }
    else
        this->hp = 100;
}

float Player::hpGetter()
{
    return this->hp;
}

void Player::renderPlayer(sf::RenderTarget& target)
{
    target.draw(sprite); //* Drawing player texture
}

void Player::updateAttack()
{
    if (Cooldown < CooldownLimit)
    {
        Cooldown += 0.5f;
    }
}

void Player::updatePlayer()
{
    this->updateAttack();
}

void Player::setPosition(float x, float y)
{
    this->sprite.setPosition(x, y);
}

sf::Vector2f Player::posGetter()
{
    return sprite.getPosition();
}

sf::FloatRect Player::boundsGetter()
{
    return sprite.getGlobalBounds();
}

bool Player::ifCooldown()
{
    if (Cooldown >= CooldownLimit)
    {
        Cooldown = 0.f;
        return true;
    }
    return false;
}
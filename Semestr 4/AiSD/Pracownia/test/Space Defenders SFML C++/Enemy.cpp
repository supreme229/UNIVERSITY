#include "Enemy.hpp"
#include <iostream>

Enemy::Enemy(sf::Vector2f position, int level)
{
    this->initVariables(level);
    this->initShape(position);
}

Enemy::~Enemy() {}

void Enemy::initVariables(int level)
{
    this->pointCount = rand() % 10 + 5;
    switch (level)
    {
    case 0:
        this->hpMax = pointCount;
        this->hp = hpMax;
        this->speed = pointCount - 3;
        this->damage = pointCount - 3;
        this->points = pointCount;
        break;
    case 1:
        this->hpMax = pointCount;
        this->hp = hpMax;
        this->speed = pointCount - 3;
        this->damage = pointCount;
        this->points = pointCount;
        break;
    case 2:
        this->hpMax = pointCount * 2;
        this->hp = hpMax;
        this->speed = pointCount - 2;
        this->damage = pointCount;
        this->points = pointCount;
        break;
    default:
        this->hpMax = 0;
        this->hp = 0;
        this->speed = 0;
        this->damage = 0;
        this->points = 0;
    }
}

void Enemy::initShape(sf::Vector2f position)
{
    shape.setRadius((float)pointCount * 3.f);
    shape.setPointCount(pointCount);
    this->shape.setPosition(position);
    sf::Color color(139, 69, 19);
    this->shape.setFillColor(color);
}

void Enemy::enemyDecreaseHP()
{
    hp -= 12 + rand() % 10;
}

bool Enemy::isAlive()
{
    if (hp > 0)
    {
        return true;
    }
    return false;
}

int Enemy::bonusGetter()
{
    return this->points;
}

int Enemy::damageGetter()
{
    return this->damage;
}

sf::FloatRect Enemy::boundsGetter()
{
    return shape.getGlobalBounds();
}

void Enemy::update()
{
    shape.move(sf::Vector2f(speed * 0.f, speed * 1.f));
}

void Enemy::render(sf::RenderTarget& target)
{
    target.draw(shape);
}
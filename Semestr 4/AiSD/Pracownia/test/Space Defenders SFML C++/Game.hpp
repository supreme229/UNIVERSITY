#pragma once

#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "Shoot.hpp"
#include "Enemy.hpp"
#include "Battery.hpp"
#include "Properties.hpp"
#include "Menu.hpp"
#include <vector>
#include <map>

class Game
{
private:
    float spawnTimer;
    float spawnTimerMax;
    float spawnTimerBattery;
    float spawnTimerMaxBattery;
    int points;
    int winning_points;

    Player* player;
    sf::RenderWindow* window;

private:
    sf::Font font;
    sf::Text textHealth;
    sf::Text textPoints;
    sf::Text textGameOver;
    sf::Text textWinner;

private:
    Menu* menu;
    Properties properties;

private:
    void initText();
    void initTextures();
    void initVariables();
    void initWindow();
    

private:
    sf::Sprite backgroundSprite;
    sf::RectangleShape lifeBarShape;

private:
    std::map<std::string, sf::Texture*> textures;
    std::vector<Shoot*> shots;
    std::vector<Enemy*> enemies;
    std::vector<Battery*> batteries;

public:
    Game();
    ~Game();
    void run();
    void render();
    void renderBackground();
    void update();
    void updateKeys();
    void updatePoints();
    void updateLifeBar();
    void updateShoot();
    void updateEnemies();
    void updateBatteries();
    void updateSFEvents();
    void mapBorders();
};
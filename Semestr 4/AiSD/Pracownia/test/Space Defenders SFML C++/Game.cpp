#include "Game.hpp"
#include <iostream>
#include <string>

//* Constructors and destructors *//
Game::Game() : properties()
{
    this->player = new Player();
    this->initVariables();
    this->initWindow();
    this->initTextures();
    this->initText();
}

Game::~Game()
{
    delete this->menu;
    delete this->window;
    delete this->player;

    for (auto& t : this->textures)
    {
        delete t.second;
    }

    for (auto* t : this->shots)
    {
        delete t;
    }

    for (auto* e : this->enemies)
    {
        delete e;
    }

    for (auto* e : this->batteries)
    {
        delete e;
    }
}

void Game::initText()
{
    this->font.loadFromFile("fonts/Montserrat-Regular.ttf");
    this->textHealth.setFont(font);
    this->textHealth.setString("HEALTH");
    this->textHealth.setPosition(10.f, 10.f);
    this->textHealth.setCharacterSize(22);
    this->textPoints.setFont(font);
    this->textPoints.setCharacterSize(22);
    this->textPoints.setPosition(10.f, 70.f);
    this->textGameOver.setFont(font);
    this->textGameOver.setString("You lost...");
    this->textGameOver.setPosition(properties.window_size_x / 2.f - 115.f, properties.window_size_y / 2.f - 50.f);
    this->textGameOver.setCharacterSize(70);
    this->textGameOver.setFillColor(sf::Color::White);
    this->textWinner.setFont(font);
    this->textWinner.setString("You saved Earth!");
    this->textWinner.setPosition(properties.window_size_x / 2.f - 265.f, properties.window_size_y / 2.f - 50.f);
    this->textWinner.setCharacterSize(70);
    this->textWinner.setFillColor(sf::Color::White);
}

void Game::initTextures()
{
    this->textures["shot"] = new sf::Texture();
    this->textures["shot"]->loadFromFile("photos/bullet_1.png");
    this->textures["battery"] = new sf::Texture();
    this->textures["battery"]->loadFromFile("photos/battery.png");
    this->textures["background"] = new sf::Texture();
    this->textures["background"]->loadFromFile("photos/background.png");
    this->lifeBarShape = sf::RectangleShape(sf::Vector2f(100.f, 20.f));
    this->lifeBarShape.setFillColor(properties.getColor(life_bar));
    this->lifeBarShape.setPosition(10.f, 40.f);
    this->backgroundSprite.setTexture(*this->textures["background"]);

}

void Game::initVariables()
{
    this->points = 0;
    spawnTimer = -150.f;
    spawnTimerMax = 65.f;
    spawnTimerBattery = 0.f;
    spawnTimerMaxBattery = 350.f;
}

void Game::initWindow()
{
    this->window = new sf::RenderWindow(sf::VideoMode(Properties::window_size_x, Properties::window_size_y), properties.TITLE, sf::Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(Properties::FPS_LIMIT);
    this->menu = new Menu((float)this->window->getSize().x, (float)this->window->getSize().y);
}

void Game::run()
{
    this->menu->runMenu();

    switch (this->menu->levelGetter())
    {
    case 0:
        this->winning_points = 150;
        break;
    case 1:
        this->winning_points = 250;
        break;
    case 2:
        this->winning_points = 350;
        break;
    }

    if (!this->menu->exitGetter())
    {

        while (this->window->isOpen())
        {
            this->updateSFEvents();
            if (this->player->hpGetter() > 0)
            {
                this->update();
            }
            this->render();
        }
    }
}

void Game::renderBackground()
{
    this->window->draw(backgroundSprite);
}

void Game::render()
{
    this->window->clear();
    this->renderBackground();
    this->window->draw(textHealth);
    this->window->draw(textPoints);
    this->window->draw(lifeBarShape);
    this->player->renderPlayer(*this->window);

    for (auto* s : this->shots)
    {
        s->render(this->window);
    }

    for (auto* e : this->enemies)
    {
        e->render(*this->window);
    }

    for (auto* e : this->batteries)
    {
        e->render(*this->window);
    }

    if (this->player->hpGetter() <= 0)
    {
        window->draw(this->textGameOver);
    }

    if (this->points >= winning_points)
    {
        window->draw(this->textWinner);
    }

    this->window->display();
}

void Game::updateSFEvents()
{
    sf::Event eventSF;
    while (this->window->pollEvent(eventSF))
    {
        switch (eventSF.type)
        {
        case sf::Event::Closed:
            this->window->close();
            break;
        }
    }
}

void Game::updateShoot()
{
    int counter = 0;
    for (auto* s : this->shots)
    {
        s->update();

        if (s->boundGetter().top + s->boundGetter().height < 0.f)
        {
            delete shots.at(counter);
            this->shots.erase(this->shots.begin() + counter);
            counter--;
        }

        counter++;
    }
}

void Game::updateKeys()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        this->player->move(-1.f, 0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        this->player->move(1.f, 0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        this->player->move(0.f, -1.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        this->player->move(0.f, 1.f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && player->ifCooldown())
    {
        this->shots.push_back(new Shoot(this->textures["shot"], this->player->posGetter().x + this->player->boundsGetter().width / 2.f, this->player->posGetter().y, 5.f, sf::Vector2f(0.f, -1.f)));
    }
}

void Game::updateLifeBar()
{
    this->lifeBarShape.setScale(this->player->hpGetter() * 0.01f, 1.f);
}

void Game::mapBorders()
{
    if (player->boundsGetter().left < 0.f)
    {
        player->setPosition(0.f, player->boundsGetter().top);
    }
    else if (player->boundsGetter().left + player->boundsGetter().width > window->getSize().x)
    {
        player->setPosition(window->getSize().x - player->boundsGetter().width, player->boundsGetter().top);
    }
    if (player->boundsGetter().top < 0.f)
    {
        player->setPosition(player->boundsGetter().left, 0.f);
    }
    else if (player->boundsGetter().top + player->boundsGetter().height >= window->getSize().y)
    {
        player->setPosition(player->boundsGetter().left, window->getSize().y - player->boundsGetter().height);
    }
}

void Game::updatePoints()
{
    this->textPoints.setString("POINTS:\n" + std::to_string(this->points));
}

void Game::updateEnemies()
{
    bool enemy_shot = false;
    spawnTimer += 1.f;

    if (spawnTimer >= spawnTimerMax)
    {
        enemies.push_back(new Enemy(sf::Vector2f((float)(rand() % (window->getSize().x - 55) + 15), -100.f), this->menu->levelGetter()));
        spawnTimer = 0.f;
    }

    for (size_t counter = 0; counter < enemies.size(); counter++)
    {
        enemies[counter]->update();
        for (size_t counter2 = 0; counter2 < shots.size() && !enemy_shot; counter2++)
        {
            if (shots[counter2]->boundGetter().intersects(enemies[counter]->boundsGetter()))
            {
                delete shots.at(counter2);
                shots.erase(shots.begin() + counter2);
                enemies.at(counter)->enemyDecreaseHP();
                if (!enemies.at(counter)->isAlive())
                {
                    this->points += enemies.at(counter)->bonusGetter();
                    delete enemies.at(counter);
                    enemies.erase(enemies.begin() + counter);
                }
                enemy_shot = true;
            }
        }

        if (!enemy_shot)
        {
            if (enemies[counter]->boundsGetter().top > window->getSize().y)
            {
                delete enemies.at(counter);
                enemies.erase(enemies.begin() + counter);
            }
            else if (enemies[counter]->boundsGetter().intersects(player->boundsGetter()))
            {
                player->decreaseHP(this->enemies[counter]->damageGetter());
                delete enemies.at(counter);
                enemies.erase(enemies.begin() + counter);
            }
        }
    }
}

void Game::updateBatteries()
{
    bool battery_destroyed = false;
    spawnTimerBattery += 1.f;

    if (spawnTimerBattery >= spawnTimerMaxBattery)
    {
        batteries.push_back(new Battery(this->textures["battery"], sf::Vector2f((float)(rand() % window->getSize().x), -100.f)));
        spawnTimerBattery = 0.f;
    }

    for (size_t counter = 0; counter < batteries.size(); counter++)
    {
        batteries[counter]->update();
        for (size_t counter2 = 0; counter2 < shots.size() && !battery_destroyed; counter2++)
        {
            if (shots[counter2]->boundGetter().intersects(batteries[counter]->boundsGetter()))
            {
                delete shots.at(counter2);
                shots.erase(shots.begin() + counter2);
                delete batteries.at(counter);
                batteries.erase(batteries.begin() + counter);
                battery_destroyed = true;
            }
        }

        if (!battery_destroyed)
        {
            if (batteries[counter]->boundsGetter().top > window->getSize().y)
            {
                delete batteries.at(counter);
                batteries.erase(batteries.begin() + counter);
            }
            else if (batteries[counter]->boundsGetter().intersects(player->boundsGetter()))
            {
                player->increaseHP();
                delete batteries.at(counter);
                batteries.erase(batteries.begin() + counter);
            }
        }
    }
}

void Game::update()
{
    this->updatePoints();
    this->updateSFEvents();
    this->updateKeys();
    this->mapBorders();
    this->player->updatePlayer();
    this->updateShoot();
    std::cout << this->player->hpGetter() << std::endl;
    if (points < winning_points)
    {
        this->updateEnemies();
        this->updateBatteries();
    }
    else
    {
        int counter = 0;

        for (auto* s : this->enemies)
        {
            delete enemies.at(counter);
            enemies.erase(enemies.begin() + counter);
            counter++;
        }

        counter = 0;
        for (auto* s : this->batteries)
        {
            delete batteries.at(counter);
            batteries.erase(batteries.begin() + counter);
            counter++;
        }
    }

    this->updateLifeBar();
}
#include "Menu.hpp"
#include "Properties.hpp"
#include <iostream>



Menu::Menu(float width, float height) : properties()
{
    this->initVariables(width, height);
    this->initWindow();
    this->font.loadFromFile("fonts/Montserrat-Regular.ttf");
    this->initMenuOptions();
    this->initLevelOptions();
    this->initTutorial();
}

Menu::~Menu()
{
    delete this->window;
}

void Menu::moveUp()
{
    if (selectIndex - 1 >= 0)
    {
        menuOptions[selectIndex].setFillColor(properties.getColor(gui));
        selectIndex--;
        menuOptions[selectIndex].setFillColor(properties.getColor(chosen_menu));
    }
}

void Menu::initMenuOptions()
{
    this->menuOptions[0].setFont(font);
    this->menuOptions[0].setCharacterSize(42);
    this->menuOptions[0].setFillColor(properties.getColor(chosen_menu));
    this->menuOptions[0].setPosition(width / 6.f, height / 6.f);
    this->menuOptions[0].setString("Play");

    this->menuOptions[1].setFont(font);
    this->menuOptions[1].setCharacterSize(42);
    this->menuOptions[1].setFillColor(properties.getColor(gui));
    this->menuOptions[1].setPosition(width / 6.f, height * 2.f / 6.f);
    this->menuOptions[1].setString("Level: ");

    this->menuOptions[2].setFont(font);
    this->menuOptions[2].setCharacterSize(42);
    this->menuOptions[2].setPosition(width / 6.f, height * 3.f / 6.f);
    this->menuOptions[2].setFillColor(properties.getColor(gui));
    this->menuOptions[2].setString("How to play?");

    this->menuOptions[3].setFont(font);
    this->menuOptions[3].setCharacterSize(42);
    this->menuOptions[3].setPosition(width / 6.f, height * 4.f / 6.f);
    this->menuOptions[3].setFillColor(properties.getColor(gui));
    this->menuOptions[3].setString("Exit");
}

void Menu::initLevelOptions()
{
    this->levelOptions.setFont(font);
    this->levelOptions.setCharacterSize(42);
    this->levelOptions.setPosition(width / 6.f + 200.f, height * 2.f / 6.f);
    this->levelOptions.setFillColor(properties.getColor(normal));
    this->levelOptions.setString("< Normal >");
}

void Menu::initTutorial()
{
    this->tutorial.setFont(font);
    this->tutorial.setCharacterSize(17);
    this->tutorial.setPosition(width / 5.5f + 275.f, height * 3.f / 6.f);
    this->tutorial.setFillColor(properties.getColor(gui));
    this->tutorial.setString(properties.TUTORIAL);
}

void Menu::initVariables(float width, float height)
{
    this->width = width;
    this->height = height;
    this->selectIndex = 0;
    this->levelIndex = 1;
    this->ifExit = false;
    this->tutorialShow = false;
}

void Menu::initWindow()
{
    this->window = new sf::RenderWindow(sf::VideoMode(Properties::window_size_x, Properties::window_size_y), properties.TITLE, sf::Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(Properties::FPS_LIMIT);
    this->window->setVerticalSyncEnabled(false);
}

void Menu::moveDown()
{
    if (selectIndex + 1 < 4)
    {
        menuOptions[selectIndex].setFillColor(properties.getColor(gui));
        selectIndex++;
        menuOptions[selectIndex].setFillColor(properties.getColor(chosen_menu));
    }
}

void Menu::levelNext()
{
    if (levelIndex + 1 < 3)
    {
        levelIndex++;
        switch (levelIndex)
        {
        case 1:
            levelOptions.setString("< Normal >");
            levelOptions.setFillColor(properties.getColor(normal));
            break;
        case 2:
            levelOptions.setString("< Hard >");
            levelOptions.setFillColor(properties.getColor(hard));
            break;
        }
    }
}

void Menu::levelPrev()
{
    if (levelIndex - 1 >= 0)
    {
        levelIndex--;
        switch (levelIndex)
        {
        case 0:
            levelOptions.setString("< Easy >");
            levelOptions.setFillColor(properties.getColor(easy));
            break;
        case 1:
            levelOptions.setString("< Normal >");
            levelOptions.setFillColor(properties.getColor(normal));
            break;
        }
    }
}

void Menu::renderMenu()
{
    this->window->clear();
    for (int i = 0; i < 4; i++)
    {
        this->window->draw(menuOptions[i]);
    }
    this->window->draw(levelOptions);
    if (this->tutorialShow)
    {
        this->window->draw(tutorial);
    }
    this->window->display();
}

void Menu::updateSFEventsMenu()
{
    sf::Event eventSF;
    while (this->window->pollEvent(eventSF))
    {
        switch (eventSF.type)
        {
        case sf::Event::Closed:
            this->window->close();
            break;

        case sf::Event::KeyReleased:
            if (eventSF.key.code == sf::Keyboard::Up)
            {
                this->moveUp();
            }
            if (eventSF.key.code == sf::Keyboard::Down)
            {
                this->moveDown();
            }
            if (eventSF.key.code == sf::Keyboard::Return)
            {
                if (selectIndex == 0)
                {
                    this->window->close();
                }

                if (selectIndex == 3)
                {
                    ifExit = true;
                    this->window->close();
                }
            }
            if (eventSF.key.code == sf::Keyboard::Left && selectIndex == 1)
            {
                this->levelPrev();
            }
            if (eventSF.key.code == sf::Keyboard::Right && selectIndex == 1)
            {
                this->levelNext();
            }
            if (selectIndex == 2)
            {
                this->tutorialShow = true;
            }
            else
            {
                this->tutorialShow = false;
            }
            break;
        }
    }
}

bool Menu::exitGetter()
{
    return this->ifExit;
}

int Menu::levelGetter()
{
    return this->levelIndex;
}

void Menu::updateMenu() {}

void Menu::runMenu()
{
    while (this->window->isOpen())
    {
        this->updateSFEventsMenu();
        this->renderMenu();
        this->updateMenu();
    }
}

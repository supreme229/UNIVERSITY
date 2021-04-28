#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Properties.hpp"

class Menu
{
private:
    Properties properties;
    sf::RenderWindow* window;
    sf::Font font;
    sf::Text menuOptions[4];
    sf::Text levelOptions;
    sf::Text tutorial;
    bool ifExit;
    bool tutorialShow;
    int selectIndex;
    int levelIndex;
    float width;
    float height;

private:
    void initMenuOptions();
    void initLevelOptions(); 
    void initTutorial(); 
    void initVariables(float width, float height);
    void initWindow();

public:
    Menu(float width, float height);
    ~Menu();

    void moveUp();
    void moveDown();
    void levelNext();
    void levelPrev();

    void renderMenu();
    void updateMenu();
    bool exitGetter();
    int levelGetter();
    void updateSFEventsMenu();
    void runMenu();
};
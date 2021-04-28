#pragma once

#include <string>
#include <SFML/Graphics.hpp>

class Properties
{
public:
    static const int MENU_SIZE = 3;
    static const int FPS_LIMIT = 60;
    const static std::string TITLE;
    const static std::string TUTORIAL;
    static const int window_size_x = 800;
    static const int window_size_y = 600;

public:
    sf::Color getColor(int key);
    Properties();
    ~Properties();
};

enum
{
    asteroid,
    chosen_menu,
    easy,
    normal,
    hard,
    gui,
    life_bar
};
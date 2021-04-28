#include "Properties.hpp"

Properties::Properties() {}

Properties::~Properties() {}

const std::string Properties::TITLE = "Space Defenders";
const std::string Properties::TUTORIAL = "Save the Earth!\nControl your spaceship using WSAD\nand shoot using Spacebar. To win\nyou need to collect specific\namount of points for each level.\n   Hard - 350 pts.\n   Normal - 250 pts.\n   Easy - 150 pts.\nYour health decreases when the\nasteroids hit your spaceship or they\navoid you and hit the Earth. You can\ncollect batteries to increase your health.\nGood luck!\n";

sf::Color Properties::getColor(int key)
{
    sf::Color color;
    switch (key)
    {
    case asteroid:
        color.r = 139;
        color.g = 69;
        color.b = 19;
        return color;
        break;
    case chosen_menu:
        color.r = 245;
        color.g = 27;
        color.b = 0;
        return color;
        break;
    case easy:
        color.r = 0;
        color.g = 255;
        color.b = 0;
        return color;
        break;
    case normal:
        color.r = 249;
        color.g = 215;
        color.b = 28;
        return color;
        break;
    case hard:
        color.r = 245;
        color.g = 27;
        color.b = 0;
        return color;
        break;
    case gui:
        color.r = 255;
        color.g = 255;
        color.b = 255;
        return color;
        break;
    case life_bar:
        color.r = 0;
        color.g = 255;
        color.b = 0;
        return color;
        break;
    }
}
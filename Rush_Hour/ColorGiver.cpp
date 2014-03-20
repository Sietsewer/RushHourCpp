/* 
 * File:   ColorGiver.cpp
 * Author: Sietse
 * 
 * Created on 20 March 2014, 12:22
 */

#include "ColorGiver.h"

ColorGiver::ColorGiver(void) {
    colors.push_back(sf::Color(0, 255, 0));
    colors.push_back(sf::Color(0, 255, 255));
    colors.push_back(sf::Color(255, 255, 0));
    colors.push_back(sf::Color(255, 0, 255));
    colors.push_back(sf::Color(0, 0, 255));
    iterator = 0;
}

sf::Color ColorGiver::getColor() {
    iterator %= colors.size()-1;
    iterator++;
    return colors.at(iterator);
}
/* 
 * File:   ColorGiver.h
 * Author: Sietse
 *
 * Created on 20 March 2014, 12:22
 */

#ifndef COLORGIVER_H
#define	COLORGIVER_H

#include <iostream>
#include <string>
#include <sstream>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
using namespace sf;

class ColorGiver {
public:
    ColorGiver(void);
    sf::Color getColor();
private:
    std::vector<sf::Color> colors;
    int iterator;
};

#endif	/* COLORGIVER_H */


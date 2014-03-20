/* 
 * File:   Vehicle.h
 * Author: Wessel
 *
 * Created on 12 maart 2014, 11:32
 */

#ifndef VEHICLE_H
#define	VEHICLE_H

#include <string>
#include <sstream>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

using namespace sf;

class Vehicle {
public:
    enum Orientation {Horizontal, Vertical};
    int width;
    int height;
    int xanchor;
    int yanchor;
    sf::RectangleShape *rect;
    sf::Color color;
    Orientation orientation;
    
    Vehicle(int x, int y, int width, int height, sf::Color color);
    Vehicle();
    ~Vehicle();
    void setAnchors(int x, int y);
    void rotateVehicle();
    void move(int dist);
    bool intersect(Vehicle *v);
    bool sameAnchors(Vehicle *v);
    std::string toString();
    bool isSame(Vehicle *v);
};

#endif	/* VEHICLE_H */


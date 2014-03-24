/* 
 * File:   Board.h
 * Author: Wessel
 *
 * Created on 12 maart 2014, 11:31
 */

#ifndef BOARD_H
#define	BOARD_H

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <math.h>
#include "Vehicle.h"

class Board{
public:
    int boardsize;
    int cost; //G value
    std::string parent;
    
    Board(int size);
    Board(int size, std::vector<Vehicle*> v);
    Board();
    Vehicle takeVehicle(int xpos, int ypos);
    void addVehicle(Vehicle *v);
    bool canMove(Vehicle *v, int dist);
    std::vector<Vehicle*>* getVehicles();
    std::string toString();
    void clear();
    void setCost(int c);
    int getEstimate();
    int getFValue();
    void moveVehicle(int index, int dist);
    void setVehicles(std::vector<Vehicle*> v);
    bool intersect(Vehicle *v, int dist);
    
    ~Board();
    
private:
    std::vector<Vehicle*> vehicles; //vector of pointers to vehicles
    
    
    bool checkBounds(Vehicle *v, int dist);
};

#endif	/* BOARD_H */


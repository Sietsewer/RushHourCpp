/* 
 * File:   Board.h
 * Author: Wessel
 *
 * Created on 12 maart 2014, 11:31
 */

#ifndef BOARD_H
#define	BOARD_H

#include <vector>
#include <string>
#include <sstream>
#include "Vehicle.h"

class Board{
public:
    int boardsize;
    int cost;
    
    Board(int size);
    Board();
    void addVehicle(Vehicle *v);
    bool canMove(Vehicle *v, int dist);
    std::vector<Vehicle*>* getVehicles();
    std::string toString();
    void clear();
    void setCost(int c);
    int getEstimate();
    int getFValue();
    void moveVehicle(int index, int dist);
    void copyVehicles(std::vector<Vehicle*> v);
    
    ~Board();
    
private:
    std::vector<Vehicle*> vehicles; //vector of pointers to vehicles
    
    bool intersect(Vehicle *v, int dist);
    bool checkBounds(Vehicle *v, int dist);
};

#endif	/* BOARD_H */


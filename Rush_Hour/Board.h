/* 
 * File:   Board.h
 * Author: Wessel
 *
 * Created on 12 maart 2014, 11:31
 */

#ifndef BOARD_H
#define	BOARD_H

class Board{
public:
    int boardsize;
    
    Board(int size);
    bool intersect(Vehicle *v, int dist);
    bool checkBounds(Vehicle *v, int dist);
    
private:
    std::vector<Vehicle*> vehicles; //vector of pointers to vehicles
    
    void addVehicle(Vehicle *v);
};

#endif	/* BOARD_H */


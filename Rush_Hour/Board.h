/* 
 * File:   Board.h
 * Author: Wessel
 *
 * Created on 12 maart 2014, 11:31
 */

#ifndef BOARD_H
#define	BOARD_H

//using namespace std;

class Board{
public:
    int boardsize;
    Board(int size);
    
private:
    std::vector<Vehicle> vehicles;
};

#endif	/* BOARD_H */


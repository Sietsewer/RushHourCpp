/* 
 * File:   Solver.h
 * Author: Wessel
 *
 * Created on 18 maart 2014, 10:37
 */

#ifndef SOLVER_H
#define	SOLVER_H

#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include "Board.h"

using namespace std;

class Solver{
public:
    std::vector<Board> openstack;
    std::vector<Board> closedstack;
    Board board;
    
    Solver(Board *board);
    void solve();
    
private:
    bool containsBoard(Board b, std::vector<Board> list);
    std::vector<Board> getSuccessors(Board b);
    std::vector<Board> dropBoard(Board b, std::vector<Board> list);
};

#endif	/* SOLVER_H */


/* 
 * File:   Solver.h
 * Author: Wessel
 *
 * Created on 18 maart 2014, 10:37
 */

#ifndef SOLVER_H
#define	SOLVER_H

#include <vector>
#include <string>
#include <math.h>
#include "Board.h"

class Solver{
public:
    std::vector<Board> openstack;
    std::vector<Board> closedstack;
    Board board;
    
    Solver(Board *board);
    void solve();
    
private:
    std::vector<Board> getSuccessors(Board b);
    int getCost(Board b, int dist);
};

#endif	/* SOLVER_H */


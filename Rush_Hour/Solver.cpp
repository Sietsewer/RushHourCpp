#include "Solver.h"

Solver::Solver(Board *board){
    this->openstack.push_back(*board);
}

void Solver::solve(){
    std::string goal = "[4,2,2,2]";
    while(!openstack.empty()){
        Board current = openstack[openstack.size() - 1]; //get the node off the open list with the lowest f and call it node_current
        //TODO: find element with lowest f
        if (current.toString().find(goal) != std::string::npos){ //does the current board contain a vehicle on the goal position?
            break; //solution found; vehicle on the goal position can only be the red car
        }
        std::vector<Board> successors = getSuccessors(current); //get possible next moves
        for(int i = 0; i < successors.size(); i++){
            //set the cost of node_successor to be the cost of node_current plus the cost to get to node_successor from node_current
            //find node_successor on the OPEN list
            //if node_successor is on the OPEN list but the existing one is as good or better then discard this successor and continue
            //if node_successor is on the CLOSED list but the existing one is as good or better then discard this successor and continue
            //remove occurences of node_successor from OPEN and CLOSED
            //set the parent of node_successor to node_current
            //set h to be the estimated distance to node_goal (Using the heuristic function)
            //add node_successor to the OPEN list 
        }
        //add node_current to the CLOSED list 
    }
}

std::vector<Board> Solver::getSuccessors(Board b){
    std::vector<Board> results;
    std::vector<Vehicle*> *vehicles = b.getVehicles();
    
    //create list of possible moves for each vehicle on the board
    for (int i = 0; i < vehicles->size(); i++){
        for (int dist = -b.boardsize + 1; dist < b.boardsize; dist++){
            if (dist != 0 && b.canMove(vehicles->at(i), dist)){
                vehicles->at(i)->move(dist);
                results.push_back(b);
            }
        }
    }
    
    return results;
}

int Solver::getCost(Board b, int dist){
    //get cost of moving a vehicle dist amound of units to its next position
    //moving a greater distance in one move means lower cost
    return b.boardsize - abs(dist);
}
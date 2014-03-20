#include "Solver.h"
#include "Board.h"

Solver::Solver(Board *board) {
    this->openstack.push_back(*board);
}

void Solver::solve() {
    std::string goal = "[4,2,2,1]";
    while (!openstack.empty()) {
        Board current = openstack.back();
        //get the node off the open list with the lowest f and call it node_current
        int max = 65536;
        std::vector<Board> temp;
        for (int i = 0; i < openstack.size(); i++){
            if (openstack[i].cost <= max || openstack[i].getFValue() < current.getFValue()){
                current = openstack[i];
                closedstack.push_back(current);
            } else {
                temp.push_back(openstack[i]);
            }
        }
        swap(openstack, temp);
        
        if (current.toString().find(goal) != std::string::npos) { //does the current board contain a vehicle on the goal position?
            break; //solution found; vehicle on the goal position can only be the red car
        }
        
        std::vector<Board> successors = getSuccessors(current); //get possible next moves
        
        for (int i = 0; i < successors.size(); i++) {
            successors[i].cost += current.cost;
            //if node_successor is on the OPEN list but the existing one is as good or better then discard this successor and continue
            //if node_successor is on the CLOSED list but the existing one is as good or better then discard this successor and continue
            std::vector<Board> res;
            cout << openstack.size() << endl;
            cout << closedstack.size() << endl;
            for (int j = 0; j < openstack.size(); j++) {
                if (successors[i].toString() == openstack[j].toString() && successors[i].cost >= openstack[j].cost) {
                    res.push_back(openstack[j]);
                } else {
                    res.push_back(successors[i]);
                }
            }

            for (int j = 0; j < closedstack.size(); j++) {
                if (successors[i].toString() == closedstack[j].toString() && successors[i].cost >= closedstack[j].cost) {
                    res.push_back(closedstack[j]);
                } else {
                    res.push_back(successors[i]);
                }
            }

            if (res.size() > 0) {
                Board newcanidate;
                for (int j = 0; j < res.size(); j++){
                    if (res[j].cost <= max){
                        newcanidate = res[j];
                    }
                }
                
                std::vector<Board> temp2;
                for (int j = 0; j < openstack.size(); j++) {
                    if (newcanidate.toString() != openstack[j].toString()) {
                        temp2.push_back(openstack[j]);
                    }
                }
                swap(openstack, temp2);

                std::vector<Board> temp3;
                for (int j = 0; j < closedstack.size(); j++) {
                    if (newcanidate.toString() != closedstack[j].toString()) {
                        temp3.push_back(closedstack[j]);
                    }
                }
                swap(closedstack, temp3);
                
                //set the parent of node_successor to node_current
                current = newcanidate;
                //set h to be the estimated distance to node_goal (Using the heuristic function)
                //doit
                openstack.push_back(successors[i]);
            } 
        }
        closedstack.push_back(current);
    }
}

std::vector<Board> Solver::getSuccessors(Board b) {
    std::vector<Board> results;
    std::vector<Vehicle*> vehicles = *b.getVehicles();
    //create vector of states of possible moves for each vehicle on the board
    //NOTE: this function will break when called BUT it does identify all legal successive moves from the current board state.
    //the problem is actually cloning the vehicles and attaching them to a successor board state, see Board.cpp line 138
    for (int i = 0; i < vehicles.size(); i++) {
        for (int dist = -b.boardsize; dist <= b.boardsize; dist++) {
            if (dist != 0 && b.canMove(vehicles[i], dist)){
                Board temp = Board(6);
                temp.setVehicles(*b.getVehicles());
                temp.moveVehicle(i, dist);
                results.push_back(temp);
            }
        }
    }
    
    cout << "new successors: " << endl;
    for (int i = 0; i < results.size(); i++){
        cout << results[i].toString() << endl;
    }
    
    return results;
}
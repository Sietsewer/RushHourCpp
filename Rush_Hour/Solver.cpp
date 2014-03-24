#include "Solver.h"
#include "Board.h"

Solver::Solver(Board *board) {
    this->openstack.push_back(*board);
}

bool Solver::containsBoard(Board b, std::vector<Board> list){
    for (int i = 0; i < list.size(); i++){
        if(list[i].toString() == b.toString()){
            return true;
        }
    }
    return false;
}

std::vector<Board> Solver::dropBoard(Board b, std::vector<Board> list){
    std::vector<Board> temp;
    for (int i = 0; i < list.size(); i++){
        if (!(list[i].toString() == b.toString())){
            temp.push_back(list[i]);
        }
    }
    swap(list, temp);
    temp.clear();
    return list;
}

void Solver::solve() {
    std::string goal = "[4,2,2,1]";
    Board current = openstack.back();
    cout << current.toString() << endl;
    
    while (!(current.toString().find(goal) != std::string::npos)){
    //loop starts here.
        unsigned int max = 2147483648; // 2^31
        for (int i = 0; i < openstack.size(); i++) {
            if (openstack[i].getFValue() <= current.getFValue()) { //find board on open stack with lowest F cost
                current = openstack[i];
                max = current.cost;
            }
        }

        closedstack.push_back(current); //add board to closedstack
        openstack = dropBoard(current, openstack); //remove current board from open stack
        std::vector<Board> successors = getSuccessors(current);

        //for each possible successor, do this:
        for (int i = 0; i < successors.size(); i++) {
            if (!containsBoard(successors[i], closedstack)) { //do only if current state is not in the closed stack
                if (!containsBoard(successors[i], openstack)) { //is current state not on the open stack?
                    openstack.push_back(successors[i]); //put it on the open stack
                    current = successors[i]; //move to successor (?)
                } else { //find alternative
                    Board tempboard = current;
                    for (int j = 0; j < openstack.size(); j++) {
                        if (successors[i].toString() == openstack[i].toString()) {
                            tempboard = openstack[i]; 
                        }
                    }

                    if (tempboard.cost <= successors[i].cost) { //compare G costs
                        current = tempboard; //if cost is lower, move to other board on openstack
                    }
                }
            }
            //else, ignore successor
        }
    }
    cout << "Done. Moves: " << endl;
    for (int i = 0; i < closedstack.size(); i++){
        cout << closedstack[i].toString() << endl;
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
                temp.setCost(b.boardsize - abs(dist)); //set G value for board b
                results.push_back(temp);
            }
        }
    }
    
    /*cout << "new successors: " << endl;
    for (int i = 0; i < results.size(); i++){
        cout << results[i].toString() << endl;
    }*/
    
    return results;
}
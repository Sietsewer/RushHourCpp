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
        if (list[i].toString() != b.toString()){
            temp.push_back(list[i]);
        }
    }
    swap(temp, list);
    temp.clear();
    return list;
}

std::vector<Board> Solver::solve() {
    std::string goal = "[4,2,2,1]";
    Board current = openstack.back();
    
    while (openstack.size() > 0){
        unsigned int max = 65536; //2^16
        for (int i = 0; i < openstack.size(); i++) {
            if (openstack[i].getFValue() < max) { //find board on open stack with lowest F cost
                current = openstack[i];
                max = current.getFValue();
            }
        }
        
        if (current.toString().find(goal) != std::string::npos){
            //goal found!
            cout << "Done: " << current.toString() << " in " << closedstack.size() << " checks" << endl;
            return getPath(&current);
        }
        
        openstack = dropBoard(current, openstack);
        closedstack.push_back(current);
        
        std::vector<Board> succ = getSuccessors(current);
        for (int i = 0; i < succ.size(); i++){
            if (containsBoard(succ[i], closedstack)){ //if successor already in closed, skip this uccessor
                continue;
            }
            
            if (!containsBoard(succ[i], openstack) || current.cost < succ[i].cost){
                //set succ[i].parent to current if current.cost < succ[i].cost, closes loop
                Board *t = new Board(6);
                t->setVehicles(*current.getVehicles());
                t->parent = current.parent;
                succ[i].parent = t; //added current as parent
                openstack = dropBoard(succ[i], openstack);
                if (!containsBoard(succ[i], openstack)){ //if successor not in open
                    openstack.push_back(succ[i]); //add to open for F evaluation
                }
            }
        }
    }
    cout << "Path not found after " << closedstack.size() << " checks" << endl;

    std::vector<Board> empty;
    return empty;
}

std::vector<Board> Solver::getPath(Board *bptr){
    std::vector<Board> path;
    do {
        path.push_back(*bptr);
        bptr = bptr->parent;
    } while (bptr != NULL);
    
    std::vector<Board> temp;
    while (!path.empty()){
        temp.push_back(path.back()); //reverse order
        path.pop_back();
    }
    swap (path, temp);
    return path;
}

std::vector<Board> Solver::getSuccessors(Board b) {
    std::vector<Board> results;
    std::vector<Vehicle*> vehicles = *b.getVehicles();
    //create vector of states of possible moves for each vehicle on the board
    for (int i = 0; i < vehicles.size(); i++) { //for each vehicle
        for (int dist = 1; dist <= b.boardsize; dist++) {
            if (b.canMove(vehicles[i], dist)){
                Board temp = Board(6);
                temp.cost = b.cost;
                temp.setVehicles(*b.getVehicles());
                temp.moveVehicle(i, dist);
                //G value is based on move distance: the greater the diztance, the lower the cost
                temp.cost += (b.boardsize - abs(dist)); //set G value for board b
                //create parent
                Board *temp2 = new Board(6);
                temp2->setVehicles(*b.getVehicles());
                temp2->parent = b.parent;
                temp.parent = temp2; //added b as parent
                results.push_back(temp);
            } else {
                break; //stop if it's no longer possible to move, prevent teleporting vehicles
            }
        }
        for (int dist = -1; dist > -b.boardsize; dist--) {
            if (b.canMove(vehicles[i], dist)){
                Board temp = Board(6);
                temp.cost = b.cost;
                temp.setVehicles(*b.getVehicles());
                temp.moveVehicle(i, dist);
                temp.cost += (b.boardsize - abs(dist)); //set G value for board b
                //create parent
                Board *temp2 = new Board(6);
                temp2->setVehicles(*b.getVehicles());
                temp2->parent = b.parent;
                temp.parent = temp2; //added b as parent
                results.push_back(temp);
            } else {
                break;
            }
        }
    }
    
    return results;
}
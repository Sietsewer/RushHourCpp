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

void Solver::solve() {
    std::string goal = "[4,2,2,1]";
    Board current = openstack.back();
    
    while (openstack.size() > 0){
        unsigned int max = 65536; // 2^31
        for (int i = 0; i < openstack.size(); i++) {
            if (openstack[i].getFValue() < max) { //find board on open stack with lowest F cost
                current = openstack[i];
                max = current.getFValue();
            }
        }
        
        if (current.toString().find(goal) != std::string::npos){
            cout << "Done: " << current.toString() << " in " << closedstack.size() << " checks" << endl;
            return;
        }
        
        openstack = dropBoard(current, openstack);
        closedstack.push_back(current);
        
        std::vector<Board> succ = getSuccessors(current);
        for (int i = 0; i < succ.size(); i++){
            if (containsBoard(succ[i], closedstack)){
                continue;
            }
            
            int tentg = current.cost + succ[i].cost;
            
            if (!containsBoard(succ[i], openstack) || tentg < succ[i].cost){
                dropBoard(succ[i], openstack);
                if (!containsBoard(succ[i], openstack)){
                    openstack.push_back(succ[i]);
                }
            }
        }
    }

    cout << "Not found after " << closedstack.size() << " checks." << endl;
}

std::vector<Board> Solver::getSuccessors(Board b) {
    std::vector<Board> results;
    std::vector<Vehicle*> vehicles = *b.getVehicles();
    //create vector of states of possible moves for each vehicle on the board
    for (int i = 0; i < vehicles.size(); i++) {
        for (int dist = 1; dist <= b.boardsize; dist++) {
            if (b.canMove(vehicles[i], dist)){
                Board temp = Board(6);
                temp.cost = b.cost;
                temp.setVehicles(*b.getVehicles());
                temp.moveVehicle(i, dist);
                temp.cost += (b.boardsize - abs(dist)); //set G value for board b
                temp.parent = b.toString(); //TODO: store parent boards as a pointer to a board!
                results.push_back(temp);
            } else {
                break;
            }
        }
        for (int dist = -1; dist > -b.boardsize; dist--) {
            if (b.canMove(vehicles[i], dist)){
                Board temp = Board(6);
                temp.cost = b.cost;
                temp.setVehicles(*b.getVehicles());
                temp.moveVehicle(i, dist);
                temp.cost += (b.boardsize - abs(dist)); //set G value for board b
                temp.parent = b.toString();
                results.push_back(temp);
            } else {
                break;
            }
        }
    }
    
    return results;
}
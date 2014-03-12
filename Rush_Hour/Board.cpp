#include <vector>
#include "Vehicle.h"
#include "Board.h"

Board::Board(int size){
    this->boardsize = size;
}

void Board::addVehicle(Vehicle* v){
    this->vehicles.push_back(v);
}

//if (!intersect(v, dist) && checkBounds(v, dist)) { //vehicle can be moved }

//check if vehicle + move offset intersects with other vehicles
bool Board::intersect(Vehicle* v, int dist){
    for (int i = 0; i < vehicles.size(); i++){
        int x1 = v->xanchor;
        int x2 = vehicles[i]->xanchor;
        int y1 = v->yanchor;
        int y2 = vehicles[i]->yanchor;
        int w1 = v->width;
        int w2 = vehicles[i]->width;
        int h1 = v->height;
        int h2 = vehicles[i]->height;
        
        if(v->orientation == Vehicle::Horizontal){
            x1 += dist;
        } else {
            y1 += dist;
        }
        
        if (x1 + w1 < x2 || x2 + w2 < x1 || y1 + h1 < y2 || y2 + h2 < y1){
            return true;
        }
    }
    return false;
}

//check if vehicle + move distance fits within board bounds
bool Board::checkBounds(Vehicle* v, int dist){
    int diff = 0;
    if (v->orientation == Vehicle::Horizontal) {
        diff = v->xanchor + v->width - 1 + dist;
    } else {
        diff = v->yanchor + v->height - 1 + dist;
    }
    if (diff >= 0 && diff <= this->boardsize) {
        return true;
    }
    return false;
}
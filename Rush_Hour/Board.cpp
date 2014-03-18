#include "Board.h"

Board::Board(int size){
    this->boardsize = size;
}

Board::Board(){}

void Board::addVehicle(Vehicle* v){
    //disallow adding intersecting vehicles or vehicles out of bounds
    if (this->intersect(v, 0) || !this->checkBounds(v, 0)){
        return;
    }
    for (int i = 0; i < vehicles.size(); i++){
        if (vehicles[i]->sameAnchors(v)){
            return;
        }
    }
    this->vehicles.push_back(v);
}

bool Board::canMove(Vehicle* v, int dist){
    return (!this->intersect(v, dist) && this->checkBounds(v, dist));
}

std::string Board::toString(){
    std::ostringstream oss;
    oss << "[";
    for (int i = 0; i < vehicles.size(); i++){
        oss << vehicles[i]->toString();
    }
    oss << "]";
    return oss.str();
}

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
        
        if ((x1 + w1 < x2 || x2 + w2 < x1 || y1 + h1 < y2 || y2 + h2 < y1) && !v->sameAnchors(vehicles[i])){
            return true;
        }
    }
    return false;
}

//check if vehicle + move distance fits within board bounds
bool Board::checkBounds(Vehicle* v, int dist){
    if (v->orientation == Vehicle::Horizontal) {
        return v->xanchor + dist >= 0 && v->xanchor + dist + v->width <= this->boardsize;
    } else {
        return v->yanchor + dist >= 0 && v->yanchor + dist + v->height <= this->boardsize;
    }
}

std::vector<Vehicle*>* Board::getVehicles(){
    return &this->vehicles;
}

Board::~Board(){
    while (!this->vehicles.empty()){
        delete this->vehicles.back();
        this->vehicles.back() = NULL;
        this->vehicles.pop_back();
    }
}
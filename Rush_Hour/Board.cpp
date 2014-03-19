#include "Board.h"

Board::Board(int size){
    this->boardsize = size;
    this->cost = 0;
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
        int p1x = v->xanchor;
        int p1y = v->yanchor;
        int p2x = v->xanchor + v->width;
        int p2y = v->yanchor + v->height;
        int p3x = vehicles[i]->xanchor;
        int p3y = vehicles[i]->yanchor;
        int p4x = vehicles[i]->xanchor + vehicles[i]->width;
        int p4y = vehicles[i]->yanchor + vehicles[i]->height;
        
        if(v->orientation == Vehicle::Horizontal){
            p1x += dist;
            p2x += dist;
        } else {
            p1y += dist;
            p2y += dist;
        }
        
        if (!(p1y <= p3y || p1y >= p4y || p2x <= p3x || p1x >= p4x ) && !(v->isSame(vehicles[i]))){
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

void Board::clear(){
    while (!this->vehicles.empty()){
        delete this->vehicles.back();
        this->vehicles.back() = NULL;
        this->vehicles.pop_back();
    }
}

void Board::setCost(int c){
    this->cost = cost;
}

int Board::getEstimate(){
    Vehicle *v = new Vehicle(0, 2, 6, 1);
    int counts = -1;
    for (int i = 0; i < this->vehicles.size(); i++){
        counts += intersect(vehicles[i], 0) ? 1 : 0;
    }
    delete v;
    return counts;
}

int Board::getFValue(){
    return getEstimate() + this->cost;
}

void Board::moveVehicle(int index, int dist){
    this->vehicles.at(index)->move(dist);
}

void Board::copyVehicles(std::vector<Vehicle*> v){
    vehicles.clear();
    for (int i = 0; i < v.size(); i++){
        addVehicle(new Vehicle(v[i]->xanchor, v[i]->yanchor, v[i]->width, v[i]->height));
    }
}
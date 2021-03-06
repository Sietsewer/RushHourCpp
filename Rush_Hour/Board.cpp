#include "Board.h"

Board::Board(int size){
    this->boardsize = size;
    this->cost = 0;
    this->parent = NULL;
}

Board::Board(int size, std::vector<Vehicle*> v){
    this->boardsize = size;
    this->cost = 0;
    for (int i = 0; i < v.size(); i++){
        this->vehicles.push_back(new Vehicle(v[i]->xanchor, v[i]->yanchor, v[i]->width, v[i]->height, v[i]->color));
    }
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

Vehicle Board::takeVehicle(int xpos, int ypos){
    std::vector<Vehicle*> temp;
    Vehicle toreturn;
    for (int i = 0; i < vehicles.size(); i++){
        if ((vehicles[i]->xanchor == xpos) && (vehicles[i]->yanchor == ypos)){
            toreturn = *vehicles[i];
        } else {
            temp.push_back(vehicles[i]);
        }
    }
    swap(vehicles, temp);
    return toreturn;
}

bool Board::canMove(Vehicle* v, int dist){
    if (this->intersect(v, dist) || !this->checkBounds(v, dist)){
        return false;
    }
    return true;
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
        //rectangle intersection for every vehicle
        int p1x = v->xanchor;
        int p1y = v->yanchor;
        int p2x = v->xanchor + v->width - 1;
        int p2y = v->yanchor + v->height - 1;
        int p3x = vehicles[i]->xanchor;
        int p3y = vehicles[i]->yanchor;
        int p4x = vehicles[i]->xanchor + vehicles[i]->width - 1;
        int p4y = vehicles[i]->yanchor + vehicles[i]->height - 1;
        
        if(v->orientation == Vehicle::Horizontal){
            p1x += dist;
            p2x += dist;
        } else {
            p1y += dist;
            p2y += dist;
        }
        
        //ignore intersection with vehicle itself
        if (!(p2y < p3y || p1y > p4y || p2x < p3x || p1x > p4x) && !(v->isSame(vehicles[i]))){
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
    for (int i = 0; i < vehicles.size(); i++){
        //delete this->vehicles[i];
    }
    this->vehicles.clear();
}

void Board::clear(){
    for (int i = 0; i < vehicles.size(); i++){
        //delete this->vehicles[i];
    }
    this->vehicles.clear();
}

void Board::setCost(int c){
    this->cost = cost;
}

//get H cost
int Board::getEstimate(){
    //calculate estimate by counting number of vehicles between red car and exit
    //find red car x-anchor
    Vehicle *rc; //pointer to red car
    for (int i = 0; i < this->vehicles.size(); i++){
        //red car is the only possible vehicle that has a x-anchor of 2 and a horizontal orientation
        if (vehicles[i]->yanchor == 2 && vehicles[i]->orientation == Vehicle::Horizontal){
            rc = vehicles[i]; //red car found
        }
    }
     
    int counts = 0;
    //count how many vehicles are blocking the exit, use this to make an estimate
    for (int i = 0; i < this->boardsize; i ++){
        Vehicle *v = new Vehicle(rc->xanchor + i, 2, 1, 1, sf::Color::Black); //1*1 "vehicle" to test intersection
        v->orientation = Vehicle::Horizontal; //dirty hax to force orientation of 1*1 "vehicle"
        counts += intersect(v, 0) ? 1 : 0;
        delete v; //cleanup
    }
    return counts * vehicles.size(); //maybe multiply this by some other factor?
}

int Board::getFValue(){
    return getEstimate() + this->cost;
    //return cost;
}

void Board::moveVehicle(int index, int dist){
    this->vehicles.at(index)->move(dist);
}

void Board::setVehicles(std::vector<Vehicle*> v){
    vehicles.clear();
    for (int i = 0; i < v.size(); i++){
        int x = v[i]->xanchor;
        int y = v[i]->yanchor;
        int w = v[i]->width;
        int h = v[i]->height;
        Vehicle *v2 = new Vehicle(x, y, w, h);
        v2->color = v[i]->color;
        this->vehicles.push_back(v2);
    }
}
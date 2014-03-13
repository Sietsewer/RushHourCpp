#include <string>
#include <sstream>
#include "Vehicle.h"

Vehicle::Vehicle(int x, int y, int width, int height){
    this->width = width;
    this->height = height;
    this->setAnchors(x, y);
    
    this->orientation = width > height ? Horizontal : Vertical;
}

void Vehicle::rotateVehicle(){
    int temp = this->width;
    this->width = this->height;
    this->height = this->width;
    
    this->orientation = this->width > this->height ? Horizontal : Vertical;
}

void Vehicle::setAnchors(int x, int y){
    this->xanchor = x;
    this->yanchor = y;
}

bool Vehicle::sameAnchors(Vehicle* v){
    return (this->xanchor == v->xanchor && this->yanchor == v->yanchor);
}

void Vehicle::move(int dist){
    //TODO: add bounds checking, have to ensure vehicle doesn't move off the board or into other vehicles
    if (this->orientation == Horizontal){
        this->xanchor += dist;
    } else {
        this->yanchor += dist;
    }
}

std::string Vehicle::toString(){
    std::ostringstream oss;
    oss << "[" << this->xanchor << "_" << this->yanchor << "_" << this->width << "_" << this->height << "]";
    return oss.str();
}
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
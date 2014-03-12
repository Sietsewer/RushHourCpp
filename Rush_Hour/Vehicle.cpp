#include "Vehicle.h"

int width;
int height;

Vehicle::Vehicle(int width, int height){
    this->width = width;
    this->height = height;
    
    orientation = width > height ? Orientation.Horizontal : Orientation.Vertical;
}

Vehicle::rotate(){
    int temp = this->width;
    this->width = this->height;
    this->height = this->width;
}
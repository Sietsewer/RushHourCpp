#include "Vehicle.h"

int width;
int height;
int xanchor;
int yanchor;
Orientation orientation;

Vehicle::Vehicle(int width, int height){
    this->width = width;
    this->height = height;
    
    this->orientation = width > height ? Orientation.Horizontal : Orientation.Vertical;
}

Vehicle::rotate(){
    int temp = this->width;
    this->width = this->height;
    this->height = this->width;
    
    this->orientation = this->width > this->height ? Orientation.Horizontal : Orientation.Vertical;
}
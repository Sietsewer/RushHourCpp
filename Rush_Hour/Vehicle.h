/* 
 * File:   Vehicle.h
 * Author: Wessel
 *
 * Created on 12 maart 2014, 11:32
 */

#ifndef VEHICLE_H
#define	VEHICLE_H

class Vehicle {
public:
    enum Orientation {Horizontal, Vertical};
    int width;
    int height;
    int xanchor;
    int yanchor;
    Orientation orientation;
    
    Vehicle(int x, int y, int width, int height);
    void setAnchors(int x, int y);
    void rotateVehicle();
    void move(int dist);
    bool intersect(Vehicle *v);
};

#endif	/* VEHICLE_H */


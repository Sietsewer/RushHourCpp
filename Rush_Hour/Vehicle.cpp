#include "Vehicle.h"

Vehicle::Vehicle(int x, int y, int width, int height, sf::Color color){
    this->width = width;
    this->height = height;
    this->setAnchors(x, y);
    
    this->rect = new sf::RectangleShape(sf::Vector2f(width*100.0f, height*100.0f));
    this->rect->setPosition(x*100.0f, y*100.0f);
    
    this->color = color;
    this->rect->setFillColor(this->color);
    this->rect->setOutlineColor(sf::Color::Black);
    this->rect->setOutlineThickness(-2.0f);
    
    this->orientation = width > height ? Horizontal : Vertical;
}

Vehicle::Vehicle(int x, int y, int width, int height){
    this->width = width;
    this->height = height;
    this->setAnchors(x, y);
    
    this->rect = new sf::RectangleShape(sf::Vector2f(width*100.0f, height*100.0f));
    this->rect->setPosition(x*100.0f, y*100.0f);
    this->rect->setFillColor(this->color);
    this->rect->setOutlineColor(sf::Color::Black);
    this->rect->setOutlineThickness(-2.0f);
    
    this->orientation = width > height ? Horizontal : Vertical;
}

Vehicle::Vehicle(){}

Vehicle::~Vehicle(){
    //delete this->rect;
    //this->rect = NULL;
}

void Vehicle::rotateVehicle(){
    int temp = this->width;
    this->width = this->height;
    this->height = temp;
    
    delete this->rect;
    this->rect = NULL;
    this->rect = new sf::RectangleShape(sf::Vector2f(width*100.0f, height*100.0f));
    this->rect->setPosition(this->xanchor*100.0f, this->yanchor*100.0f);
    this->rect->setFillColor(this->color);
    
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
    if (this->orientation == Horizontal){
        this->xanchor += dist;
    } else {
        this->yanchor += dist;
    }
}

std::string Vehicle::toString(){
    std::ostringstream oss;
    oss << "[" << this->xanchor << "," << this->yanchor << "," << this->width << "," << this->height << "]";
    return oss.str();
}

bool Vehicle::isSame(Vehicle *v){
    return (this->toString() == v->toString());
}
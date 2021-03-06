/* 
 * File:   main.cpp
 * Author: Sietse & Wessel
 *
 * Created on 11 March 2014, 11:08
 */

#include <cstdlib>
//#include <SFML/Window.hpp>
#include <iostream> //for console debugging, because console is the shit.
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "Vehicle.h"
#include "Board.h"
#include "Button.h"
#include "Solver.h"
#include "ColorGiver.h"

using namespace std;

/*
 * 
 */
Solver *s;
Board *b;
std::vector<Board> path;
int pindex = 0;

sf::Color themeColor = sf::Color::Green;        //Default colour for menus
sf::Color backColor = sf::Color::White;         //Default other colour for menus

//Menu items and such
sf::RectangleShape sideBarOutline(sf::Vector2f(200.0f, 600.0f));
sf::RectangleShape sideBarPanel1(sf::Vector2f(160.0f, 300.0f));
sf::RectangleShape sideBarPanel2(sf::Vector2f(160.0f, 240.0f));
sf::RectangleShape rect_btn_Solve(sf::Vector2f(120.0f, 40.0f));
sf::RectangleShape rect_btn_vehicle_2(sf::Vector2f(120.0f, 40.0f));
sf::RectangleShape rect_btn_vehicle_3(sf::Vector2f(120.0f, 40.0f));
sf::RectangleShape board_Rects[6][6];
sf::RectangleShape rect_btn_step_next(sf::Vector2f(40.0f, 40.0f));
sf::RectangleShape rect_btn_step_prev(sf::Vector2f(40.0f, 40.0f));
//Menu items end

bool dragging = false;  //True if dragging a vehicle
Vehicle dragged;        //Vehicle that is being dragged
sf::RectangleShape draggingRect;        //Shape to indicate location of dragged vehicle
std::vector<Vehicle*>* vehiclePointers;
sf::Vector2f mouseLocation;     //Location of the mouse pointer in the window.
int dragWidth;  //Size of the vehicle being dragged
int dragHeight;
bool rotateDownBlock = false;   //True if the rotate button is down
bool moveDownBlock = false;     //True if the move button is down

ColorGiver colors = ColorGiver();       //Object of class that gives new colors

void btn_Solve_Click() {
    //Stuff to do when you click the solve button
    s = new Solver(b);
    path.clear();
    path = s->solve(); //a* search!
    pindex = 0;
    for (int i = 0; i < path.size(); i++){
        cout << path[i].toString() << endl;
    }
}

void vehicle_2_click() {
    //Called when the button for vehicle of 2 is clicked
    dragging = true;    //Set dragging state
    dragWidth = 2;      //Set vehicle sizes
    dragHeight = 1;
    draggingRect.setSize(sf::Vector2f(dragWidth * 100.0f, dragHeight * 100.0f));//Multiply size by 100, as grid square is 100 by 100
    draggingRect.setFillColor(colors.getColor());
    draggingRect.setOrigin(50.0f, 50.0f);//Offset origin a bit, so the mouse is in the middle of the shape
    draggingRect.setPosition(mouseLocation);    //Set rectangle on mouse location
}

void vehicle_3_click() {
    //Called when the button for vehicle of 3 is clicked. Same as method above^^
    dragging = true;
    dragWidth = 3;      //Except for this, though.
    dragHeight = 1;
    draggingRect.setSize(sf::Vector2f(dragWidth * 100.0f, dragHeight * 100.0f));
    draggingRect.setFillColor(colors.getColor());
    draggingRect.setOrigin(50.0f, 50.0f);
    draggingRect.setPosition(mouseLocation);
}

void btn_step_next_click() {
    //Cycle trough sollution steps
    if (pindex + 1 < path.size()){
        b = &path[pindex + 1];
        pindex++;
    }
}

void btn_step_prev_click() {
    //Cycle trough sollution steps, except backwards
    if (pindex - 1 >= 0 && path.size() > 0) {
        b = &path[pindex - 1];
        pindex--;
    }
}

int main(int argc, char** argv) {
    //Setting a default board state
    b = new Board(6);
    //b->addVehicle(new Vehicle(1, 0, 1, 3));
    b->addVehicle(new Vehicle(1, 0, 2, 1, colors.getColor()));
    b->addVehicle(new Vehicle(1, 2, 2, 1, colors.getColor()));
    //b->addVehicle(new Vehicle(0, 2, 2, 1, colors.getColor()));
    cout << b->toString() << endl;


    sf::RenderWindow window;
    window.create(sf::VideoMode(800, 600), "Rush Hour");//Create a window object
    //Menu items settings
    //  Colours
    sideBarOutline.setFillColor(themeColor);
    sideBarPanel1.setFillColor(backColor);
    sideBarPanel2.setFillColor(backColor);
    rect_btn_Solve.setFillColor(themeColor);
    rect_btn_vehicle_2.setFillColor(themeColor);
    rect_btn_vehicle_3.setFillColor(themeColor);
    rect_btn_step_next.setFillColor(themeColor);
    rect_btn_step_prev.setFillColor(themeColor);

    //  Positions
    sideBarOutline.setPosition(600.0f, 0.0f);
    sideBarPanel1.setPosition(620.0f, 20.0f);
    sideBarPanel2.setPosition(620.0f, 340.0f);
    rect_btn_Solve.setPosition(640.0f, 360.0f);
    rect_btn_vehicle_2.setPosition(640.0f, 40.0f);
    rect_btn_vehicle_3.setPosition(640.0f, 100.0f);
    rect_btn_step_next.setPosition(720.0f, 420.0f);
    rect_btn_step_prev.setPosition(640.0f, 420.0f);

    //  Board loop
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            board_Rects [i] [j] = sf::RectangleShape(sf::Vector2f(80.0f, 80.0f));
            board_Rects [i] [j].setFillColor(sf::Color(200, 200, 200));
            board_Rects [i] [j].setPosition(10.0f + (i * 100.0f), 10.0f + (j * 100.0f));
        }
    }

    //  Buttons
    Button btn_Solve(rect_btn_Solve, themeColor, sf::Color::Black, &window, &btn_Solve_Click);
    Button btn_vehicle_2(rect_btn_vehicle_2, themeColor, sf::Color::Black, &window, &vehicle_2_click);
    Button btn_vehicle_3(rect_btn_vehicle_3, themeColor, sf::Color::Black, &window, &vehicle_3_click);
    Button btn_step_next(rect_btn_step_next, themeColor, sf::Color::Black, &window, &btn_step_next_click);
    Button btn_step_prev(rect_btn_step_prev, themeColor, sf::Color::Black, &window, &btn_step_prev_click);

    //Menu items end
    while (window.isOpen()) {
        //   ---   UPDATE LOOP BEGINS HERE   ---   //
        sf::Event event;
        mouseLocation = window.mapPixelToCoords(sf::Mouse::getPosition(window));

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (dragging) {
                //Enter when dragging a shape
                draggingRect.setPosition(mouseLocation);//Set shape location on mouse pointer
                if ((sf::Mouse::isButtonPressed(sf::Mouse::Right)&&~rotateDownBlock)) {
                    //Enter when rotate button is clicked (while dragging, ofc.)
                    int temp = dragWidth;//Swap shape width an height
                    dragWidth = dragHeight;
                    dragHeight = temp;

                    draggingRect.setSize(sf::Vector2f(dragWidth * 100.0f, dragHeight * 100.0f));//Apply new sizes to shape
                    draggingRect.setOrigin(50.0f, 50.0f);
                    draggingRect.setPosition(mouseLocation);
                    rotateDownBlock = true;// Set state to rotate, to prevent spamming of rotation when button is held
                } else {
                    //Enter when rotate is not pressed, or held down
                    rotateDownBlock = sf::Mouse::isButtonPressed(sf::Mouse::Right);// Set state to state of button
                }
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)&&~moveDownBlock) {
                    dragging = false;
                    if ((mouseLocation.x > 0.0f && mouseLocation.x <= 600.0f)&&(mouseLocation.y > 0.0f && mouseLocation.y <= 600.0f)) {
                        b->addVehicle(new Vehicle((int) (mouseLocation.x / 100.0f), (int) (mouseLocation.y / 100.0f), dragWidth, dragHeight, draggingRect.getFillColor()));
                    }
                    moveDownBlock=true;
                } else {
                    moveDownBlock = sf::Mouse::isButtonPressed(sf::Mouse::Left);
                }
                /*if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
                    dragging = false;
                }*/
            } else {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)&&~moveDownBlock) {
                    btn_vehicle_2.mouseDown();
                    btn_vehicle_3.mouseDown();
                    btn_step_next.mouseDown();
                    btn_step_prev.mouseDown();
                    btn_Solve.mouseDown();
                    moveDownBlock = true;
                    if (((mouseLocation.x > 0.0f && mouseLocation.x <= 600.0f)&&(mouseLocation.y > 0.0f && mouseLocation.y <= 600.0f)) && ~moveDownBlock) {

                        Vehicle t = b->takeVehicle((int) mouseLocation.x / 100.0f, (int) mouseLocation.y / 100.0f);
                        moveDownBlock = true;
                        if (~(t.color == sf::Color::Black)) {
                            dragging = true;
                            dragWidth = t.width;
                            dragHeight = t.height;
                            draggingRect.setSize(sf::Vector2f(dragWidth * 100.0f, dragHeight * 100.0f));
                            draggingRect.setFillColor(t.color);
                            draggingRect.setOrigin(50.0f, 50.0f);
                            draggingRect.setPosition(mouseLocation);
                        }
                    } else {
                        moveDownBlock = sf::Mouse::isButtonPressed(sf::Mouse::Left);
                    }

                } else {
                    moveDownBlock = sf::Mouse::isButtonPressed(sf::Mouse::Left);
                    btn_vehicle_2.mouseUp();
                    btn_vehicle_3.mouseUp();
                    btn_step_next.mouseUp();
                    btn_step_prev.mouseUp();
                    btn_Solve.mouseUp();
                    
                }
            }
        }

        window.clear(sf::Color::White); //BEGIN render list << --
        //Main board
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 6; j++) {
                window.draw(board_Rects [i] [j]);
            }
        }
        vehiclePointers = b->getVehicles();
        Vehicle v;
        for (int i = 0; i < vehiclePointers->size(); i++) {
            v = *vehiclePointers->at(i);
            v.rect->setFillColor(v.color);
            window.draw(*v.rect);
        }
        //Here, AND NO FURTHER. (Else order will be fucked)
        //END main board

        //Side menu background
        window.draw(sideBarOutline);
        window.draw(sideBarPanel1);
        window.draw(sideBarPanel2);
        window.draw(btn_Solve);
        window.draw(btn_vehicle_2);
        window.draw(btn_vehicle_3);
        window.draw(btn_step_next);
        window.draw(btn_step_prev);
        if (dragging) {
            window.draw(draggingRect);
        }
        //END menu background

        //Menu button
        //Buttons of the menu here.
        //END menu buttons

        window.display(); //END render list << --
    }
    //   ---   UPDATE LOOP ENDS HERE   ---   //
    delete b; //memory leak fixed!
    delete s;
    b = NULL; //for safety
    s = NULL;
    //end test
    return 0;
}
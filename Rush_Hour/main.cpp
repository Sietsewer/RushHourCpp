/* 
 * File:   main.cpp
 * Author: Sietse & Wessel
 *
 * Created on 11 March 2014, 11:08
 */

#include <cstdlib>
//#include <SFML/Window.hpp>
#include <iostream> //for console debugging
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "Vehicle.h"
#include "Board.h"
#include "Button.h"
#include "Solver.h"

using namespace std;

/*
 * 
 */
sf::Color themeColor = sf::Color::Green;
sf::Color backColor = sf::Color::White;

//Menu items and such
sf::RectangleShape sideBarOutline(sf::Vector2f(200.0f, 600.0f));
sf::RectangleShape sideBarPanel1(sf::Vector2f(160.0f, 300.0f));
sf::RectangleShape sideBarPanel2(sf::Vector2f(160.0f, 240.0f));
sf::RectangleShape rect_btn_Solve(sf::Vector2f(120.0f, 40.0f));
sf::RectangleShape rect_btn_vehicle_2(sf::Vector2f(120.0f, 40.0f));
sf::RectangleShape board_Rects[6][6];
//Menu items end

bool dragging = false;
Vehicle dragged;
sf::RectangleShape draggingRect;
std::vector<Vehicle*>* vehiclePointers;
sf::Vector2f mouseLocation;
int dragWidth;
int dragHeight;

void btn_Solve_Click() {
    cout << "Button clicky!" << endl;
    //Stuff to do when you click the solve button
}

void vehicle_2_click() {
    dragging = true;
    dragWidth = 2;
    dragHeight = 1;
    draggingRect.setSize(sf::Vector2f(dragWidth * 100.0f, dragHeight * 100.0f));
    draggingRect.setFillColor(sf::Color::Red);
    draggingRect.setOrigin(50.0f, 50.0f);
    draggingRect.setPosition(mouseLocation);

}

int main(int argc, char** argv) {

    //testing shit pls don't touch kthxbye
    Board *b = new Board(6);
    //b->addVehicle(new Vehicle(1, 0, 1, 3));
    b->addVehicle(new Vehicle(1, 0, 2, 1, sf::Color::Blue));
    b->addVehicle(new Vehicle(1, 2, 2, 1, sf::Color::Yellow));
    cout << b->toString() << endl;

    Solver *s = new Solver(b);
    //s->solve(); //Don't use this one yet, please. Shit just fucking breaks right now
    //see Solver::getSuccessors() for a little more detail
    //things specifically go wrong at Board line 138, still don't know what's causing it...
    //also move this bit to btn_Solve_Click() once it actually works


    sf::RenderWindow window;
    window.create(sf::VideoMode(800, 600), "Rush Hour");
    //Menu items settings
    //  Colours
    sideBarOutline.setFillColor(themeColor);
    sideBarPanel1.setFillColor(backColor);
    sideBarPanel2.setFillColor(backColor);
    rect_btn_Solve.setFillColor(themeColor);
    rect_btn_vehicle_2.setFillColor(themeColor);

    //  Positions
    sideBarOutline.setPosition(600.0f, 0.0f);
    sideBarPanel1.setPosition(620.0f, 20.0f);
    sideBarPanel2.setPosition(620.0f, 340.0f);
    rect_btn_Solve.setPosition(640.0f, 360.0f);
    rect_btn_vehicle_2.setPosition(640.0f, 40.0f);

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

    //Menu items end
    while (window.isOpen()) {
        sf::Event event;
        mouseLocation = window.mapPixelToCoords(sf::Mouse::getPosition(window));

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {

                window.close();
            }

            if (dragging) {
                draggingRect.setPosition(mouseLocation);
                if (sf::Mouse::isButtonPressed(sf::Mouse::Middle)) {
                    int temp = dragWidth;
                    dragWidth = dragHeight;
                    dragHeight = temp;

                    draggingRect.setSize(sf::Vector2f(dragWidth * 100.0f, dragHeight * 100.0f));
                    draggingRect.setFillColor(sf::Color::Red);
                    draggingRect.setOrigin(50.0f, 50.0f);
                    draggingRect.setPosition(mouseLocation);
                }
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    dragging = false;
                    if ((mouseLocation.x > 0.0f && mouseLocation.x < 600.0f)&&(mouseLocation.y > 0.0f && mouseLocation.y < 600.0f)) {
                        b->addVehicle(new Vehicle((int) (mouseLocation.x / 100.0f), (int) (mouseLocation.y / 100.0f), dragWidth, dragHeight, draggingRect.getFillColor()));
                    }
                }
                if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
                    dragging = false;
                }
            } else {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    btn_vehicle_2.mouseDown();
                    btn_Solve.mouseDown();
                } else {
                    btn_vehicle_2.mouseUp();
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
        for (int i = 0; i < vehiclePointers->size(); i++) {
            window.draw(*vehiclePointers->at(i)->rect);
        }
        //Here, AND NO FURTHER. (Else order will be fucked)
        //END main board

        //Side menu background
        window.draw(sideBarOutline);
        window.draw(sideBarPanel1);
        window.draw(sideBarPanel2);
        window.draw(btn_Solve);
        window.draw(btn_vehicle_2);
        if (dragging) {
            window.draw(draggingRect);
        }
        //END menu background

        //Menu button
        //Buttons of the menu here.
        //END menu buttons

        window.display(); //END render list << --
    }
    delete b; //memory leak fixed!
    delete s;
    b = NULL; //for safety
    s = NULL;
    //end test
    return 0;
}


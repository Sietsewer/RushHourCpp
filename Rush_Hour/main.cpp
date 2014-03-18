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
sf::RectangleShape board_Rects[6][6];
//Menu items end

std::vector<Vehicle*>* vehiclePointers;

void btn_Solve_Click() {
    cout << "Button clicky!" << endl;
    //Stuff to do when you click the solve button
}

int main(int argc, char** argv) {

    //testing shit pls don't touch kthxbye
    Board *b = new Board(6);
    b->addVehicle(new Vehicle(0, 0, 1, 3));
    b->addVehicle(new Vehicle(1, 0, 2, 1));
    cout << b->toString() << endl;


    sf::RenderWindow window;
    window.create(sf::VideoMode(800, 600), "Rush Hour");
    //Menu items settings
    //  Colours
    sideBarOutline.setFillColor(themeColor);
    sideBarPanel1.setFillColor(backColor);
    sideBarPanel2.setFillColor(backColor);

    //  Positions
    sideBarOutline.setPosition(600.0f, 0.0f);
    sideBarPanel1.setPosition(620.0f, 20.0f);
    sideBarPanel2.setPosition(620.0f, 340.0f);
    rect_btn_Solve.setPosition(640.0f, 360.0f);

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

    //Menu items end
    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {

                window.close();
            }


            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                btn_Solve.mouseDown();
            } else {
                btn_Solve.mouseUp();
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
        //END menu background

        //Menu button
        //Buttons of the menu here.
        //END menu buttons

        window.display(); //END render list << --
    }
    delete b; //memory leak fixed!
    b = NULL; //for safety
    //end test
    return 0;
}


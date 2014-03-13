/* 
 * File:   main.cpp
 * Author: Sietse & Wessel
 *
 * Created on 11 March 2014, 11:08
 */

#include <cstdlib>
//#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

using namespace std;

/*
 * 
 */
sf::Color themeColor = sf::Color::Green;
sf::Color backColor  = sf::Color::White;

//Menu items and such
sf::RectangleShape sideBarOutline(sf::Vector2f(200.0f, 600.0f));
sf::RectangleShape sideBarPanel1(sf::Vector2f(160.0f, 300.0f));
sf::RectangleShape sideBarPanel2(sf::Vector2f(160.0f, 240.0f));
sf::RectangleShape btnSolve(sf::Vector2f(120.0f, 40.0f));
sf::Font font;
sf::Text text;
//Menu items end

int main(int argc, char** argv) {
    
    //testing shit pls don't touch kthxbye
    Board *b = new Board(6);
    Vehicle *v1 = new Vehicle(0, 0, 1, 3);
    Vehicle *v2 = new Vehicle(1, 0, 2, 1);
    b->addVehicle(v1);
    b->addVehicle(v2);
    std::string res = (b->canMove(v1, 0)) ? "true" : "false";
    cout << res << endl;
    delete b; //may leak a bit of memory!
    delete v1;
    delete v2;
    //end test
    
    sf::RenderWindow window;
    window.create(sf::VideoMode(800, 600), "Rush Hour");
    //Menu items settings
    //  Colours
    sideBarOutline.setFillColor(themeColor);
    sideBarPanel1.setFillColor(backColor);
    sideBarPanel2.setFillColor(backColor);
    btnSolve.setFillColor(themeColor);

    //  Positions
    sideBarOutline.setPosition(600.0f, 0.0f);
    sideBarPanel1.setPosition(620.0f, 20.0f);
    sideBarPanel2.setPosition(620.0f, 340.0f);
    btnSolve.setPosition(640.0f, 360.0f);
    //Menu items end
    while (window.isOpen())
    {
        sf::Event event;
        
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        window.clear(sf::Color::White);//BEGIN render list << --
        //Main board
                //Here, AND NO FURTHER. (Else order will be fucked)
        //END main board
        
        //Side menu background
        window.draw(sideBarOutline);
        window.draw(sideBarPanel1);
        window.draw(sideBarPanel2);
        window.draw(btnSolve);
        window.draw(text);
        //END menu background
        
        //Menu button
                //Buttons of the menu here.
        //END menu buttons
        
        window.display();//END render list << --
    }
    return 0;
}


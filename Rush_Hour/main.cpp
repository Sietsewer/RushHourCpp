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

int main(int argc, char** argv) {
    
    sf::RenderWindow window;
    window.create(sf::VideoMode(800, 600), "sup!");
    sf::RectangleShape sideBarOutline(sf::Vector2f(200.0f, 600.0f));
    sf::RectangleShape sideBarPanel1(sf::Vector2f(160.0f, 300.0f));
    sf::RectangleShape sideBarPanel2(sf::Vector2f(160.0f, 240.0f));
    sideBarOutline.setFillColor(themeColor);
    sideBarPanel1.setFillColor(backColor);
    sideBarPanel2.setFillColor(backColor);
    sideBarOutline.setPosition(600.0f, 0.0f);
    sideBarPanel1.setPosition(620.0f, 20.0f);
    sideBarPanel2.setPosition(620.0f, 340.0f);
    while (window.isOpen())
    {
        sf::Event event;
        
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        window.clear(sf::Color::White);//BEGIN render list << --
        window.draw(sideBarOutline);
        window.draw(sideBarPanel1);
        window.draw(sideBarPanel2);
        window.display();//END render list << --
    }
    return 0;
}


/* 
 * File:   main.cpp
 * Author: Sietse & Wessel
 *
 * Created on 11 March 2014, 11:08
 */

#include <cstdlib>
#include <SFML/Window.hpp>

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    sf::Window window;
    window.create(sf::VideoMode(800, 600), "sup!");
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
    }
    return 0;
}


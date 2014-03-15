/* 
 * File:   Button.h
 * Author: Sietse
 *
 * Created on 13 March 2014, 13:59
 */

#ifndef BUTTON_H
#define	BUTTON_H

using namespace sf;

class Button : public sf::RectangleShape{
public:
    sf::Color baseColor;
    sf::Color selectColor;
    sf::RenderWindow* window;
    Button(sf::RectangleShape rect, sf::Color _baseColor, sf::Color _selectColor, sf::RenderWindow* _window, void (*buttonClick)());
    void mouseUp();
    void mouseDown();
    bool isMouseOver();
    void (*buttonClick)();
private:
    bool isDown;
};

#endif	/* BUTTON_H */


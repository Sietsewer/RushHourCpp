/* 
 * File:   Button.cpp
 * Author: Sietse
 * 
 * Created on 13 March 2014, 13:59
 */
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "Button.h"

Button::Button(sf::RectangleShape rect, sf::Color _baseColor, sf::Color _selectColor, sf::RenderWindow* _window, void (*_buttonClick)())
: RectangleShape(rect) {
    window = _window;
    sf::RectangleShape(rect.getSize());
    setPosition(rect.getPosition());
    baseColor = _baseColor;
    selectColor = _selectColor;
    rect.setFillColor(baseColor);
    buttonClick = _buttonClick;
}

bool Button::isMouseOver() {
    sf::Vector2f mousePos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
    if (((mousePos.x > getPosition().x) && (mousePos.x < (getPosition().x + getSize().x))) &&
            ((mousePos.y > getPosition().y) && (mousePos.y < (getPosition().y + getSize().y)))) {
        setFillColor(selectColor);
        return true;
    }
    setFillColor(baseColor);
    return false;
}

void Button::mouseUp() {
    if (isDown) {
        if (isMouseOver()) {
            buttonClick();
        }
        isDown = false;
        setFillColor(baseColor);
    }
}

void Button::mouseDown() {
    isDown = isMouseOver();
}

#include "Rectangle.h"

Rectangle::Rectangle(sf::Vector2f position, sf::Vector2f dimensions, int rotation): rotation(rotation), position(position), dimensions(dimensions){ Init();}

Rectangle::Rectangle(int x, int y, int width, int height, int rotation): rotation(rotation), position(x, y), dimensions(width, height){ Init(); }

void Rectangle::Init(){
    this->shape.setSize(dimensions);
    this->shape.setPosition(position);
    this->shape.setRotation(rotation);
    this->shape.setFillColor(sf::Color(65,45,60));
}

void Rectangle::Draw(sf::RenderWindow& window){
    window.draw(this->shape);
}
#include "Rectangle.h"
#include <iostream>
#include <math.h>

float Rectangle::shadow_extension_distance = 100000;

Rectangle::Rectangle(sf::Vector2f position, sf::Vector2f dimensions, int rotation): rotation(rotation), position(position), dimensions(dimensions){ Init();}

Rectangle::Rectangle(int x, int y, int width, int height, int rotation): rotation(rotation), position(x, y), dimensions(width, height){ Init(); }

void Rectangle::Init(){
    shape.setSize(dimensions);
    shape.setPosition(position);
    shape.setRotation(rotation);
    shape.setOrigin(dimensions.x / 2.0f, dimensions.y / 2.0f);
    shape.setFillColor(sf::Color(31, 19, 28));

    shadow_shape.setPrimitiveType(sf::TriangleStrip);
    
    CalculateCorners();
}

float Rectangle::Radians(float degrees){
    return degrees * ( 3.14159 / 180 );
}

void Rectangle::CalculateCorners(){

    // using the rotation matrix defined at 
    // https://en.wikipedia.org/wiki/2D_computer_graphics#Rotation

    corners.clear(); // remove exisiting calculations 

    float halfW = dimensions.x / 2.0f;
    float halfH = dimensions.y / 2.0f;
    float angle = Radians((float)rotation);
    
    sf::Vertex point(sf::Vector2f(0,0), sf::Color::Red);


    point.position.x = position.x + (halfW * cos(angle)) - (halfH * sin(angle));
    point.position.y = position.y + (halfW * sin(angle)) + (halfH * cos(angle));
    corners.append(point);

    point.position.x = position.x - (halfW * cos(angle)) - (halfH * sin(angle));
    point.position.y = position.y - (halfW * sin(angle)) + (halfH * cos(angle));
    corners.append(point);

    point.position.x = position.x - (halfW * cos(angle)) + (halfH * sin(angle));
    point.position.y = position.y - (halfW * sin(angle)) - (halfH * cos(angle));
    corners.append(point);

    point.position.x = position.x + (halfW * cos(angle)) + (halfH * sin(angle));
    point.position.y = position.y + (halfW * sin(angle)) - (halfH * cos(angle));
    corners.append(point);
}

void Rectangle::CalculateShadowShape(sf::RenderWindow& window){
    
    shadow_shape.clear();

    sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);

    sf::Color shadow_colour = sf::Color::Black;

    for(int i = 0; i < 4; i++){

        sf::Vector2f point = corners[i].position;
        shadow_shape.append(sf::Vertex(point, shadow_colour));

        // from light source to corner
        float angle = atan2(mouse_pos.y - point.y, mouse_pos.x - point.x);
        
        sf::Vector2f point_extension = point;
        point_extension.x -= cos(angle) * shadow_extension_distance;
        point_extension.y -= sin(angle) * shadow_extension_distance;
        shadow_shape.append(sf::Vertex(point_extension, shadow_colour));
    }       
}

void Rectangle::DrawShape(sf::RenderTexture& texture){
    texture.draw(shape);
}

void Rectangle::DrawShapeCutout(sf::RenderTexture& texture){
    sf::Color previous_colour = shape.getFillColor();
    shape.setFillColor(sf::Color::White);
    
    texture.draw(shape);

    shape.setFillColor(previous_colour);
}

void Rectangle::DrawShadow(sf::RenderTexture& texture, sf::RenderWindow& window){
    CalculateShadowShape(window);
    texture.draw(shadow_shape);
}
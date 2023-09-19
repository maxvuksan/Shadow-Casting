#include "Game.h"
#include <iostream>
Game::Game():
    window_height(600),
    window_width(600),
    window(sf::VideoMode(600, 600), "Shadow Casting")
{}

void Game::Start(){
    
    rectangles.emplace_back(140,130,40,120,45);
    rectangles.emplace_back(300,450,150,200, -30);
    rectangles.emplace_back(400,160,45,55, 10);
}


void Game::Run(){



    this->Start();

    while (window.isOpen())
    {
        this->PollEvents();

        window.clear( sf::Color(65,45,60));

        this->Update();
        
        window.display();
    }

}

void Game::PollEvents(){

    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
    }
}

void Game::Update(){


    for(auto& r : rectangles){
        r.Draw(window);
    }

}

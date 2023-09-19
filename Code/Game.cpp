#include "Game.h"
#include <iostream>
Game::Game():
    window_height(600),
    window_width(600),
    window(sf::VideoMode(600, 600), "Shadow Casting"),
    shader_contents(
        "uniform sampler2D texture;"\
        "uniform vec2 u_light_position;"\
        "void main()"\
        "{"\
        "    vec2 pos = gl_TexCoord[0].xy; "\
        "    float dis = distance(pos, u_light_position) * 1.5;"\
        "    dis -= 0.2 ; "\
        "   dis = clamp(dis, 0, 1); "\
        "    gl_FragColor = vec4(vec3(1.0) - vec3(dis), 1.0);"\
        "}")
{}

void Game::Start(){
        
    if (!sf::Shader::isAvailable())
    {
        std::cout << "SHADERS ARE NOT AVAILABLE\n"; 
    }
    else{
        if (!light_shader.loadFromMemory(shader_contents, sf::Shader::Fragment))
        {
            std::cout << "ERROR LOADING light_shader\n";
        }
    }

    rectangles.emplace_back(140,130,40,120,45);
    rectangles.emplace_back(300,450,150,200, -30);
    rectangles.emplace_back(400,160,45,55, 10);
}


void Game::Run(){



    this->Start();

    while (window.isOpen())
    {
        this->PollEvents();

        window.clear();

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


    sf::RenderTexture shadow_texture;
    shadow_texture.create(window_width, window_height);
    shadow_texture.clear(sf::Color::Black);

    light_shader.setUniform("u_light_position", sf::Vector2f(sf::Mouse::getPosition(window).x / (float)window_width, sf::Mouse::getPosition(window).y / (float)window_height));

    sf::RenderTexture light_draw_object;
    light_draw_object.create(window_width, window_height);

    shadow_texture.draw(sf::Sprite(light_draw_object.getTexture()), &light_shader);

    for(auto& r : rectangles){
        r.DrawShadow(shadow_texture, window);
    }
    for(auto& r : rectangles){
        r.DrawShapeCutout(shadow_texture);
    }
    shadow_texture.display();

    sf::RenderTexture final_texture;
    final_texture.create(window_width, window_height);
    final_texture.clear(sf::Color(47,34,50));

    for(auto& r : rectangles){
        r.DrawShape(final_texture);
    }
    final_texture.draw(sf::Sprite(shadow_texture.getTexture()), sf::BlendMultiply);

    final_texture.display();
    
    window.draw(sf::Sprite(final_texture.getTexture()));

}

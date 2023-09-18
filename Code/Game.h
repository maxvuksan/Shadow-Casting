#include <SFML/Graphics.hpp>
#include "Rectangle.h"

class Game{

    public:      
        Game();
        void Run();

    private:

        sf::RenderWindow window;
        int window_width;
        int window_height;

        std::vector<Rectangle> rectangles;

        void Start();
        void PollEvents();
        void Update();
        

};
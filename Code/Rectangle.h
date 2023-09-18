#include <SFML/Graphics.hpp>

class Rectangle{

    public:
        Rectangle(sf::Vector2f position, sf::Vector2f dimensions, int rotation=0);
        Rectangle(int x, int y, int width, int height, int rotation=0);

        void Draw(sf::RenderWindow& window);

    private:
        void Init();

        sf::Vector2f position;
        sf::Vector2f dimensions;
        int rotation;
    
        sf::RectangleShape shape;

};
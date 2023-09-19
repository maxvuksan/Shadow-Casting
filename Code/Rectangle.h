#include <SFML/Graphics.hpp>

class Rectangle{

    public:
        Rectangle(sf::Vector2f position, sf::Vector2f dimensions, int rotation=0);
        Rectangle(int x, int y, int width, int height, int rotation=0);

        void Draw(sf::RenderWindow& window);

    private:
        void Init();
        void CalculateCorners();    
        void CalculateShadowShape(sf::RenderWindow& window);

        // converts degrees to radians
        float Radians(float degrees);    

        sf::Vector2f position;
        sf::Vector2f dimensions;
        int rotation;


        sf::VertexArray corners;    
        sf::VertexArray shadow_shape;

        static float shadow_extension_distance;

        sf::RectangleShape shape;

};
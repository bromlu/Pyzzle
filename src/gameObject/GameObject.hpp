#include <SFML/Graphics.hpp>
using namespace std;

class GameObject {
    public:
    GameObject(int globalIndex);

    float getX();
    float getY();
    void setX(float x);
    void setY(float y);

    float getAnimationElapsedTime();
    void restartAnimationClock();

    sf::Sprite* addSprite(int index);
    sf::Sprite* getSprite(int index);
    void addSprite(string fileName);

    void draw(sf::RenderWindow* window);

    private:
    int globalIndex;
    float x;
    float y;
    vector<sf::Sprite> sprites;
    vector<sf::Texture> textures;
    sf::Clock animationClock;
};
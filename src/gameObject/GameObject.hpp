#include <SFML/Graphics.hpp>
using namespace std;

class GameObject {
    public:
    GameObject(int globalIndex);

    sf::Vector2f getPosition();
    void setPosition(sf::Vector2f position);
    void move(sf::Vector2f distance);

    float getAnimationElapsedTime();
    void restartAnimationClock();

    sf::Sprite* addSprite(int index);
    sf::Sprite* getSprite(int index);
    void addSprite(string fileName);

    int getAnimation(int index);
    int addAnimation(int y);

    void draw(sf::RenderWindow* window);

    private:
    int globalIndex;
    sf::Vector2f position;
    vector<sf::Sprite> sprites;
    vector<sf::Texture> textures;
    vector<int> animations;
    sf::Clock animationClock;
};
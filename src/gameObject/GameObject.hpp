#include <SFML/Graphics.hpp>
#include "Animation.hpp"
using namespace std;

class GameObject {
    public:
    GameObject(int globalIndex);

    sf::Vector2f getPosition();
    void setPosition(sf::Vector2f position);
    void move(sf::Vector2f distance);

    float getAnimationElapsedTime();
    void restartAnimationClock();

    sf::Sprite* getSprite();
    void addSprite(string fileName);

    int getAnimation(int index);
    int addAnimation();
    void addAnimationFrame(long index, long x, long y, long width, long height);
    void addAnimationFrames(long index, long fromX, long fromY, long toX, long toY, long width, long height);

    void draw(sf::RenderWindow* window);

    private:
    int globalIndex;
    sf::Vector2f position;
    sf::Sprite sprite;
    sf::Texture texture;
    vector<Animation> animations;
    sf::Clock animationClock;
};
#ifndef GAMEOBJECT
#define GAMEOBJECT

#include <SFML/Graphics.hpp>
using namespace std;

class Animation;

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

    int addAnimation();
    void addAnimationFrame(long index, long x, long y, long width, long height);
    void addAnimationFrames(long index, long fromX, long fromY, long toX, long toY, long width, long height);
    Animation* getAnimation(int index);

    void draw(sf::RenderWindow* window);

    private:
    int globalIndex;
    sf::Vector2f position;
    sf::Sprite sprite;
    sf::Texture texture;
    vector<Animation> animations;
    sf::Clock animationClock;
};

#endif
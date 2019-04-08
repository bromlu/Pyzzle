#ifndef ANIMATION
#define ANIMATION

#include <SFML/Graphics.hpp>
using namespace std;

class GameObject;

class Animation {
    public:
    Animation(int textrueWidth, GameObject* gameObject);

    void addAnimationFrame(long x, long y, long width, long height);
    void addAnimationFrames(long fromX, long fromY, long toX, long toY, long width, long height);
    void animate();

    void setGlobalIndex(long index);
    long getGlobalIndex();

    private:
    sf::IntRect getNextFrame();

    int textureWidth;
    int currentFrame;
    long globalIndex;
    GameObject* gameObject;
    vector<sf::IntRect > animationFrames;
};

#endif
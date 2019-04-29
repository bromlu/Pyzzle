#ifndef ANIMATION
#define ANIMATION

#include <SFML/Graphics.hpp>
using namespace std;

class GameObject;

class Animation {
    public:
    Animation(int textrueWidth, GameObject* gameObject);

    void addAnimationFrame(int x, int y, int width, int height);
    void addAnimationFrames(int fromX, int fromY, int toX, int toY, int width, int height);
    void animate();

    void setDelay(float delay);

    void pause();
    void resume();
    void stop();

    private:
    sf::IntRect getNextFrame();

    int textureWidth;
    int currentFrame;
    float delay;
    bool paused;
    GameObject* gameObject;
    vector<sf::IntRect > animationFrames;
};

#endif
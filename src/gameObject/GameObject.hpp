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
    void addAnimationFrame(int index, int x, int y, int width, int height);
    void addAnimationFrames(int index, int fromX, int fromY, int toX, int toY, int width, int height);
    Animation* getAnimation(int index);

    void draw(sf::RenderWindow* window);

	void addRect(int left, int top, int width, int height);
	sf::Rect<float> getGlobalRect(int index);
	void drawCollisionObjects(sf::RenderWindow* window);
	bool contains(sf::Vector2f p);
	bool collides(GameObject* other);
	bool intersects(float x1, float y1, float x2, float y2);
    int getActiveAnimationLocalIndex();
    int getActiveAnimationGlobalIndex();

    void playAnimation(int globalIndex, int localIndex);
    void stopAnimation();
    void pauseAnimation();
    void resumeAnimation();


    private:
    int globalIndex;
    int activeAnimationLocalIndex;
    int activeAnimationGlobalIndex;
    sf::Vector2f position;
	vector<sf::Rect<float> > rects;
    sf::Sprite sprite;
    sf::Texture texture;
    vector<Animation> animations;
    sf::Clock animationClock;
};

#endif

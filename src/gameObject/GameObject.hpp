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

    void draw(sf::RenderWindow* window);

	void addRect(int left, int top, int width, int height);
	sf::Rect<float> getGlobalRect(int index);
	void drawCollisionObjects(sf::RenderWindow* window);
	bool contains(sf::Vector2f p);
	bool collides(GameObject* other);
	bool intersects(float x1, float y1, float x2, float y2);

    private:
    int globalIndex;
    sf::Vector2f position;
    vector<sf::Sprite> sprites;
    vector<sf::Texture> textures;
	vector<sf::Rect<float> > rects;
    sf::Clock animationClock;
};

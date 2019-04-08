#include <SFML/Graphics.hpp>
using namespace std;

class Animation {
    public:
    Animation(int textrueWidth);

    void addAnimationFrame(long x, long y, long width, long height);
    void addAnimationFrames(long fromX, long fromY, long toX, long toY, long width, long height);

    private:
    int textureWidth;
    vector<sf::Rect<long> > animationFrames;
};
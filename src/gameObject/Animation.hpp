#include <SFML/Graphics.hpp>
using namespace std;

class Animation {
    public:
    Animation();

    private:
    vector<sf::IntRect> animationFrames;
};
#include <SFML/Graphics.hpp>
#include "Animation.hpp"
#include <iostream>
using namespace std;

Animation::Animation(int textureWidth) {
    this->textureWidth = textureWidth;
}

void Animation::addAnimationFrame(long x, long y, long width, long height) {
    this->animationFrames.push_back(sf::Rect<long>(x, y, width, height));
}

void Animation::addAnimationFrames(long fromX, long fromY, long toX, long toY, long width, long height) {
    for (long y = fromY; y <= toY; y += height) {
        for (long x = fromX; x <= textureWidth && (x <= toX || y<=toY); x+= width) {
            this->animationFrames.push_back(sf::Rect<long>(x, y, width, height));
        }
    }
}
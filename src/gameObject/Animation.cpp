#include <SFML/Graphics.hpp>
#include "GameObject.hpp"
#include "Animation.hpp"
#include <iostream>
using namespace std;

Animation::Animation(int textureWidth, GameObject* gameObject) {
    this->textureWidth = textureWidth;
    this->gameObject = gameObject;
    this->currentFrame = 0;
    this->globalIndex = -1;
    this->paused = false;
    this->delay = 0.1;
}

sf::IntRect Animation::getNextFrame() {
    currentFrame = (currentFrame + 1) % this->animationFrames.size();
    return this->animationFrames.at(currentFrame);
}

void Animation::addAnimationFrame(long x, long y, long width, long height) {
    this->animationFrames.push_back(sf::IntRect(x, y, width, height));
}

void Animation::addAnimationFrames(long fromX, long fromY, long toX, long toY, long width, long height) {
    for (long y = fromY; y <= toY; y += height) {
        for (long x = fromX; x <= textureWidth && !(x > toX && y >= toY); x+= width) {
            this->animationFrames.push_back(sf::IntRect(x, y, width, height));
        }
    }
}

void Animation::setDelay(float delay) {
    this->delay = delay;
}

void Animation::animate() {
    if(this->paused || this->gameObject->getAnimationElapsedTime() < this->delay){
        return;
    }
    this->gameObject->restartAnimationClock();
    this->gameObject->getSprite()->setTextureRect(this->getNextFrame());
}

void Animation::pause() {
    this->paused = true;
}

void Animation::resume() {
    this->paused = false;
}

void Animation::start(long index) {
    this->globalIndex = index;
}

void Animation::stop() {
    this->globalIndex = -1;
    this->currentFrame = 0;
    this->paused = false;
}

long Animation::getGlobalIndex() {
    return this->globalIndex;
}
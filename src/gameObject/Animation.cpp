#include <SFML/Graphics.hpp>
#include "GameObject.hpp"
#include "Animation.hpp"
#include <iostream>
using namespace std;

Animation::Animation(int textureWidth, GameObject* gameObject) {
    this->textureWidth = textureWidth;
    this->gameObject = gameObject;
    this->currentFrame = 0;
    this->paused = false;
    this->delay = 0.1;
}

sf::IntRect Animation::getNextFrame() {
    currentFrame = (currentFrame + 1) % this->animationFrames.size();
    return this->animationFrames.at(currentFrame);
}

void Animation::addAnimationFrame(int x, int y, int width, int height) {
    this->animationFrames.push_back(sf::IntRect(x, y, width, height));
}

void Animation::addAnimationFrames(int fromX, int fromY, int toX, int toY, int width, int height) {
    for (int y = fromY; y <= toY; y += height) {
        for (int x = fromX; x <= textureWidth && !(x > toX && y >= toY); x+= width) {
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

void Animation::stop() {
    this->currentFrame = -1;
    this->gameObject->getSprite()->setTextureRect(this->getNextFrame());
    this->paused = false;
}
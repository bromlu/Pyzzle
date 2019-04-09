#include <SFML/Graphics.hpp>
#include "GameObject.hpp"
#include "Animation.hpp"
#include <iostream>
using namespace std;

GameObject::GameObject(int globalIndex) {
    this->globalIndex = globalIndex;
    this->position = sf::Vector2f(0.0, 0.0);
    this->activeAnimationGlobalIndex = -1;
    this->activeAnimationLocalIndex = -1;
}

sf::Vector2f GameObject::getPosition() {
    return this->position;
}

void GameObject::setPosition(sf::Vector2f position) {
    this->position = position;
    this->sprite.setPosition(position);
}

void GameObject::move(sf::Vector2f distance) {
    this->position += distance;
    this->sprite.move(distance);
}

float GameObject::getAnimationElapsedTime() {
    return this->animationClock.getElapsedTime().asSeconds();
}

void GameObject::restartAnimationClock() {
    this->animationClock.restart();
}

int GameObject::addAnimation() {
    this->animations.push_back(Animation(this->sprite.getTexture()->getSize().x, this));
    return this->animations.size() - 1;
}

void GameObject::addAnimationFrame(int index, int x, int y, int width, int height) {
    this->animations.at(index).addAnimationFrame(x, y, width, height);
}

void GameObject::addAnimationFrames(int index, int fromX, int fromY, int toX, int toY, int width, int height) {
    this->animations.at(index).addAnimationFrames(fromX, fromY, toX, toY, width, height);
}

Animation* GameObject::getAnimation(int index) {
    return &(this->animations.at(index));
}

void GameObject::addSprite(string fileName) {
    this->texture = sf::Texture();
    texture.loadFromFile(fileName);

    this->sprite = sf::Sprite(this->texture);
    this->sprite.setPosition(this->position);
    this->sprite.setScale(5, 5);
}

sf::Sprite* GameObject::getSprite() {
    return &(this->sprite);
}

void GameObject::draw(sf::RenderWindow* window) {  
    window->draw(this->sprite);  
}

int GameObject::getActiveAnimationLocalIndex() {
    return this->activeAnimationLocalIndex;
}

int GameObject::getActiveAnimationGlobalIndex() {
    return this->activeAnimationGlobalIndex;
}

void GameObject::playAnimation(int globalIndex, int localIndex) {
    this->activeAnimationGlobalIndex = globalIndex;
    this->activeAnimationLocalIndex = localIndex;
}

void GameObject::stopAnimation() {
    this->animations.at(activeAnimationLocalIndex).stop();
    this->activeAnimationGlobalIndex = -1;
    this->activeAnimationLocalIndex = -1;
}

void GameObject::pauseAnimation() {
    this->animations.at(activeAnimationLocalIndex).pause();
}

void GameObject::resumeAnimation() {
    this->animations.at(activeAnimationLocalIndex).resume();
}

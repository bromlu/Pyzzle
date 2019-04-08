#include <SFML/Graphics.hpp>
#include "GameObject.hpp"
#include <iostream>
using namespace std;

GameObject::GameObject(int globalIndex) {
    this->globalIndex = globalIndex;
    this->position = sf::Vector2f(0.0, 0.0);
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
    this->animations.push_back(Animation(this->sprite.getTexture()->getSize().x));
    return this->animations.size() - 1;
}

void GameObject::addAnimationFrame(long index, long x, long y, long width, long height) {
    this->animations.at(index).addAnimationFrame(x, y, width, height);
}

void GameObject::addAnimationFrames(long index, long fromX, long fromY, long toX, long toY, long width, long height) {
    this->animations.at(index).addAnimationFrames(fromX, fromY, toX, toY, width, height);
}

int GameObject::getAnimation(int index) {
    return 0;
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
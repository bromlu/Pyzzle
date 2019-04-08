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

int GameObject::addAnimationFrame(sf::IntRect frame) {
    return 0;
}

int GameObject::addAnimationFrames(sf::IntRect startFrame, sf::IntRect endFrame) {
    return 0;
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
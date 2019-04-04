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
    for (std::vector<sf::Sprite>::iterator it = this->sprites.begin(); it != this->sprites.end(); ++it) {
        it->setPosition(position);
    }
}

void GameObject::move(sf::Vector2f distance) {
    this->position += distance;
    for (std::vector<sf::Sprite>::iterator it = this->sprites.begin(); it != this->sprites.end(); ++it) {
        it->move(distance);
    }
}

float GameObject::getAnimationElapsedTime() {
    return this->animationClock.getElapsedTime().asSeconds();
}

void GameObject::restartAnimationClock() {
    this->animationClock.restart();
}

int GameObject::addAnimation(int y) {
    this->animations.push_back(y);
    return (this->animations.size() - 1);
}

int GameObject::getAnimation(int index) {
    return this->animations.at(index);
}

void GameObject::addSprite(string fileName) {
    sf::Texture texture = sf::Texture();
    texture.loadFromFile(fileName);
    this->textures.push_back(texture);

    sf::Sprite sprite(this->textures.at(this->textures.size() - 1));
    sprite.setPosition(this->position);
    sprite.setScale(5, 5);
    this->sprites.push_back(sprite);
}

sf::Sprite* GameObject::getSprite(int index) {
    return &(this->sprites.at(index));
}

void GameObject::draw(sf::RenderWindow* window) {    
    for (std::vector<sf::Sprite>::iterator it = this->sprites.begin(); it != this->sprites.end(); ++it) {
        window->draw(*it);
    }
}
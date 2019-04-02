#include <SFML/Graphics.hpp>
#include "GameObject.hpp"
#include <iostream>
using namespace std;

GameObject::GameObject(int globalIndex) {
    this->globalIndex = globalIndex;
    this->x = 0.0;
    this->y = 0.0;
}

float GameObject::getX() {
    return this->x;
}

float GameObject::getY() {
    return this->y;
}

void GameObject::setX(float x) {
    this->x = x;
}

void GameObject::setY(float y) {
    this->y = y;
}

float GameObject::getAnimationElapsedTime(){
    return this->animationClock.getElapsedTime().asSeconds();
}

void GameObject::restartAnimationClock(){
    this->animationClock.restart();
}

void GameObject::addSprite(string fileName) {
    sf::Texture texture = sf::Texture();
    texture.loadFromFile(fileName);
    this->textures.push_back(texture);

    sf::Sprite sprite(this->textures.at(this->textures.size() - 1));
    sprite.setPosition(this->x, this->y);
    sprite.setScale(5, 5);
    this->sprites.push_back(sprite);
}

sf::Sprite* GameObject::getSprite(int index) {
    return &(this->sprites.at(index));
}

void GameObject::draw(sf::RenderWindow* window) {    
    for (std::vector<sf::Sprite>::iterator it = this->sprites.begin(); it != this->sprites.end(); ++it) {
        window->draw((*it));
    }
}
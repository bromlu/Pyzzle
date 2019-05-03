#include <SFML/Graphics.hpp>
#include "GameObject.hpp"
#include "./../collision/collision_includes.cpp"
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
    sf::Vector2f offset(this->sprite.getGlobalBounds().width / 2, this->sprite.getGlobalBounds().height / 2);
    cout << this->sprite.getGlobalBounds().width << endl;
    cout << offset.x << " : " << offset.y << endl;
    this->sprite.setPosition(position - offset);
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
    if(activeAnimationLocalIndex != -1) {
        this->animations.at(activeAnimationLocalIndex).pause();
    }
}

void GameObject::resumeAnimation() {
    if(activeAnimationLocalIndex != -1) {
        this->animations.at(activeAnimationLocalIndex).resume();
    }
}

void GameObject::addRect(int left, int top, int width, int height) {
	sf::Rect<float> rect((float)left, (float)top, (float)width, (float)height);
	this->rects.push_back(rect);
}

sf::Rect<float> GameObject::getGlobalRect(int index) {
	sf::Rect<float> ret(this->rects[index]);
	ret.left += this->position.x;
	ret.top += this->position.y;
	return ret;
}

void GameObject::drawCollisionObjects(sf::RenderWindow* window) {
	for(unsigned int i = 0; i < this->rects.size(); i++) {
		sf::Rect<float> rect = this->getGlobalRect(i);
		sf::RectangleShape drawRect(sf::Vector2f(rect.width - 2, rect.height - 2));
		drawRect.setPosition(sf::Vector2f(rect.left + 1, rect.top + 1));
		drawRect.setFillColor(sf::Color::Transparent);
		drawRect.setOutlineThickness(1);
		drawRect.setOutlineColor(sf::Color(0, 255, 0));
		window->draw(drawRect);
	} 
}

bool GameObject::contains(sf::Vector2f p) {
	for(unsigned int i = 0; i < this->rects.size(); i++) {
		if(this->getGlobalRect(i).contains(p))
			return true;
	}
	return false;
}

bool GameObject::collides(GameObject* other) {
	for(unsigned int i = 0; i < this->rects.size(); i++) {
		sf::Rect<float> rect = this->getGlobalRect(i);
		for(unsigned int j = 0; j < other->rects.size(); j++) {
			if(rect.intersects(other->getGlobalRect(j)))
				return true;
		}
	}
	return false;
}

bool GameObject::intersects(float x1, float y1, float x2, float y2) {
	for(unsigned int i = 0; i < this->rects.size(); i++) {
		sf::Rect<float> rect = this->getGlobalRect(i);

		if(lineLine(x1, y1, x2, y2, rect.left, rect.top, rect.left + rect.width, rect.top))
			return true;
		if(lineLine(x1, y1, x2, y2, rect.left, rect.top, rect.left, rect.top + rect.height))
			return true;
		if(lineLine(x1, y1, x2, y2, rect.left + rect.width, rect.top, rect.left + rect.width, rect.top))
			return true;
		if(lineLine(x1, y1, x2, y2, rect.left, rect.top + rect.height, rect.left, rect.top + rect.height))
			return true;
	}

	return false;
}


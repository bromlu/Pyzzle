#include <SFML/Graphics.hpp>
#include "GameObject.hpp"
#include "./../collision/collision_includes.cpp"
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


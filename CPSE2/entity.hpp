#pragma once

#include <SFML\Graphics.hpp>

class Entity {
protected:
	sf::Vector2f position;
	sf::Vector2f size;
	sf::Color color;
public:
	Entity(sf::Vector2f position, sf::Vector2f size, sf::Color color);

	virtual void draw(sf::RenderWindow & window) const = 0;
	virtual void update(sf::RenderWindow & window) = 0;

	virtual void move(sf::Vector2f delta);
	virtual void jump(sf::Vector2f target);
	virtual void jump(sf::Vector2i target);

	virtual void interact(const Entity& other) {};

protected:
	bool overlaps(const Entity & other);
};


#pragma once

#include <SFML\Graphics.hpp>
#include "entity.hpp"

class Rectangle: public Entity {
private:
	sf::RectangleShape rectangle;
public:
	Rectangle(sf::Vector2f position, sf::Color color, sf::Vector2f size);

	void draw(sf::RenderWindow& window) const override;
	void update(sf::RenderWindow& window) override;
};


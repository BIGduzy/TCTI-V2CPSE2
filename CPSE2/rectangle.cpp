#include "rectangle.hpp"

Rectangle::Rectangle(sf::Vector2f position, sf::Color color, sf::Vector2f size):
	Entity(position, size, color),
	rectangle(size)
{
	rectangle.setFillColor(color);
}

void Rectangle::draw(sf::RenderWindow& window) const {
	window.draw(rectangle);
}

void Rectangle::update(sf::RenderWindow& window) {
	rectangle.setPosition(position);
}
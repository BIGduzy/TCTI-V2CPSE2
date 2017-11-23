#include "ball.hpp"
#include <math.h>

Ball::Ball(sf::Vector2f position, sf::Color color, float size):
	Entity(position, sf::Vector2f(size * 2, size * 2), color),
	circle(size),
	velocity(speed, speed)
{
	circle.setFillColor(color);
}

void Ball::draw(sf::RenderWindow & window) const {
	window.draw(circle);
}

void Ball::update(sf::RenderWindow & window) {
	move(velocity);
	circle.setPosition(position);
}

#include <iostream>

void Ball::interact(const Entity& other) {
	if (overlaps(other)) {
		float angle = atan2f(velocity.y, velocity.x) - 3.141592654f / 2;

		velocity.x = cos(angle) * speed;
		velocity.y = sin(angle) * speed;
		move(velocity); // Move out of entity
	}
};

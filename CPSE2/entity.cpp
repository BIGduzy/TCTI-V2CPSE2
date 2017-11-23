#include "entity.hpp"

Entity::Entity(sf::Vector2f position, sf::Vector2f size, sf::Color color):
	position(position),
	size(size),
	color(color)
{}

void Entity::move(sf::Vector2f delta) {
	position += delta;
}

void Entity::jump(sf::Vector2f target) {
	position = target;
}

void Entity::jump(sf::Vector2i target) {
	jump(sf::Vector2f(
		static_cast< float >(target.x),
		static_cast< float >(target.y)
	));
}

bool within(float x, float a, float b) {
	return (x >= a) && (x <= b);
}

bool Entity::overlaps(const Entity & other) {
	bool x_overlap = within(
		position.x,
		other.position.x,
		other.position.x + other.size.x
	) || within(
		other.position.x,
		position.x,
		position.x + size.x
	);

	bool y_overlap = within(
		position.y,
		other.position.y,
		other.position.y + other.size.y
	) || within(
		other.position.y,
		position.y,
		position.y + size.y
	);

	return x_overlap && y_overlap;
}
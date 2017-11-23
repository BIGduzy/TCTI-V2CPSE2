#pragma once
#include <SFML/Graphics.hpp>
#include "entity.hpp"

class Ball: public Entity {
private:
	static const uint8_t speed = 6;
	sf::CircleShape circle;
	sf::Vector2f velocity;
public:
	Ball(sf::Vector2f position, sf::Color color, float size = 30.0);

	void draw(sf::RenderWindow & window) const override;
	void update(sf::RenderWindow & window) override;

	void interact(const Entity& other) override;
};
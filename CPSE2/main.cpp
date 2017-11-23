#include <iostream>
#include <functional>
#include <SFML/Graphics.hpp>

#include "entity.hpp"
#include "ball.hpp"
#include "rectangle.hpp"

class action {
private:
	std::function< bool() > condition;
	std::function< void() > work;
public:
	action(
		std::function< bool() > condition,
		std::function< void() > work
	) : condition(condition),
		work(work)
	{}

	action(
		sf::Keyboard::Key key,
		std::function< void() > work
	) :
		condition(
			[key]()->bool { return sf::Keyboard::isKeyPressed(key); }
		),
		work(work)
	{}

	action(
		sf::Mouse::Button button,
		std::function< void() > work
	) :
		condition(
			[button]()->bool { return sf::Mouse::isButtonPressed(button); }
		),
		work(work)
	{}

	void operator()() {
		if (condition()) {
			work();
		}
	}
};

int main(int argc, char *argv[]) {
	std::cout << "Starting application Week 2\n";

	constexpr const float windowWidth = 640.0;
	constexpr const float windowHeight = 480.0;
	constexpr const uint8_t rectSize = 40;

	sf::RenderWindow window{ sf::VideoMode{ static_cast<unsigned int>(windowWidth), static_cast<unsigned int>(windowHeight) }, "SFML window" };

	

	Ball my_ball(sf::Vector2f{ 100.0, 100.0 }, sf::Color(55, 44, 255));
	Ball my_ball2(sf::Vector2f{ 500, 50.0 }, sf::Color(255, 44, 255));
	Rectangle wallUpper(sf::Vector2f(0.0, 0.0), sf::Color(22, 22, 22), sf::Vector2f(windowWidth, rectSize));
	Rectangle wallRight(sf::Vector2f(windowWidth - rectSize, 0.0), sf::Color(22, 22, 22), sf::Vector2f(rectSize, windowHeight));
	Rectangle wallLower(sf::Vector2f(0.0, windowHeight - rectSize), sf::Color(22, 22, 22), sf::Vector2f(windowWidth, rectSize));
	Rectangle wallLeft(sf::Vector2f(0.0, 0.0), sf::Color(22, 22, 22), sf::Vector2f(rectSize, windowHeight));
	Rectangle block(sf::Vector2f(windowWidth / 2 - rectSize, windowHeight / 2 - rectSize), sf::Color(255, 22, 22), sf::Vector2f(rectSize, rectSize));
	Entity* entities[] = {
		&my_ball,
		&my_ball2,
		&wallUpper,
		&wallRight,
		&wallLower,
		&wallLeft,
		&block
	};

	action actions[] = {
		action(sf::Keyboard::Left,  [&]() { block.move(sf::Vector2f(-1.0,  0.0)); }),
		action(sf::Keyboard::Right, [&]() { block.move(sf::Vector2f(+1.0,  0.0)); }),
		action(sf::Keyboard::Up,    [&]() { block.move(sf::Vector2f(0.0, -1.0)); }),
		action(sf::Keyboard::Down,  [&]() { block.move(sf::Vector2f(0.0, +1.0)); }),
		action(sf::Mouse::Left,     [&]() { block.jump(sf::Mouse::getPosition(window)); })
	};

	while (window.isOpen()) {
		for (auto & action : actions) {
			action();
		}

		window.clear(sf::Color(55, 55, 55));
		for (auto& entity : entities) {
			entity->update(window);
			entity->draw(window);

			for (auto& other : entities) {
				if (entity != other) {
					entity->interact(*other);
				}
			}
		}
		window.display();

		sf::sleep(sf::milliseconds(20));

		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
	}

	std::cout << "Terminating application\n";
	return 0;
}


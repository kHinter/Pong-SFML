#include <SFML/Graphics.hpp>
#include <random>
#include <iostream>

#include "dottedLine.hpp"
#include "ball.hpp"
#include "infos.hpp"
#include "Events.hpp"

void setPlayersPlates(const sf::RenderWindow& window, sf::RectangleShape& a, sf::RectangleShape& b)
{
	constexpr double marginX = 30;

	a.setPosition(marginX, window.getSize().y / 2);
	b.setPosition(window.getSize().x - (marginX + b.getSize().x), window.getSize().y / 2);
}

int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Pong", sf::Style::Titlebar | sf::Style::Close , settings);
	constexpr unsigned FramerateLimit = 60;
	window.setFramerateLimit(FramerateLimit);

	sf::RectangleShape plate1(sf::Vector2f(20, 100));
	sf::RectangleShape plate2(sf::Vector2f(20, 100));

	setPlayersPlates(window, plate1, plate2);

	dottedLine middleLine(sf::Vector2f(6, 20), 15, 20, dottedLine::Axis::y);
	middleLine.setPosition(sf::Vector2f(window.getSize().x/2 - 3, 10));

	sf::Font font;
	if (!font.loadFromFile("counter.ttf"))
	{
		std::cerr << "Cannot open this file !" << std::endl;
	}

	constexpr std::size_t textSize = 50;
	sf::Text PlayerCounter("0", font, textSize);
	sf::Text AICounter("0", font, textSize);

	Ball ball(10.f);
	ball.setSpeed(6.f);

	unsigned playerPoints = 0;
	unsigned aiPoints = 0;

	sf::Event event;
	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		ball.update(plate1, plate2);
		pointsCount(ball, playerPoints, aiPoints);

		//adapt the player plate position to mouseX position
		plate1.setPosition(plate1.getPosition().x, sf::Mouse::getPosition(window).y);

		window.clear();
		//draw all entities
		window.draw(middleLine);
		window.draw(plate1);
		window.draw(plate2);
		window.draw(ball);

		window.display();
	}
	return 0;
}
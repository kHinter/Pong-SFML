#include "ball.hpp"
#include "infos.hpp"

#include <SFML/Graphics.hpp>
#include <cassert>
#include <random>
#include <cmath>
#include <iostream>

Ball::Ball(float radius)
	: m_radius(radius), m_bounds(-m_radius, -m_radius, m_radius, m_radius)
{
	assert(m_radius > 0.0);
}

void Ball::setSpeed(float speed)
{
	m_speed = speed;
}

float Ball::getSize() const
{
	return m_radius;
}

float Ball::getSpeed() const
{
	return m_speed;
}

const sf::FloatRect& Ball::getLocalBounds() const
{
	return m_bounds;
}

const sf::FloatRect& Ball::getGlobalBounds() const
{
	return getTransform().transformRect(getLocalBounds());
}

void Ball::launch()
{
	if (m_clock.getElapsedTime().asSeconds() >= 1.5)
	{
		std::random_device seed;
		std::default_random_engine rnd(seed());
		std::uniform_real_distribution<> randomAngle(-m_speed, m_speed);

		m_velocity.x = randomAngle(rnd);
		m_velocity.y = sin(acos(m_velocity.x / m_speed)) * m_speed;

		//set Position at middle dottedLine
		std::uniform_real_distribution<> randomPosX(0, SCREEN_HEIGHT/2);
		setPosition(sf::Vector2f(SCREEN_WIDTH / 2 - getSize() / 2, randomPosX(rnd)));

		m_clock.restart();
	}
}

void Ball::update()
{
	//check collisions
	if (getPosition().y >= SCREEN_HEIGHT || getPosition().y <= 0)
	{
		m_velocity.y = -m_velocity.y;
	}
	move(m_velocity);
	std::clog << "Ball x : " << getPosition().x << "\tBall y : " << getPosition().y << std::endl;
}

void Ball::update(const sf::RectangleShape& shape1, const sf::RectangleShape& shape2)
{
	//check if the ball collide to a shape
	if (getGlobalBounds().intersects(shape1.getGlobalBounds()) || getGlobalBounds().intersects(shape2.getGlobalBounds()))
	{
		m_velocity.x = -m_velocity.x;
	}
	//check if a ball collide the x borders
	else if (getPosition().y >= SCREEN_HEIGHT || getPosition().y <= 0)
	{
		m_velocity.y = -m_velocity.y;
	}
	move(m_velocity);
	std::clog << "Ball x : " << getPosition().x << "\tBall y : " << getPosition().y << std::endl;
}

void Ball::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	states.texture = nullptr;
	target.draw(m_vertices, states);
}

void Ball::initVertices()
{
	constexpr double vertexCount = 360; //number of vertices to draw

	m_vertices.setPrimitiveType(sf::TrianglesFan);
	m_vertices.resize(vertexCount);

	//initialise the center
	m_vertices[0].position = sf::Vector2f(0, 0);

	double vertexAngle = 360 / vertexCount;
	double angle = 360;
	for (std::size_t i = 1; i < vertexCount; ++i)
	{
		double x = std::cos(angle) * m_radius;
		double y = std::sin(angle) * m_radius;

		m_vertices[i].position = sf::Vector2f(x, y);
		angle -= vertexAngle;
	}
}

void Ball::calculateReboundTrajectory()
{

}
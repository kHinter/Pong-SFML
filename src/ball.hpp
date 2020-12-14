#ifndef BALL_HPP
#define BALL_HPP

#include <SFML/Graphics.hpp>

enum class Turn
{
	Player,
	AI
};

class Ball : public sf::Drawable, public sf::Transformable
{
public:
	Ball() = delete;
	Ball(float radius);

	Ball(const Ball& cpy) = delete;
	Ball& operator=(const Ball& cpy) = delete;

	Ball(Ball&& move) = default;
	Ball& operator=(Ball&& move) = default;

	virtual ~Ball() = default;

	float getSize() const;
	float getSpeed() const;

	const sf::FloatRect& getLocalBounds() const;
	const sf::FloatRect& getGlobalBounds() const;

	void setSpeed(float speed);

	void launch();
	void update();
	void update(const sf::RectangleShape& shape1, const sf::RectangleShape& shape2);

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void initVertices();
	void calculateReboundTrajectory();
	float m_radius;
	float m_speed{ 0 };
	sf::FloatRect m_bounds;
	sf::Clock m_clock;
	sf::Vector2f m_velocity{ 0, 0 };
	sf::VertexArray m_vertices;
};

#endif
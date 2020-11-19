#ifndef MIDDLE_HPP
#define MIDDLE_HPP

#include <SFML/Graphics.hpp>
#include <cassert>

class dottedLine : public sf::Drawable, public sf::Transformable
{
public:
	enum class Axis
	{
		x,
		y
	};

	explicit dottedLine(const sf::Vector2f& dotSize, unsigned dotCount, float gapLength, Axis axis);

	dottedLine() = delete;
	dottedLine(const dottedLine& cpy) = delete;
	dottedLine& operator=(const dottedLine& cpy) = delete;
	
	dottedLine(dottedLine&& move) = delete;
	dottedLine& operator=(dottedLine&& move) = delete;

	virtual ~dottedLine() = default;

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	sf::VertexArray m_vertices;
	sf::Vector2f m_dotSize;
	float m_gapLength;
	unsigned m_dotCount;
	Axis m_axis;
};

#endif
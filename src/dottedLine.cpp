#include "dottedLine.hpp"
#include <SFML/Graphics.hpp>
#include <cassert>

dottedLine::dottedLine(const sf::Vector2f& dotSize, unsigned dotCount, float gapLength, Axis axis)
	: m_dotSize(dotSize), m_dotCount(dotCount), m_gapLength(gapLength), m_axis(axis)
{
	assert(m_gapLength >= 0);
	assert(m_dotCount > 0);

	m_vertices.setPrimitiveType(sf::Quads);
	m_vertices.resize(m_dotCount * 4);

	float totalGapLength = 0;
	if (m_axis == Axis::x)
	{
		for (unsigned i = 0; i < m_vertices.getVertexCount() / 4; ++i)
		{
			m_vertices[0 + i * 4].position = sf::Vector2f(totalGapLength, 0);
			m_vertices[1 + i * 4].position = sf::Vector2f(m_dotSize.x + totalGapLength, 0);
			m_vertices[2 + i * 4].position = sf::Vector2f(m_dotSize.x + totalGapLength, m_dotSize.y);
			m_vertices[3 + i * 4].position = sf::Vector2f(totalGapLength, m_dotSize.y);
			totalGapLength += m_gapLength + m_dotSize.x;
		}
	}
	else if (m_axis == Axis::y)
	{
		for (unsigned i = 0; i < m_vertices.getVertexCount() / 4; ++i)
		{
			m_vertices[0 + i * 4].position = sf::Vector2f(0, totalGapLength);
			m_vertices[1 + i * 4].position = sf::Vector2f(0, m_dotSize.y + totalGapLength);
			m_vertices[2 + i * 4].position = sf::Vector2f(m_dotSize.x, m_dotSize.y + totalGapLength);
			m_vertices[3 + i * 4].position = sf::Vector2f(m_dotSize.x, totalGapLength);
			totalGapLength += m_gapLength + m_dotSize.y;
		}
	}
}

void dottedLine::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	states.texture = nullptr;
	target.draw(m_vertices, states);
}
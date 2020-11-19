#include "Events.hpp"

#include "ball.hpp"
#include "infos.hpp"

void pointsCount(Ball& ball, unsigned playerPoints, unsigned aiPoints)
{
	if (ball.getPosition().x >= SCREEN_WIDTH)
	{
		++playerPoints;
		ball.launch();
	}
	else if (ball.getPosition().x <= 0)
	{
		++aiPoints;
		ball.launch();
	}
}
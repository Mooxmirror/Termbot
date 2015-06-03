#include "Point.hpp"

// New point with the specific x and y coordinates
Point::Point(int x, int y)
{
	this->x = x;
	this->y = y;
}
// Copies the coordinates from src to the new point
Point::Point(const Point& src)
{
	x = src.x;
	y = src.y;
}

// New point with the coordinates (0, 0)
Point::Point() : Point(0, 0) {}

// Compares the coordinates
auto Point::operator==(Point cmp) -> bool
{
	return cmp.x == x && cmp.y == y;
}

// Creates a new point with (src.x, src.y - 1)
auto Point::up() -> Point
{
	return Point(x, y - 1);
}

// Creates a new point with (src.x, src.y + 1)
auto Point::down() -> Point
{
	return Point(x, y + 1);
}

// Creates a new point with (src.x - 1, src.y)
auto Point::left() -> Point
{
	return Point(x - 1, y);
}

// Creates a new point with (src.x + 1, src.y)
auto Point::right() -> Point
{
	return Point(x + 1, y);
}

// Moves the point upwards (y - 1)
auto Point::move_up() -> void
{
	y -= 1;
}

// Moves the point downwards (y + 1)
auto Point::move_down() -> void
{
	y += 1;
}

// Moves the point leftwards (x - 1)
auto Point::move_left() -> void
{
	x -= 1;
}

// Moves the point rightwards (x + 1)
auto Point::move_right() -> void
{
	x += 1;
}

// Moves the point forward relative to the specified direction 
auto Point::forward(int direction) -> Point
{
	switch (direction)
	{
	case 0:
		return right();
	case 1:
		return down();
	case 2:
		return left();
	case 3:
		return up();
	default:
		return Point(x, y);
	}
}
#ifndef TERMBOT_POINT_H_
#define TERMBOT_POINT_H_

// Stores a point with XY-components
struct Point
{
	// New point with the specific x and y coordinates
	Point(int x, int y);
	// Copies the coordinates from src to the new point
	Point(const Point& cp);
	// New point with the coordinates (0, 0)
	Point();

	// Compares the coordinates
	auto operator==(Point cmp)	-> bool;
	// Creates a new point with (src.x, src.y - 1)
	auto up()					-> Point;
	// Creates a new point with (src.x, src.y + 1)
	auto down()					-> Point;
	// Creates a new point with (src.x - 1, src.y)
	auto left()					-> Point;
	// Creates a new point with (src.x + 1, src.y)
	auto right()				-> Point;
	// Moves the point forward relative to the specified direction 
	auto forward(int direction) -> Point;
	// Moves the point upwards (y - 1)
	auto move_up()				-> void;
	// Moves the point downwards (y + 1)
	auto move_down()			-> void;
	// Moves the point leftwards (x - 1)
	auto move_left()			-> void;
	// Moves the point rightwards (x + 1)
	auto move_right()			-> void;

	// X component of the point
	int x;
	// Y component of the point
	int y;
};

#endif